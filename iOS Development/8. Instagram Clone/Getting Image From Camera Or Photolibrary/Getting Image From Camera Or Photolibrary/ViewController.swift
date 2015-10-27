//
//  ViewController.swift
//  Getting Image From Camera Or Photolibrary
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit


/// UINavigationControllerDelegate, UIImagePickerControllerDelegate from camera or photoLibrary
class ViewController: UIViewController, UINavigationControllerDelegate, UIImagePickerControllerDelegate {
    
    
    

    @IBAction func importImage(sender: AnyObject) {
        
        var image = UIImagePickerController()  // actually is a view controller allows user to get out of app to pick up image from camera or photoLibrary
        
        image.delegate = self
        
        image.sourceType = UIImagePickerControllerSourceType.PhotoLibrary  // choose from camera or photoLibrary
        
        image.allowsEditing = false
        
        self.presentViewController(image, animated: true, completion: nil)
        
        
    }
    
    
    
    /// this function is called as soon as importImage function finished and image has been chosen by a user
    /// this function is used to display the image on the imageView and show it to user
    func imagePickerController(picker: UIImagePickerController!, didFinishPickingImage image: UIImage!, editingInfo: [NSObject : AnyObject]!) {
        
        println("Image Selected")
        
        self.dismissViewControllerAnimated(true, completion: nil)  //  ger rid of UIImagePickerController() which created
        
        importedImage.image = image
    }
    
    
    @IBOutlet weak var importedImage: UIImageView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

