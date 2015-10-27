//
//  ViewController.swift
//  Downloading Web Contents
//
//  Created by DIAN REN on 9/17/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var webView: UIWebView!
    
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        
        //////// these fews lines of code are extrmely important because we can use this to get web content and use it in our apps ////////
        
        let url = NSURL(string: "http://www.stackoverflow.com")
        
        let task = NSURLSession.sharedSession().dataTaskWithURL(url!, completionHandler: { (data, response, error) -> Void in
            
            if error == nil { // always check because url link may be null
                
                var urlContent = NSString(data: data, encoding: NSUTF8StringEncoding)
                
                println(urlContent)
                
                
                ///  if the network has delay, we should use queue to store the information 
                
                dispatch_async(dispatch_get_main_queue()) {
                    
                    self.webView.loadHTMLString(urlContent!, baseURL: nil)
                    
                }
                
            }
            
        })
        
        task.resume()
    }
    
///////////////////////////////////////////////////////////////////////////////////////////////////////

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

