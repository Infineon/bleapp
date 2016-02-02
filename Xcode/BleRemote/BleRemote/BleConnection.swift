//
//  BleConnection.swift
//  BleRemote
//

import CoreBluetooth

class BleConnection: NSObject, CBPeripheralDelegate {
    
    var peripheral : CBPeripheral
    var car : RcCar!
    
    var speedLeftChar : CBCharacteristic?
    var speedRightChar : CBCharacteristic?
    var tachLeftChar : CBCharacteristic?
    var tachRightChar : CBCharacteristic?
    
    init(peripheral: CBPeripheral)
    {
        self.peripheral = peripheral
        super.init()
        peripheral.delegate = self
    }
    
    func peripheral(peripheral: CBPeripheral, didDiscoverServices error: NSError?) {
        
        for service in peripheral.services! {
            print("Found service \(service)")
            if service.UUID == BLEParameters.motorService {
                peripheral.discoverCharacteristics(nil, forService: service )
            }
        }
    }
    
    func peripheral(peripheral: CBPeripheral, didDiscoverCharacteristicsForService service: CBService, error: NSError?) {
        for i in service.characteristics!
        {
      
                print("Found characteristic \(i)")
                switch i.UUID {
                case BLEParameters.speedLeftChar:  speedLeftChar = i
                case BLEParameters.speedRightChar: speedRightChar = i
                case BLEParameters.tachLeftChar:   tachLeftChar = i
                case BLEParameters.tachRightChar:  tachRightChar = i
                default: break
                }
        }
        peripheral.setNotifyValue(true, forCharacteristic: tachLeftChar!)
        peripheral.setNotifyValue(true, forCharacteristic: tachRightChar!)
        
        NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.ConnectionComplete, object: nil)
    }
    
    func peripheral(peripheral: CBPeripheral, didUpdateValueForCharacteristic characteristic: CBCharacteristic, error: NSError?) {
        
        if characteristic.value != nil {

            if characteristic == tachLeftChar! {
                var out: NSInteger = 0
                characteristic.value!.getBytes(&out, length:sizeof(NSInteger))
                car.tachLeft = out
                NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.UpdatedTach, object: nil)
            }
            
            if characteristic == tachRightChar! {
                var out: NSInteger = 0
                characteristic.value!.getBytes(&out, length:sizeof(NSInteger))
                car.tachRight = out
                NSNotificationCenter.defaultCenter().postNotificationName(RCNotifications.UpdatedTach, object: nil)
            }
        }
    }
    
    
    func writeLeftSpeed(val : Int8)
    {
        if speedLeftChar != nil {
            bleWriteInt8(val, char: speedLeftChar!)
        }
    }
    
    func writeRightSpeed(val : Int8)
    {
        if speedRightChar != nil {
            bleWriteInt8(val, char: speedRightChar!)
        }
    }
    
    private func bleWriteInt8(var val: Int8, char: CBCharacteristic)
    {
        let ns = NSData(bytes: &val, length: sizeof(Int8))
        peripheral.writeValue(ns, forCharacteristic: char, type: CBCharacteristicWriteType.WithResponse)
    }

}
