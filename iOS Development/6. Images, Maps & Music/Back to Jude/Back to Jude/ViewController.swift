//
//  ViewController.swift
//  Back to Jude
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {
    
    
    var player:AVAudioPlayer = AVAudioPlayer()
    
    
    
    
    
    
    
    @IBOutlet weak var playLabel: UIBarButtonItem!

    @IBAction func playAction(sender: AnyObject) {
        
        
            player.play()
        
        
        
    }
    
    
    @IBOutlet weak var sliderValue: UISlider!
    
    @IBAction func sliderChanges(sender: AnyObject) {
        
        player.volume = sliderValue.value
        
        
    }
    
    
    @IBAction func pauseAction(sender: AnyObject) {
        
        player.pause()
        
    }
    
    
    
    @IBAction func stopAction(sender: AnyObject) {
        
        player.stop()
        
        player.currentTime = 0
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        var audioPath = NSURL(fileURLWithPath: NSBundle.mainBundle().pathForResource("Jude", ofType: "mp3")!)
        
        var error:NSError? = nil
        
        
        // NSURL  means change string to NSURL
        // & means pointer to error
        
        player = AVAudioPlayer(contentsOfURL: audioPath, error: &error)
        
        
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

