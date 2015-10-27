/**
* Copyright (c) 2015-present, Parse, LLC.
* All rights reserved.
*
* This source code is licensed under the BSD-style license found in the
* LICENSE file in the root directory of this source tree. An additional grant
* of patent rights can be found in the PATENTS file in the same directory.
*/

import UIKit
import Parse




class ViewController: UIViewController {
    
    
    var activityIndicator: UIActivityIndicatorView = UIActivityIndicatorView()
    
    var signupActive = true

    
    @IBOutlet weak var username: UITextField!
    
    @IBOutlet weak var password: UITextField!
    
    @IBOutlet weak var signUpButton: UIButton! /// use for change button text
    
    @IBOutlet weak var registeredText: UILabel!
    
    @IBOutlet weak var loginButton: UIButton!
    
    
    
    
    
    
    //@available(iOS 8.0, *)
    func displayAlertMessage(title: String, message: String) {
        
        
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.Alert)
        
        
        alert.addAction(UIAlertAction(title: "OK", style: .Default, handler: { (action) -> Void in
            
            self.dismissViewControllerAnimated(true, completion: nil) // nil means we don not need something happen when it was finished
            
        }))
        
        self.presentViewController(alert, animated: true, completion: nil)
        
    }

    
    
    @IBAction func signUp(sender: AnyObject) {
        
        
        if username.text == "" || password.text == "" {
            
            displayAlertMessage("Error in form", message: "Please enter a username and password")
            
        } else {
            
            //////   create a spinner  ///////
            activityIndicator = UIActivityIndicatorView(frame: CGRectMake(0, 0, 50, 50))
            activityIndicator.center = self.view.center
            activityIndicator.hidesWhenStopped = true
            activityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyle.Gray
            view.addSubview(activityIndicator)
            activityIndicator.startAnimating()
            UIApplication.sharedApplication().beginIgnoringInteractionEvents()  // stop button
            
            
            var errorMessage = "Please try again later"
            
            if signupActive == true {/// means already sign up
            
            //////   sign up    ////////
                let user = PFUser()
                user.username = username.text
                user.password = password.text
            
                
            
                user.signUpInBackgroundWithBlock({ (success, error) -> Void in
                
                    self.activityIndicator.stopAnimating()
                    UIApplication.sharedApplication().endIgnoringInteractionEvents()  // active button again
                
                    if error == nil {
                    
                        /// sign up successfully
                        
                        self.performSegueWithIdentifier("login", sender: self) // sign up and will jump to other page
                    
                    
                    } else {
                    
                        if let errorString = error!.userInfo["error"] as? String {
                        
                            errorMessage = errorString
                        
                        }
                    
                        self.displayAlertMessage("Failed SignUp", message: errorMessage)
                    
                    }
                
                })
                
            } else {
                
                
                ///////////////////// log in /////////////////////////
                
                PFUser.logInWithUsernameInBackground(username.text!, password: password.text!, block: { (user, error) -> Void in
                    
                    self.activityIndicator.stopAnimating()
                    UIApplication.sharedApplication().endIgnoringInteractionEvents()  // active button again
                    
                    if user != nil {
                        
                        // logged in
                        self.performSegueWithIdentifier("login", sender: self) // sign up and will jump to other page
                        
                    } else {
                        
                        if let errorString = error!.userInfo["error"] as? String {
                            
                            errorMessage = errorString
                            
                        }
                        
                        self.displayAlertMessage("Failed Login", message: errorMessage)
                        
                    }
                    
                })
                
            }
            
        }
        
        
        
    }
    
    
    
    //////  change button text ///////////
    @IBAction func login(sender: AnyObject) {
        
        if signupActive == true {
            
            signUpButton.setTitle("Log In", forState: UIControlState.Normal)
            
            registeredText.text = "Not registered?"
            
            loginButton.setTitle("Sign Up", forState: UIControlState.Normal)
            
            signupActive = false
            
        } else {
            
            signUpButton.setTitle("Sign Up", forState: UIControlState.Normal)
            
            registeredText.text = "Already registered?"
            
            loginButton.setTitle("Log In", forState: UIControlState.Normal)
            
            signupActive = true
            
        }
        
    }
    
    
//    override func viewDidAppear(animated: Bool) {
//        
//        var currentUser = PFUser.currentUser()
//        
//        if currentUser != nil {
//            
//            self.performSegueWithIdentifier("login", sender: self)
//            
//        }
//    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        
    }
    
    
    
    
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
