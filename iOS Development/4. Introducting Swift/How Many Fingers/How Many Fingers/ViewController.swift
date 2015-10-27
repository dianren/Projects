//
//  ViewController.swift
//  How Many Fingers
//
//  Created by DIAN REN on 9/16/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var guess: UITextField!
    
    @IBOutlet weak var resultLabel: UILabel!
    
    @IBAction func guessButton(sender: AnyObject) {
        
        var randomNumber = arc4random_uniform(6)
        
        var guessInt = guess.text.toInt()
        
        if guessInt != nil && guessInt <= 5 {
            
            if guessInt == Int(randomNumber) {
                
                resultLabel.text = "Correct!"
                
            } else {
                
                resultLabel.text = "Nope! The answer is \(randomNumber)"
                
            }
            
        } else {
            
            resultLabel.text = "Please enter a number between 0 and 5"
            
        }
        
        println(guess.text)
        
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

