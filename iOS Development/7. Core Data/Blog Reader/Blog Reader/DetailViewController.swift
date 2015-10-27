//
//  DetailViewController.swift
//  Blog Reader
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {

    

    @IBOutlet weak var webview: UIWebView!

    var detailItem: AnyObject? {
        didSet {
            // Update the view.
            self.configureView()
        }
    }

    func configureView() {
        // Update the user interface for the detail item.
        if let detail: AnyObject = self.detailItem {
            if let wv = self.webview {
                
                // load html content
                wv.loadHTMLString(detail.valueForKey("content")!.description, baseURL: nil)
                
            }
        }

               
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.configureView()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

