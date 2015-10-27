//
//  ViewController.swift
//  is-it-prime
//
//  Created by DIAN REN on 9/16/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    
    @IBOutlet weak var enterNumber: UITextField!
    
    
    @IBOutlet weak var resultLabel: UILabel!
    
    @IBAction func pressButton(sender: AnyObject) {
        
        var number = enterNumber.text.toInt()
        
        var isPrime = true
        
        if number != nil {
            
            var unwrappedNumber = number!
        
            if unwrappedNumber == 1 {
            
                isPrime = false
            
            }
        
            if unwrappedNumber != 2 && unwrappedNumber != 1 {
            
                for var i = 2; i < unwrappedNumber; i++ {
                
                    if unwrappedNumber % i == 0 {
                    
                        isPrime = false
                    
                    }
                
                }
            
            }
        
            resultLabel.text = "\(isPrime)"
        
        } else {
            
            resultLabel.text = "Please enter a number"
            
        }

        
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

