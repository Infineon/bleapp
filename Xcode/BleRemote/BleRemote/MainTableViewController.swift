//
//  MainTableViewController.swift
//  BleRemote
//

import UIKit
var bleLand = BlueToothNeighborhood()

class MainTableViewController: UITableViewController {
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        bleLand.startUpCentralManager()

        // if a new device is found then reload the table
        NSNotificationCenter.defaultCenter().addObserverForName(RCNotifications.FoundDevice, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.tableView.reloadData() }
    }
    
    override func viewWillDisappear(animated: Bool) {
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }

    // MARK: - Table view data source

    // The table only has one section, just the list of Robot devices that it can see
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        // #warning Potentially incomplete method implementation.
        // Return the number of sections.
        return 1
    }

    // The number of rows will be the number of BLE devices that you have seen with the right service being advertised
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete method implementation.
        // Return the number of rows in the section.
        return bleLand.cars.count
    }

    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("rccar", forIndexPath: indexPath) 
        cell.tag = indexPath.row
        cell.textLabel?.text = bleLand.cars[indexPath.row].connection.peripheral.name
    
        return cell
    }

    
    // MARK: - Navigation

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        //let destination = segue.destinationViewController as? UIViewController
        if let rcvc = segue.destinationViewController as? RCViewController
        {
            if let tvc = sender as? UITableViewCell {
                rcvc.car = bleLand.cars[tvc.tag]
                bleLand.connectToDevice(rcvc.car.connection.peripheral)
            }
        }
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }
}
