//
//  ViewController.swift
//  What's The Weather
//
//  Created by DIAN REN on 9/18/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {
    
    
    @IBOutlet weak var myCity: UITextField!
    
    
    @IBOutlet weak var resultLabel: UILabel!
    
    
    
    @IBAction func clearButton(sender: AnyObject) {
        
        myCity.text = ""
        
        resultLabel.text = ""
        
        
    }
    
    
    
    
    
    
    
    @IBAction func findWeather(sender: AnyObject) {
        
        
        var url = NSURL(string: "http://www.weather-forecast.com/locations/" + myCity.text.stringByReplacingOccurrencesOfString(" ", withString: "-") + "/forecasts/latest")
        
        if url != nil {
            
            let task = NSURLSession.sharedSession().dataTaskWithURL(url!, completionHandler: { (data, response, error) -> Void in
                
                var weather = ""
                
                var urlError = false
                
                if error == nil {
                    
                    var urlContent = NSString(data: data, encoding: NSUTF8StringEncoding) as NSString!
                    
                    //println(urlContent)
                    
                    var urlContentArray = urlContent.componentsSeparatedByString("<span class=\"phrase\">")
                    
                    if urlContentArray.count > 0 {
                        
                        var weatherArray = urlContentArray[1].componentsSeparatedByString("</span>")
                        
                        weather = weatherArray[0] as String
                        
                        weather = weather.stringByReplacingOccurrencesOfString("&deg;", withString: "°")
                        
                    } else {
                        
                        urlError = true
                        
                    }
                    
                    
                    
                } else {
                    
                    urlError = true
                    
                }
                
                
                
                dispatch_async(dispatch_get_main_queue()) {
                    
                    if urlError == true {
                        
                        self.showError()
                        
                    } else {
                        
                        self.resultLabel.text = weather
                        
                    }
                    
                }
                
                
                
            })
            
            task.resume()
            
            
        } else {
            
            
            showError()
            
        }

        
        
        
    }
    
    
    
    func showError() {
        
        
        resultLabel.text = "Can not find the weather of " + myCity.text + ". Please try again!"
        
    }
    
    
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        
        self.view.endEditing(true)
        
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        
        myCity.resignFirstResponder()
        
        return true
        
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

