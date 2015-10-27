//
//  ViewController.swift
//  Animations
//
//  Created by DIAN REN on 9/18/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    
    var counter = 1

    @IBOutlet weak var alienImage: UIImageView!
    
    
    @IBAction func updateImage(sender: AnyObject) {
        
        if (counter == 2) {
            
            counter = 1
            
        } else {
        
            counter++
            
        }
        
        alienImage.image = UIImage(named: "frame\(counter).png")
        
        
        
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
