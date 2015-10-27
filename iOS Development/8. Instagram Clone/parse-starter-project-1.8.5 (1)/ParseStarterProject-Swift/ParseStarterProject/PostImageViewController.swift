//
//  PostImageViewController.swift
//  ParseStarterProject-Swift
//
//  Created by DIAN REN on 9/22/15.
//  Copyright (c) 2015 Parse. All rights reserved.
//

import UIKit
import Parse



class PostImageViewController: UIViewController, UINavigationControllerDelegate, UIImagePickerControllerDelegate, UITextFieldDelegate {
    
    
    func displayAlertMessage(title: String, message: String) {
        
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.Alert)
        
        alert.addAction(UIAlertAction(title: "OK", style: .Default, handler: { (action) -> Void in
            
            self.dismissViewControllerAnimated(true, completion: nil) // nil means we don not need something happen when it was finished
            
        }))
        
        self.presentViewController(alert, animated: true, completion: nil)
        
    }

    
    /// should need a activityIndicator to show the user uploadded
    var activityIndicator = UIActivityIndicatorView()
    
    
    

    @IBOutlet weak var imageToPost: UIImageView!
    
    @IBAction func chooseImage(sender: AnyObject) {
        
        let image = UIImagePickerController()  // actually is a view controller allows user to get out of app to pick up image from camera or photoLibrary
        
        image.delegate = self
        
        image.sourceType = UIImagePickerControllerSourceType.PhotoLibrary  // choose from camera or photoLibrary
        
        image.allowsEditing = false
        
        self.presentViewController(image, animated: true, completion: nil)
        
    }
    
    
    
    func imagePickerController(picker: UIImagePickerController!, didFinishPickingImage image: UIImage!, editingInfo: [NSObject : AnyObject]!) {
        
        self.dismissViewControllerAnimated(true, completion: nil)
        
        imageToPost.image = image
    }
    
    @IBOutlet weak var textField: UITextField!
    
    
    @IBAction func postImage(sender: AnyObject) {
        
        
        ///  show the spinners
        activityIndicator = UIActivityIndicatorView(frame: self.view.frame) //  show whole screen
        activityIndicator.backgroundColor = UIColor(white: 1.0, alpha: 0.5) // alpha means how transparent
        activityIndicator.center = self.view.center
        activityIndicator.hidesWhenStopped = true
        activityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyle.Gray
        view.addSubview(activityIndicator)
        activityIndicator.startAnimating()
        
        UIApplication.sharedApplication().beginIgnoringInteractionEvents()
        
        
        
        let post = PFObject(className:  "Post") /// create a class
        
        post["text"] = textField.text // create a "text" object
        
        post["userId"] = PFUser.currentUser()!.objectId! // create a "userid" object
        
        /// change a image to a file ///
        let imageData = UIImagePNGRepresentation(imageToPost.image!)
        let imageFile = PFFile(name: "image.png", data: imageData!)
        
        post["imageFile"] = imageFile  // create a "imageFile" object
        
        post.saveInBackgroundWithBlock ({ (success, error) -> Void in
            
            self.activityIndicator.stopAnimating()
            
            UIApplication.sharedApplication().endIgnoringInteractionEvents()
            
            if error == nil {
                
                self.displayAlertMessage("Imaged Posted", message: "Your image has been posted successfully!")
                
                
                // improve user experience! when you post manys images, this will return to original when you post one
                self.imageToPost.image = UIImage(named: "empty-face.png")
                self.textField.text = ""
                
            } else {
                
                self.displayAlertMessage("Could not post image", message: "Please try again later!")
                
            }
            
            
        })
        
    }
    
    
    ////// control the keyboard
    override func touchesBegan(touches: Set<UITouch>?, withEvent event: UIEvent?) {
        
        self.view.endEditing(true)
        
    }
    
    func textFieldShouldReturn(textF: UITextField) -> Bool {
        
        textF.resignFirstResponder()
        
        return true
        
    }
    
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.textField.delegate = self
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
