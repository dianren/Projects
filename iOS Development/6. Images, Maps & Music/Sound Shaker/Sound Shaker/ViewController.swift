//
//  ViewController.swift
//  Sound Shaker
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {
    
    var player:AVAudioPlayer = AVAudioPlayer()
    
    var sounds = ["Lucky", "Everytime", "Heart", "jude", "OneInAMillion", "Woman"]
    
    
    @IBOutlet weak var shakeLabel: UILabel!
    
    
   

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        
        
    }
    
    
    override func motionEnded(motion: UIEventSubtype, withEvent event: UIEvent) {
        
        if event.subtype == UIEventSubtype.MotionShake {
            
            var randomNumber = Int(arc4random_uniform(UInt32(sounds.count)))
            
            var audioPath = NSURL(fileURLWithPath: NSBundle.mainBundle().pathForResource(sounds[randomNumber], ofType: "mp3")!)
            
            var error:NSError? = nil
            
            player = AVAudioPlayer(contentsOfURL: audioPath, error: &error)
            
            player.play()
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

