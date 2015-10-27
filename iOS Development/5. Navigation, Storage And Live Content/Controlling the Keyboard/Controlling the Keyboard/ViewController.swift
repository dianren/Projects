//
//  ViewController.swift
//  Controlling the Keyboard
//
//  Created by DIAN REN on 9/17/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate { //  should inclue UITextFieldDelegate because we use the UITextField

    @IBOutlet weak var textField: UITextField!
    
    
    @IBOutlet weak var resultLabel: UILabel!
    
    
    @IBAction func pressButton(sender: AnyObject) {
        
        resultLabel.text = textField.text
        
    }
    
    
    // when user touch outside the keyboard, the keyboard will down
    override func touchesBegan(touches: Set<UITouch>?, withEvent event: UIEvent?) {
        
        self.view.endEditing(true) // close the keyboard
        
    }
    
    //  when we touch the return button on the keyboard, the keyboard will down
    func textFieldShouldReturn(textF: UITextField!) -> Bool {
        
        textF.resignFirstResponder()
        
        return true
        
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.textField.delegate = self // 这个地方不太懂
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

