//
//  ViewController.swift
//  Core Data Demo
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit
import CoreData



class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        // setting the context for us to access the database
        var appDel:AppDelegate = UIApplication.sharedApplication().delegate as AppDelegate
        
        var context:NSManagedObjectContext = appDel.managedObjectContext!
        
        
//        var newUser = NSEntityDescription.insertNewObjectForEntityForName("Users", inManagedObjectContext: context) as NSManagedObject
//        
//        
//        // give some data
//        newUser.setValue("Sindy", forKey: "username")
//        
//        newUser.setValue("pass2", forKey: "password")
//        
//        context.save(nil)
        
        
        
        
        // bring back data from database
        var request = NSFetchRequest(entityName: "Users")
        
        request.returnsObjectsAsFaults = false
        
        
        /// predicate is something like a searching, like "username".  "%@" means give something to username
        request.predicate = NSPredicate(format: "username = %@", "Tony") // search for someone
        
        
        var results = context.executeFetchRequest(request, error: nil)
        
        
        /// the answer has many meta data which we do not need. We should process the data
        if results?.count > 0 {
            
            println(results)
        
            for result: AnyObject in results! {
                
                /// a method to handle "optional"
                if let user = result.valueForKey("username") as? String {
                    
                    
                    
                    if user == "Tony" {
                        
                        /// remove item
//                        context.deleteObject(result as NSManagedObject)
//                        
//                        println(user + " has been deleted")
                        
                        
                        /// change something 
                        result.setValue("pass6", forKey: "password")
                        
                        
                    }
                    
                }
                context.save(nil)
                
            }
            
        } else {
            
            println("No results")
            
        }
        
        
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

