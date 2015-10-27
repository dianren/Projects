//
//  ViewController.swift
//  ShakeAndSwipe
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        var swipeRight = UISwipeGestureRecognizer(target: self, action: "swiped:")
        
        swipeRight.direction = UISwipeGestureRecognizerDirection.Right
        
        self.view.addGestureRecognizer(swipeRight)
        
        
        
        var swipeUp = UISwipeGestureRecognizer(target: self, action: "swiped:")
        
        swipeUp.direction = UISwipeGestureRecognizerDirection.Up
        
        self.view.addGestureRecognizer(swipeUp)
        
        
    }
    
    func swiped(gesture: UIGestureRecognizer) {
        
        if let swipeGesture = gesture as? UISwipeGestureRecognizer {
            
            
            switch swipeGesture.direction {
                
                case UISwipeGestureRecognizerDirection.Right:
                    println("User swiped Right")
                case UISwipeGestureRecognizerDirection.Up:
                    println("User swiped Up")
                default:
                    break
            }
        }
        
        
    }
    
    
    
    /// mobile action
    override func motionEnded(motion: UIEventSubtype, withEvent event: UIEvent) {
        
        if event.subtype == UIEventSubtype.MotionShake {
            
            println("User shook Their Device")
            
        }
        
    }
    
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

