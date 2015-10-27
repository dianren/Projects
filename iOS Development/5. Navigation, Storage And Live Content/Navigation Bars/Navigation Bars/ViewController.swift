//
//  ViewController.swift
//  Navigation Bars
//
//  Created by DIAN REN on 9/16/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var countingLabel: UITextField!
    
    @IBAction func clearButton(sender: AnyObject) {
        elapsedTime = 0
        
        timer.invalidate()
        
        startTime = NSDate.timeIntervalSinceReferenceDate()
        
        countingLabel.text = "00:00:00"
    
    }
    
    @IBAction func playButton(sender: AnyObject) {
            startTime = NSDate.timeIntervalSinceReferenceDate()
            timer = NSTimer.scheduledTimerWithTimeInterval(0.01, target: self, selector: Selector("updateTime"), userInfo: nil, repeats: true)
            //startTime = NSDate.timeIntervalSinceReferenceDate()
            
    }
    
    @IBAction func pauseButton(sender: AnyObject) {
        elapsedTime = 0
        
        timer.invalidate()
        
    }
    
    var timer = NSTimer()
    
    var startTime = NSTimeInterval()
    
    var elapsedTime = NSTimeInterval()
    
    func updateTime() {
        
        //Find the difference between current time and start time.
        
        var currentTime = NSDate.timeIntervalSinceReferenceDate()
        
        var elapsedTime:NSTimeInterval = currentTime - startTime
        
        //calculate the minutes in elapsed time.
        
        let minutes = UInt8(elapsedTime / 60.0)
        
        elapsedTime -= NSTimeInterval(minutes) * 60
        
        //calculate the seconds in elapsed time.
        
        let seconds = UInt8(elapsedTime)
        
        elapsedTime -= NSTimeInterval(seconds)
        
        //find out the fraction of milliseconds to be displayed
        
        let fraction = UInt8(elapsedTime * 60)
        
        //add the leading zero for minutes, seconds and millseconds and store them as string constants
        
        let strMinutes = String(format: "%02d", minutes)
        
        let strSeconds = String(format: "%02d", seconds)
        
        let strFraction = String(format: "%02d", fraction)
        
        countingLabel.text = "\(strMinutes):\(strSeconds):\(strFraction)"
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

