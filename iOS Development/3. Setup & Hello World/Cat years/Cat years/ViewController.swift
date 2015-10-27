//
//  ViewController.swift
//  Cat years
//
//  Created by DIAN REN on 9/15/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBAction func findAge(sender: AnyObject) {
        
        // age.text is string
        var enteredAge = age.text.toInt()
        
        if enteredAge != nil {
        // ! means no invertable
        var catYears = enteredAge! * 7
        
        resultLabel.text = "Your cat is \(catYears) in cat years"
            
        } else {
            
            resultLabel.text = "Please enter a number in the box"
        }
    }
    
    @IBOutlet weak var age: UITextField!
    
    @IBOutlet weak var resultLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

