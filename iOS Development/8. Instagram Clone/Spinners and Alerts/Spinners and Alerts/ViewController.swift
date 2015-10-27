//
//  ViewController.swift
//  Spinners and Alerts
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    var activityIndicator: UIActivityIndicatorView = UIActivityIndicatorView()

    
    //// create a spinner ////

    @IBAction func pause(sender: AnyObject) {
        
        activityIndicator = UIActivityIndicatorView(frame: CGRectMake(0, 0, 50, 50))

        activityIndicator.center = self.view.center  // put in the view controller center
        
        activityIndicator.hidesWhenStopped = true
        
        activityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyle.Gray
        
        view.addSubview(activityIndicator)  // 显示圈圈
        
        activityIndicator.startAnimating()
        
        
        /// this line can let all the buttons stop working
        //UIApplication.sharedApplication().beginIgnoringInteractionEvents()
        
    }
    
    @IBAction func restore(sender: AnyObject) {
        
        
        
        activityIndicator.stopAnimating()
        
        
        //UIApplication.sharedApplication().endIgnoringInteractionEvents()
        
    }
    
    
    ///// create a alert   /////
    @IBAction func alert(sender: AnyObject) {
        
        var alert = UIAlertController(title: "Hey there", message: "Are you sure", preferredStyle: UIAlertControllerStyle.Alert)
        
        
        // add a action to it
        alert.addAction(UIAlertAction(title: "OK", style: .Default, handler:  { (action) -> Void in
            
           self.dismissViewControllerAnimated(true, completion: nil)
            
            
        }))
        
        self.presentViewController(alert, animated: true, completion: nil) // present alert
        
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

