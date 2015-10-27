//
//  TableViewController.swift
//  Memorable Places
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

/// create a dictionary to store a location of latitude, longitude and description
// indeed we can not create a empty array outside the tableViewController class, we should put something in it. The system will add automaticly. So, indeed the array size is actually 1. We should remove that later.
var places = [Dictionary<String, String>()]



var activePlace = -1 // -1 means no active place, user should add himself


class TableViewController: UITableViewController {

    @IBOutlet var placesTable: UITableView!
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        
        // if the dictionary is empty, we should create a example to user
        if places.count == 1 {
            
            places.removeAtIndex(0)  // remove the original one
            
            places.append(["name": "Taj Mahal", "latitude" : "27.175277", "longitude": "78.042128"])
            
        }
        
        //// permanent storeage /////
        
        if NSUserDefaults.standardUserDefaults().objectForKey("dictionary") != nil {// check whether toDoList exits or not
            
            places = NSUserDefaults.standardUserDefaults().objectForKey("dictionary")! as [Dictionary<String, String>]
        }

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        // #warning Potentially incomplete method implementation.
        // Return the number of sections.
        return 1
    }

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete method implementation.
        // Return the number of rows in the section.
        
        
        return places.count
    }

    // how we create a table cell
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as UITableViewCell

        cell.textLabel?.text = places[indexPath.row]["name"]

        return cell
    }
    
    
    
    /// this function is : when you press the name in table, it will jump to the map view !!!
    override func tableView(tableView: UITableView, willSelectRowAtIndexPath indexPath: NSIndexPath) -> NSIndexPath? {
        
        activePlace = indexPath.row
        
        return indexPath
        
    }
    
    
    
    //// last part:  当你加了地址以后，回到表， 然后再点“＋”， 现在回到的是上一个被加的地址， 而不是用户自己的地址。 所以要修补这个bug
    //  首先： 需要到 “ main.storyboard“，把"+" 的 identify 变成" newPlace"
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        if segue.identifier == "newPlace" {
            
            activePlace = -1
            
        }
        
    }
    
    
    
    
    /////////////////////// Delete a item //////////////////////
    
    override func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath) {
        
        if editingStyle == UITableViewCellEditingStyle.Delete {
            
            places.removeAtIndex(indexPath.row)
            
            NSUserDefaults.standardUserDefaults().setObject(places, forKey: "dictionary") // each time should update NSUser
            
            placesTable.reloadData()  //  should update the table
            
        }
        
    }
    
    
//    override func viewDidAppear(animated: Bool) {
//        
//        placesTable.reloadData()
//        
//    }
    
    

    /*
    // Override to support conditional editing of the table view.
    override func tableView(tableView: UITableView, canEditRowAtIndexPath indexPath: NSIndexPath) -> Bool {
        // Return NO if you do not want the specified item to be editable.
        return true
    }
    */

    /*
    // Override to support editing the table view.
    override func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath) {
        if editingStyle == .Delete {
            // Delete the row from the data source
            tableView.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Fade)
        } else if editingStyle == .Insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        }    
    }
    */

    /*
    // Override to support rearranging the table view.
    override func tableView(tableView: UITableView, moveRowAtIndexPath fromIndexPath: NSIndexPath, toIndexPath: NSIndexPath) {

    }
    */

    /*
    // Override to support conditional rearranging of the table view.
    override func tableView(tableView: UITableView, canMoveRowAtIndexPath indexPath: NSIndexPath) -> Bool {
        // Return NO if you do not want the item to be re-orderable.
        return true
    }
    */

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using [segue destinationViewController].
        // Pass the selected object to the new view controller.
    }
    */

}
