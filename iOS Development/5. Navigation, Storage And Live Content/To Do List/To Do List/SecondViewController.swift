//
//  SecondViewController.swift
//  To Do List
//
//  Created by DIAN REN on 9/17/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class SecondViewController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var addText: UITextField!
    
    @IBAction func addButton(sender: AnyObject) {
        
        toDoList.append(addText.text)
        
        addText.text = "" // after add one, clear, then can add one more
        
        
        // permanent storeage
        NSUserDefaults.standardUserDefaults().setObject(toDoList, forKey: "toDoList") // each time should update NSUser
    }
    
    
    
    /////  keyboard down  feactures ////////////
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        
        self.view.endEditing(true)
        
    }
    
    func textFieldShouldReturn(textField: UITextField!) -> Bool {
        
        addText.resignFirstResponder()
        
        return true
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.addText.delegate = self
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    
}

