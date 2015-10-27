//
//  ViewController.swift
//  Permanent Storage
//
//  Created by DIAN REN on 9/17/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        // store user id or other things
        
        //NSUserDefaults.standardUserDefaults().setObject("Rob", forKey: "name") /// store data
        
        var name = NSUserDefaults.standardUserDefaults().objectForKey("name")! as String // ! means not warpped,not optional
        
        println(name) // retrives data
        
        
        
        ///  for  array
        
        var arr = [1, 2, 3]
        
        //NSUserDefaults.standardUserDefaults().setObject(arr, forKey: "array")
        
        var recalledArray = NSUserDefaults.standardUserDefaults().objectForKey("array")! as NSArray
        
        println(recalledArray[2])
        
    }
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

