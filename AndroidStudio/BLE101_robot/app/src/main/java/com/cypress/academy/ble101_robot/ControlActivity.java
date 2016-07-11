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

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

/**
 * This Activity provides the user interface to control the robot.  The Activity
 * communicates with {@code BluetoothLeService}, which in turn interacts with the
 * Bluetooth LE API.
 */
public class ControlActivity extends AppCompatActivity {

    // Objects to access the layout items for Tach, Buttons, and Seek bars
    private static TextView mTachLeftText;
    private static TextView mTachRightText;
    private static SeekBar mSpeedLeftSeekBar;
    private static SeekBar mSpeedRightSeekBar;
    private static Switch mEnableLeftSwitch;
    private static Switch mEnableRightSwitch;

    // This tag is used for debug messages
    private static final String TAG = ControlActivity.class.getSimpleName();

    private static String mDeviceAddress;
    private static PSoCBleRobotService mPSoCBleRobotService;

    /**
     * This manages the lifecycle of the BLE service.
     * When the service starts we get the service object, initialize the service, and connect.
     */
    private final ServiceConnection mServiceConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            Log.i(TAG, "onServiceConnected");
            mPSoCBleRobotService = ((PSoCBleRobotService.LocalBinder) service).getService();
            if (!mPSoCBleRobotService.initialize()) {
                Log.e(TAG, "Unable to initialize Bluetooth");
                finish();
            }
            // Automatically connects to the car database upon successful start-up initialization.
            mPSoCBleRobotService.connect(mDeviceAddress);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mPSoCBleRobotService = null;
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        // Assign the various layout objects to the appropriate variables
        mTachLeftText = (TextView) findViewById(R.id.tach_left);
        mTachRightText = (TextView) findViewById(R.id.tach_right);
        mEnableLeftSwitch = (Switch) findViewById(R.id.enable_left);
        mEnableRightSwitch = (Switch) findViewById(R.id.enable_right);
        mSpeedLeftSeekBar = (SeekBar) findViewById(R.id.speed_left);
        mSpeedRightSeekBar = (SeekBar) findViewById(R.id.speed_right);

        final Intent intent = getIntent();
        mDeviceAddress = intent.getStringExtra(ScanActivity.EXTRAS_BLE_ADDRESS);

        // Bind to the BLE service
        Log.i(TAG, "Binding Service");
        Intent RobotServiceIntent = new Intent(this, PSoCBleRobotService.class);
        bindService(RobotServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        /* This will be called when the left motor enable switch is changed */
        mEnableLeftSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                enableMotorSwitch(isChecked, PSoCBleRobotService.Motor.LEFT);
            }
        });

        /* This will be called when the right motor enable switch is changed */
        mEnableRightSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                enableMotorSwitch(isChecked, PSoCBleRobotService.Motor.RIGHT);
            }
        });

        /* This will be called when the left speed seekbar is moved */
        mSpeedLeftSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }

            public void onProgressChanged(SeekBar seekBar, int speed, boolean fromUser) {
                /* Scale the speed from what the seek bar provides to what the PSoC FW expects */
                speed = scaleSpeed(speed);
                mPSoCBleRobotService.setMotorSpeed(PSoCBleRobotService.Motor.LEFT, speed);
                Log.d(TAG, "Left Speed Change to:" + speed);
            }
        });

        /* This will be called when the right speed seekbar is moved */
        mSpeedRightSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }

            public void onProgressChanged(SeekBar seekBar, int speed, boolean fromUser) {
                /* Scale the speed from what the seek bar provides to what the PSoC FW expects */
                speed = scaleSpeed(speed);
                mPSoCBleRobotService.setMotorSpeed(PSoCBleRobotService.Motor.RIGHT, speed);
                Log.d(TAG, "Right Speed Change to:" + speed);
            }
        });
    } /* End of onCreate method */

    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(mRobotUpdateReceiver, makeRobotUpdateIntentFilter());
        if (mPSoCBleRobotService != null) {
            final boolean result = mPSoCBleRobotService.connect(mDeviceAddress);
            Log.i(TAG, "Connect request result=" + result);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mRobotUpdateReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        mPSoCBleRobotService = null;
    }

     /**
     * Scale the speed read from the slider (0 to 20) to
     * what the car object expects (-100 to +100).
     *
     * @param speed Input speed from the slider
     * @return scaled value of the speed
     */
    private int scaleSpeed(int speed) {
        final int SCALE = 10;
        final int OFFSET = 100;

        return ((speed * SCALE) - OFFSET);
    }

    /**
     * Enable or disable the left/right motor
     *
     * @param isChecked used to enable/disable motor
     * @param motor is the motor to enable/disable (left or right)
     */
    private void enableMotorSwitch(boolean isChecked, PSoCBleRobotService.Motor motor) {
        if (isChecked) { // Turn on the specified motor
            mPSoCBleRobotService.setMotorState(motor, true);
            Log.d(TAG, (motor == PSoCBleRobotService.Motor.LEFT ? "Left" : "Right") + " Motor On");
        } else { // turn off the specified motor
            mPSoCBleRobotService.setMotorState(motor, false);
            mPSoCBleRobotService.setMotorSpeed(motor, 0); // Force motor off
            if(motor == PSoCBleRobotService.Motor.LEFT) {
                mSpeedLeftSeekBar.setProgress(10); // Move slider to middle position
            } else {
                mSpeedRightSeekBar.setProgress(10); // Move slider to middle position
            }
            Log.d(TAG, (motor == PSoCBleRobotService.Motor.LEFT ? "Left" : "Right") + " Motor Off");
        }

    }

    /**
     * Handle broadcasts from the Car service object. The events are:
     * ACTION_CONNECTED: connected to the car.
     * ACTION_DISCONNECTED: disconnected from the car.
     * ACTION_DATA_AVAILABLE: received data from the car.  This can be a result of a read
     * or notify operation.
     */
    private final BroadcastReceiver mRobotUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            switch (action) {
                case PSoCBleRobotService.ACTION_CONNECTED:
                    // No need to do anything here. Service discovery is started by the service.
                    break;
                case PSoCBleRobotService.ACTION_DISCONNECTED:
                    mPSoCBleRobotService.close();
                    break;
                case PSoCBleRobotService.ACTION_DATA_AVAILABLE:
                    // This is called after a Notify completes
                    mTachLeftText.setText(String.format("%d", PSoCBleRobotService.getTach(PSoCBleRobotService.Motor.LEFT)));
                    mTachRightText.setText(String.format("%d", PSoCBleRobotService.getTach(PSoCBleRobotService.Motor.RIGHT)));
                    break;
            }
        }
    };

    /**
     * This sets up the filter for broadcasts that we want to be notified of.
     * This needs to match the broadcast receiver cases.
     *
     * @return intentFilter
     */
    private static IntentFilter makeRobotUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(PSoCBleRobotService.ACTION_CONNECTED);
        intentFilter.addAction(PSoCBleRobotService.ACTION_DISCONNECTED);
        intentFilter.addAction(PSoCBleRobotService.ACTION_DATA_AVAILABLE);
        return intentFilter;
    }
}