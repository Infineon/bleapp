//
//  RCViewController.swift
//  BleRemote
//

import UIKit
import CoreBluetooth

class RCViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {
    
    var car : RcCar!
    
    @IBOutlet weak var tachLeft: UILabel!
    @IBOutlet weak var tachRight: UILabel!
   
    override func viewDidLoad() {
        super.viewDidLoad()
        leftMotor.dataSource = self
        leftMotor.delegate = self
        rightMotor.dataSource = self
        rightMotor.delegate = self
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.ConnectionComplete, object: nil, queue: NSOperationQueue.mainQueue()) { _ in
            self.powerLeft.userInteractionEnabled = true
            self.powerRight.userInteractionEnabled = true
            self.leftMotor.userInteractionEnabled = true
            self.rightMotor.userInteractionEnabled = true
            self.leftMotor.selectRow(10, inComponent: 0, animated: false)
            self.rightMotor.selectRow(10, inComponent: 0, animated: false)
        }
        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.DisconnectedDevice, object: nil, queue: NSOperationQueue.mainQueue()) { _ in
            print("Disconnected device")
            self.navigationController?.popViewControllerAnimated(true)

        }

        
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.UpdatedTach, object: nil, queue: NSOperationQueue.mainQueue()) { _ in
            self.tachLeft.text = "\(self.car.tachLeft)"
            self.tachRight.text = "\(self.car.tachRight)"
        }
        
    }
    
    override func viewWillDisappear(animated: Bool) {
        NSNotificationCenter.defaultCenter().removeObserver(self)
        bleLand.disconnectDevice(car.connection.peripheral)
    }

   
    // MARK: - PickerView 
    @IBOutlet weak var leftMotor: UIPickerView!
    @IBOutlet weak var rightMotor: UIPickerView!
    
    func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int {
        return 1
    }
    func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return 21
    }
    
    func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let rval = convertRowToPercent(row)
        return "\(rval)"
        
    }
    
    func pickerView(pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if pickerView == leftMotor {
            car.speedLeft = Int8(convertRowToPercent(row))
        }
        if pickerView == rightMotor {
            car.speedRight = Int8(convertRowToPercent(row))

        }
    }
    
    // There are 21 rows... the 0 row is -100 and then each row is 10 more than the previous
    func convertRowToPercent(row : Int) -> Int
    {
        return -100 + row*10
    }

    @IBOutlet weak var powerRight: UISwitch!
    @IBOutlet weak var powerLeft: UISwitch!
    
    @IBAction func switchPower(sender: UISwitch) {
        var control : UIPickerView = leftMotor
        if(sender == powerRight)
        {
            control = rightMotor
        }
       
        if sender.on {
            control.userInteractionEnabled = true
        }
        else // sender must be off
        {
            control.userInteractionEnabled = false
            control.selectRow(10, inComponent: 0, animated: true)
            if control == rightMotor
            {
                car.speedRight = 0
            }
            else // control must equal leftMotor
            {
                car.speedLeft = 0
            }
        }
    }
    
}
