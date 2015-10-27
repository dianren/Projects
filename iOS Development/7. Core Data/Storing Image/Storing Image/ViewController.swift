//
//  ViewController.swift
//  Storing Image
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    
    @IBOutlet weak var zhaoyun: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
       // download image from internet
       let url = NSURL(string: "http://images.panjk.com/a1/images/201504/20150402145526475.jpg")
        
       let urlRequest = NSURLRequest(URL: url!)
        
       
        //Asynchronous means if we write some code under the "})", these codes may happen before this request completed.
        //but the code in this request only run when the request completed
       NSURLConnection.sendAsynchronousRequest(urlRequest, queue: NSOperationQueue.mainQueue(), completionHandler: {
            response, data, error in
        
          if error != nil {
            
               println("There was an error")
            
           } else {
            
                let image = UIImage(data: data)
            
               //self.zhaoyun.image = image
            
            
            
        /////////// find a location to store our image       ///////////
            
                var documentDirectory:String?
            
                // return an array of the paths of folders that we can us store the documents in.  Normally only one value
                var paths:[AnyObject] = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true)
            
                if paths.count > 0 {
                   
                    documentDirectory = paths[0] as? String
                    
                    var savePath = documentDirectory! + "/zhaoyun.jpg"
                   
                    NSFileManager.defaultManager().createFileAtPath(savePath, contents: data, attributes: nil) // save the image
                    
                   self.zhaoyun.image = UIImage(named: savePath)
               }
            }
        
        
       })
        
        
        
        
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

