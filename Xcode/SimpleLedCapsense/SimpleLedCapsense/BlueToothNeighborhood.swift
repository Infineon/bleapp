

import CoreBluetooth


private struct BLEParameters {
    static let capsenseLedService = CBUUID(string: "00000000-0000-1000-8000-00805F9B34F0")
    static let ledCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F1")
    static let capsenseCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F2")
}

class BlueToothNeighborhood: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate  {
    
    private var centralManager : CBCentralManager!
    private var capsenseLedBoard : CBPeripheral?
    private var capsenseLedService : CBService!
    private var ledCharacteristic : CBCharacteristic!
    private var capsenseCharacteristic : CBCharacteristic!
    
    
    // MARK: - Functions to start of the central manager
    
    func startUpCentralManager() {
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    @objc func centralManagerDidUpdateState(central: CBCentralManager) {
        switch (central.state) {
        case .PoweredOff: break
        case .PoweredOn:
            NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.BluetoothReady, object: nil)
            print("Bluetooth is on")
        case .Resetting: break
        case .Unauthorized: break
        case .Unknown:break
        case .Unsupported:break
        }
    }
    
    // MARK: - Functions to discover ble devices
    
    func discoverDevice() {
        print("Starting scan")
        centralManager.scanForPeripheralsWithServices([BLEParameters.capsenseLedService], options: [CBCentralManagerScanOptionAllowDuplicatesKey:false])
    }
    
    func centralManager(central: CBCentralManager, didDiscoverPeripheral peripheral: CBPeripheral, advertisementData: [String : AnyObject], RSSI: NSNumber)
    {
        if capsenseLedBoard == nil {
            print("Found a new Periphal advertising capsense led service")
            capsenseLedBoard = peripheral
            NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.FoundDevice, object: nil)
            centralManager.stopScan()
        }
    }
    
    // MARK: - Functions to connect to a device
    func connectToDevice()
    {
        centralManager.connectPeripheral(capsenseLedBoard!, options: nil)
    }
    
    // a device connection is complete
    func centralManager(central: CBCentralManager, didConnectPeripheral peripheral: CBPeripheral) {
        print("Connection complete \(capsenseLedBoard) \(peripheral)")
        capsenseLedBoard!.delegate = self
        NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.ConnectionComplete, object: nil)
    }
    
    
    // MARK: - Functions to discover the services on a device
    func discoverServices()
    {
        capsenseLedBoard!.discoverServices(nil)
    }
    
    func peripheral(peripheral: CBPeripheral, didDiscoverServices error: NSError?) {
        print("discovered services")
        for service in peripheral.services! {
            print("Found service \(service)")
            if service.UUID == BLEParameters.capsenseLedService {
                capsenseLedService = service // as! CBService
            }
        }
        NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.ServiceScanComplete, object: nil)
        
    }
    
    // MARK: - Functions to discover the characteristics
    
    func discoverCharacteristics()
    {
        capsenseLedBoard!.discoverCharacteristics(nil, forService: capsenseLedService)
    }
    
    func peripheral(peripheral: CBPeripheral, didDiscoverCharacteristicsForService service: CBService, error: NSError?) {
        for characteristic in service.characteristics!
        {
            
            print("Found characteristic \(characteristic)")
            switch characteristic.UUID {
            case BLEParameters.capsenseCharactersticUUID:  capsenseCharacteristic = characteristic
            case BLEParameters.ledCharactersticUUID: ledCharacteristic = characteristic
            default: break
            }
            
        }
        
        NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.CharacteristicScanComplete, object: nil)
    }
    
    // MARK: - Functions to handle disconnection
    func disconnectDevice()
    {
        centralManager.cancelPeripheralConnection(capsenseLedBoard!)
    }
    
    // disconnected a device
    func centralManager(central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: NSError?) {
        print("Disconnected \(peripheral)")
        capsenseLedBoard = nil
        NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.DisconnectedDevice, object: nil)
    }
    
    
    // MARK: - Functions to write/read from the device
    func writeLedCharacteristic(var val: Int8)
    {
        let ns = NSData(bytes: &val, length: sizeof(Int8))
        capsenseLedBoard!.writeValue(ns, forCharacteristic: ledCharacteristic, type: CBCharacteristicWriteType.WithResponse)
    }
    
    func writeCapsenseNotify(state: Bool)
    {
        capsenseLedBoard!.setNotifyValue(state, forCharacteristic: capsenseCharacteristic)
    }
    
    var capsenseValue = 0
    
    // This delegate function is called when an updated value is received from the Bluetooth Stack
    func peripheral(peripheral: CBPeripheral, didUpdateValueForCharacteristic characteristic: CBCharacteristic, error: NSError?) {
        if characteristic == capsenseCharacteristic {
            var out: NSInteger = 0
            characteristic.value!.getBytes(&out, length:sizeof(NSInteger))
            capsenseValue = out
            NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.UpdatedCapsense, object: nil)
        }
    }
    
}

