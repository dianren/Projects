//
//  ViewController.swift
//  Audio
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

import AVFoundation



class ViewController: UIViewController {
    
    var player:AVAudioPlayer = AVAudioPlayer()
    

    @IBAction func play(sender: AnyObject) {
        
        
        var audioPath = NSURL(fileURLWithPath: NSBundle.mainBundle().pathForResource("HeyJude", ofType: "mp3")!)
        
        var error:NSError? = nil
        
        
        // NSURL  means change string to NSURL
        // & means pointer to error
        
        player = AVAudioPlayer(contentsOfURL: audioPath, error: &error)
        
        if error == nil {
            
            player.play()
            
        } else {
            
            println(error)
            
        }
        
    }
    
    
    @IBAction func pause(sender: AnyObject) {
        
        player.pause()
        
        
    }
    
    
    @IBAction func sliderChanges(sender: AnyObject) {
        
        player.volume = sliderValue.value  ///between (0, 1)
        
    }
    
    
    @IBOutlet weak var sliderValue: UISlider!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

