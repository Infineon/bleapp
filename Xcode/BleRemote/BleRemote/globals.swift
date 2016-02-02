//
//  globals.swift
//  BleRemote
//

import CoreBluetooth

//  Identify the NSNotification Messages
struct RCNotifications {
    static let FoundDevice = "com.cypress.bleremote.founddevice"
    static let ConnectionComplete = "com.cypress.bleremote.connectioncomplete"
    static let DisconnectedDevice = "com.cypress.bleremote.disconnecteddevice"
    
    static let UpdatedSpeed = "com.cypress.bleremote.updatedspeed"
    static let UpdatedTach = "com.cypress.bleremote.updatedtach"
    
}

// Identify the UUIDs of the services and characteristics for the Robot
struct BLEParameters {
    static let motorService = CBUUID(string: "00000000-0000-1000-8000-00805F9B34F0")
    static let speedLeftChar = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F1")
    static let speedRightChar = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F2")
    static let tachLeftChar =  CBUUID(string:"00000000-0000-1000-8000-00805F9B34F3")
    static let tachRightChar = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F4")
}
