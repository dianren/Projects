//
//  ViewController.swift
//  Web View Demo
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var webview: UIWebView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
    /*
        var url = NSURL(string: "http://www.google.com")
        
        var request = NSURLRequest(URL:url!)
        
        webview.loadRequest(request)
      */
        
        
        
        /// from html
        
        var html = "<html><head></head><body><h1>Hello World!</h1></body></html>"
        
        webview.loadHTMLString(html, baseURL: nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

