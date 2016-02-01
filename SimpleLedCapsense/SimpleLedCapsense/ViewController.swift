//
//  ViewController.swift
//  SimpleLedCapsense

import UIKit
import CoreBluetooth

struct RCNotifications {
    static let BluetoothReady = "org.elkhorn-creek.simpleledcapsense.bluetoothReady"
    static let FoundDevice = "org.elkhorn-creek.simpleledcapsense.founddevice"
    static let ConnectionComplete = "org.elkhorn-creek.simpleledcapsense.connectioncomplete"
    static let ServiceScanComplete = "org.elkhorn-creek.simpleledcapsense.servicescancomplete"
    static let CharacteristicScanComplete = "org.elkhorn-creek.simpleledcapsense.characteristicsscancomplete"
    static let DisconnectedDevice = "org.elkhorn-creek.simpleledcapsense.disconnecteddevice"
    static let UpdatedCapsense = "org.elkhorn-creek.simpleledcapsense.updatedcapsense"

}



class ViewController: UIViewController {

    var bleLand : BlueToothNeighborhood!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        bleLand = BlueToothNeighborhood()
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.BluetoothReady, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.blueToothOn() }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.FoundDevice, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.foundDevice() }
      
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.ConnectionComplete, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.connectionComplete() }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.ServiceScanComplete, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.discoveredServices() }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.CharacteristicScanComplete, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.discoveredCharacteristics() }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.DisconnectedDevice, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.disconnectedComplete() }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.UpdatedCapsense, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.updateCapsense() }

    }
    
    // MARK: - Manage Bluetooth Buttons
    @IBOutlet weak var startBluetoothButton: UIButton!
    @IBAction func startBluetoothAction(sender: AnyObject){
        bleLand.startUpCentralManager()
        startBluetoothButton.enabled = false
    }
    
    func blueToothOn()
    {
        searchButton.enabled = true
    }
    
    @IBOutlet weak var searchButton: UIButton!
    @IBAction func searchAction(sender: AnyObject) {
        bleLand.discoverDevice()
        searchButton.enabled = false
    }
    
    func foundDevice()
    {
        connectDeviceButton.enabled = true
    }
    
    @IBOutlet weak var connectDeviceButton: UIButton!
    @IBAction func connectDeviceAction(sender: AnyObject) {
        connectDeviceButton.enabled = false
        bleLand.connectToDevice()
    }
    
    func connectionComplete()
    {
        discoverServicesButton.enabled = true
        disconnectButton.enabled = true
    }
    
    @IBOutlet weak var discoverServicesButton: UIButton!
    @IBAction func discoverServicesAction(sender: AnyObject) {
        bleLand.discoverServices()
        discoverServicesButton.enabled = false
    }
    
    func discoveredServices()
    {
        discoverCharacteristicsButton.enabled = true
    }
  
    
    @IBOutlet weak var discoverCharacteristicsButton: UIButton!
    
    @IBAction func discoverCharacteristicsAction(sender: AnyObject) {
        bleLand.discoverCharacteristics()
        discoverCharacteristicsButton.enabled = false
    }
    
    func discoveredCharacteristics()
    {
        ledSwitch.enabled = true
        capsenseNotifySwitch.enabled = true
    }
   
    
    @IBOutlet weak var disconnectButton: UIButton!
    
    @IBAction func disconnectAction(sender: AnyObject) {
        bleLand.disconnectDevice()
    }
    func disconnectedComplete()
    {
        searchButton.enabled = true
        connectDeviceButton.enabled = false
        discoverServicesButton.enabled = false
        discoverCharacteristicsButton.enabled = false
        disconnectButton.enabled = false
        ledSwitch.enabled = false
        capsenseNotifySwitch.enabled = false
        capsenseNotifySwitch.on = false
    }
    
    // MARK: - Manage Capsense Label, Capsense Button + Red LED Switch

    @IBOutlet weak var capsenseLabel: UILabel!

    @IBOutlet weak var ledSwitch: UISwitch!
    
    @IBAction func ledSwitchAction(sender: AnyObject) {
        if ledSwitch.on {
            bleLand.writeLedCharacteristic(1)
        }
        else
        {
            bleLand.writeLedCharacteristic(0)
        }
    }

    
    @IBAction func capsenseNotifyAction(sender: UISwitch) {
        bleLand.writeCapsenseNotify(sender.on)
    }
    
    
    @IBOutlet weak var capsenseNotifySwitch: UISwitch!
    func updateCapsense()
    {
        capsenseLabel.text = "\(bleLand!.capsenseValue)"
    }
}

