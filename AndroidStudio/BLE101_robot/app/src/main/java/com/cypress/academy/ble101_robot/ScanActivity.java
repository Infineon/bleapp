/*
Copyright (c) 2016, Cypress Semiconductor Corporation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


For more information on Cypress BLE products visit:
http://www.cypress.com/products/bluetooth-low-energy-ble
 */

package com.cypress.academy.ble101_robot;

import android.Manifest;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanFilter;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.ParcelUuid;
import android.support.annotation.NonNull;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 * Activity for scanning and displaying BLE devices that match our service UUID
  */
@TargetApi(Build.VERSION_CODES.M) // This is needed so that we can use Marshmallow API calls
public class ScanActivity extends AppCompatActivity {

    private final static String TAG = ScanActivity.class.getSimpleName();

    // This  tag that allosw us to pass the address of the selected
    // BLE device to the control activity
    public static final String EXTRAS_BLE_ADDRESS = "BLE_ADDRESS";

    // BLE related objects
    private static BluetoothAdapter mBluetoothAdapter;
    private static BluetoothLeScanner mLEScanner;
    private static boolean mScanning;
    private static Handler mHandler;

    private static final int REQUEST_ENABLE_BLE = 1;
    // Scan for 10 seconds.
    private static final long SCAN_TIMEOUT = 10000;

    //This is required for Android 6.0 (Marshmallow)
    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 1;

     // This allows rescanning when we swipe down from the top of the screen
    private static SwipeRefreshLayout mSwipeRefreshLayout;

    // This is the list view in the layout that holds the items
    ListView BleDeviceList;

    // These lists hold the BLE devices found during scanning and their names
    List<BluetoothDevice> mBluetoothDevice;
    List<String> mBleName;

     // The array adapter will be used to display the list of devices found during scanning
    ArrayAdapter<String> mBleArrayAdapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scan);

        // This is the list view in the layout that holds the items
        BleDeviceList = (ListView) findViewById(R.id.BlelistItems);

        // This is used once scanning is started in a new thread
        mHandler = new Handler();

        // Check to see if the device supports BLE. If not, just exit right away.
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, R.string.no_ble, Toast.LENGTH_SHORT).show();
            finish();
        }

        // Initialize the Bluetooth adapter using the bluetoothManager
        final BluetoothManager bluetoothManager =
                (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        mBluetoothAdapter = bluetoothManager.getAdapter();

        // Checks if Bluetooth manager returned the adapter. If not, exit.
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, R.string.no_ble, Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        //This section required for Android 6.0 (Marshmallow) permissions
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android M Permission check 
            if (this.checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                final AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("This app needs location access ");
                builder.setMessage("Please grant location access so this app can detect devices.");
                builder.setPositiveButton(android.R.string.ok, null);
                builder.setOnDismissListener(new DialogInterface.OnDismissListener() {
                    public void onDismiss(DialogInterface dialog) {
                        requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_REQUEST_COARSE_LOCATION);
                    }
                });
                builder.show();
            }
        } //End of section for Android 6.0 (Marshmallow)
    }

    //This method required for Android 6.0 (Marshmallow) permissions
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String permissions[], @NonNull int[] grantResults) {
        switch (requestCode) {
            case PERMISSION_REQUEST_COARSE_LOCATION: {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Log.i("Permission for 6.0:", "Coarse location permission granted");
                } else {
                    final AlertDialog.Builder builder = new AlertDialog.Builder(this);
                    builder.setTitle("Error");
                    builder.setMessage("Since location access has not been granted, scanning will not work.");
                    builder.setPositiveButton(android.R.string.ok, null);
                    builder.setOnDismissListener(new DialogInterface.OnDismissListener() {
                        @Override
                        public void onDismiss(DialogInterface dialog) {
                        }
                    });
                    builder.show();
                }
            }
        }
    } //End of section for Android 6.0 (Marshmallow)

    @Override
    protected void onResume() {
        super.onResume();

        // Verify that bluetooth is enabled. If not, request permission to enable it.
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BLE);

        }

        // Create arrays to hold BLE info found during scanning
        mBluetoothDevice = new ArrayList<>();
        mBleName = new ArrayList<>();
        // Create an array adapter and associate it with the list in the layout that displays the values
        mBleArrayAdapter = new ArrayAdapter<>(this, R.layout.ble_device_list, R.id.ble_name, mBleName);
        BleDeviceList.setAdapter(mBleArrayAdapter);
        // Setup the SwipeRefreshLayout and add a listener to refresh when the user
        // swipes down from the top of the screen.
        mSwipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swipeRefreshId);

        // Setup a listener for swipe events
        mSwipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                if (!mScanning) {
                    mBluetoothDevice.clear(); // Remove all existing devices
                    mBleArrayAdapter.clear();
                    scanLeDevice(true); // Start a scan if not already running
                    Log.i(TAG, "Rescanning");
                }
                mSwipeRefreshLayout.setRefreshing(false);
            }
        });

        // Set up a listener for when the user clicks on one of the devices found.
        // We need to launch the control activity when that happens
        BleDeviceList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Log.i(TAG, "Item Selected");
                final Intent intent = new Intent(ScanActivity.this, ControlActivity.class);
                // Send the address of the device that was selected so that the control activity
                // knows which device to connect with
                intent.putExtra(EXTRAS_BLE_ADDRESS, mBluetoothDevice.get(position).getAddress());
                scanLeDevice(false); // Stop scanning
                startActivity(intent);
            }
        });

        scanLeDevice(true); // Start scanning automatically when we first start up
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // User chose not to enable Bluetooth so we will exit.
        if (requestCode == REQUEST_ENABLE_BLE && resultCode == Activity.RESULT_CANCELED) {
            finish();
            return;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onPause() {
        super.onPause();
        scanLeDevice(false);
        mBluetoothDevice.clear();
        mBleArrayAdapter.clear();
        mSwipeRefreshLayout.setRefreshing(false);
    }

    /**
     * Start or stop BLE scanning
     *
     * @param enable start scanning if true
     */
    private void scanLeDevice(final boolean enable) {
        if (enable) { // enable set to start scanning
            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    if(mScanning) {
                        mScanning = false;
                        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
                            //noinspection deprecation
                            mBluetoothAdapter.stopLeScan(mLeScanCallback);
                        } else {
                            mLEScanner.stopScan(mScanCallback);
                        }
                        invalidateOptionsMenu();
                    }
                }
            }, SCAN_TIMEOUT);

            mScanning = true;
            UUID[] motorServiceArray = {PSoCBleRobotService.getMotorServiceUUID()};
            if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
                //noinspection deprecation
                mBluetoothAdapter.startLeScan(motorServiceArray, mLeScanCallback);
            } else { // New BLE scanning introduced in LOLLIPOP
                ScanSettings settings;
                List<ScanFilter> filters;
                mLEScanner = mBluetoothAdapter.getBluetoothLeScanner();
                settings = new ScanSettings.Builder()
                        .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
                        .build();
                filters = new ArrayList<>();
                // We will scan just for the CAR's UUID
                ParcelUuid PUuid = new ParcelUuid(PSoCBleRobotService.getMotorServiceUUID());
                ScanFilter filter = new ScanFilter.Builder().setServiceUuid(PUuid).build();
                filters.add(filter);
                mLEScanner.startScan(filters, settings, mScanCallback);
            }
        } else { // enable set to stop scanning
            if(mScanning) {
                mScanning = false;
                if (Build.VERSION.SDK_INT < 21) {
                    //noinspection deprecation
                    mBluetoothAdapter.stopLeScan(mLeScanCallback);
                } else {
                    mLEScanner.stopScan(mScanCallback);
                }
            }
        }
        invalidateOptionsMenu();
    }

    /**
     * This is the callback for BLE scanning on versions prior to LOLLIPOP
     * It is called each time a device is found so we need to add it to the list
     */
    private final BluetoothAdapter.LeScanCallback mLeScanCallback = new BluetoothAdapter.LeScanCallback() {
        @Override
        public void onLeScan(final BluetoothDevice device, int rssi, byte[] scanRecord) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if(!mBluetoothDevice.contains(device)) { // only add new devices
                        mBluetoothDevice.add(device);
                        mBleName.add(device.getName());
                        mBleArrayAdapter.notifyDataSetChanged(); // Update the list on the screen
                    }

                }
            });
        }
    };

    /**
     * This is the callback for BLE scanning for LOLLIPOP and later
     * It is called each time a devive is found so we need to add it to the list
     */
    private final ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            if(!mBluetoothDevice.contains(result.getDevice())) { // only add new devices
                mBluetoothDevice.add(result.getDevice());
                mBleName.add(result.getDevice().getName());
                mBleArrayAdapter.notifyDataSetChanged(); // Update the list on the screen
            }

        }
    };
}
