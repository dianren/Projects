//
//  TableViewController.swift
//  ParseStarterProject-Swift
//
//  Created by DIAN REN on 9/21/15.
//  Copyright (c) 2015 Parse. All rights reserved.
//

import UIKit
import Parse



class TableViewController: UITableViewController {
    
    var usernames = [""]
    var userids = [""]
    var isFollowing = ["":false] /// use a dictionary to traverse the order
    
    var refresher: UIRefreshControl!
    
    
    
    func refresh() {
        
        
        
        /////////////////////// following part ///////////////////////////////
        /////////////////////////////////////////////////////////////////////
        
        var query = PFUser.query()!
        query.orderByAscending("username") /// one constraint
        
        query.findObjectsInBackgroundWithBlock ({ (objects: [AnyObject]?, error: NSError?) -> Void in
            
            
            if let users = objects {
                
                self.usernames.removeAll(keepCapacity: true)
                self.userids.removeAll(keepCapacity: true)
                self.isFollowing.removeAll(keepCapacity: true)
                
                for object in users {
                    
                    
                    if let user = object as? PFUser {
                        
                        // can not let current user in
                        if user.objectId != PFUser.currentUser().objectId {
                            
                            self.usernames.append(user.username!)
                            self.userids.append(user.objectId!)
                            
                            
                            var query = PFQuery(className: "followers")
                            
                            query.whereKey("follower", equalTo: PFUser.currentUser()!.objectId!)// one constraint
                            query.whereKey("following", equalTo: user.objectId!)// another constraint
                            
                            query.findObjectsInBackgroundWithBlock({ (objects, error) -> Void in
                                
                                if let objects = objects { // 这里只是检测了是否存在， objects 是 AnyObjects
                                    
                                    if objects.count > 0 {
                                        
                                        self.isFollowing[user.objectId!] = true
                                        
                                    } else {
                                        
                                        self.isFollowing[user.objectId!] = false
                                        
                                    }
                                    
                                }
                                
                                if self.isFollowing.count == self.usernames.count {
                                    
                                    self.tableView.reloadData()
                                    
                                    self.refresher.endRefreshing()
                                    
                                }
                                
                            })
                            
                            
                            
                        }
                        
                    }
                    
                }
                
            }
            
        })

        
        
    }
    
    
    
    

    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        ///////////////////// refresh through down polling //////////////////
        /////////////////////////////////////////////////////////////////////
        refresher = UIRefreshControl()
        
        refresher.attributedTitle = NSAttributedString(string: "Pull to refresh")
        
        refresher.addTarget(self, action: "refresh", forControlEvents: UIControlEvents.ValueChanged)
        
        self.tableView.addSubview(refresher)
        
        refresh()
        
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK: - Table view data source

    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        // #warning Potentially incomplete method implementation.
        // Return the number of sections.
        return 1
    }

    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete method implementation.
        // Return the number of rows in the section.
        return usernames.count
    
    }

    
    
    /// create a table ////
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as UITableViewCell

        cell.textLabel?.text = usernames[indexPath.row]
        
        let followedObjectId = userids[indexPath.row]
        
        if isFollowing[followedObjectId] == true {
            
            cell.accessoryType = UITableViewCellAccessoryType.Checkmark
            
        }
        
        return cell
    }
    
 
    
    /// this function is you select a row, it will excute this row, 这个方程很重要！！！！/////
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
    
        var cell:UITableViewCell = tableView.cellForRowAtIndexPath(indexPath)!
        
        let followedObjectId = userids[indexPath.row]
        
        if isFollowing[followedObjectId] == false {
            
            isFollowing[followedObjectId] = true
            /////  paint a mark, 就是被关注的打个钩 ////
            
            cell.accessoryType = UITableViewCellAccessoryType.Checkmark /// mark a check
        
            /// update the following ////
            var following = PFObject(className: "followers")
            following["following"] = userids[indexPath.row]
            following["follower"] = PFUser.currentUser()?.objectId
            following.saveInBackground()
        
            
        } else {
            
            isFollowing[followedObjectId] = false
            
            cell.accessoryType = UITableViewCellAccessoryType.None /// cancle a mark
            ////  delete a follow
            var query = PFQuery(className: "followers")
            
            query.whereKey("follower", equalTo: PFUser.currentUser()!.objectId!)// one constraint
            query.whereKey("following", equalTo: userids[indexPath.row])// another constraint
            
            query.findObjectsInBackgroundWithBlock({ (objects, error) -> Void in
                
                if let objects = objects { // 这里只是检测了是否存在， objects 是 AnyObjects
                    
                    for object in objects {
                        
                        object.deleteInBackground()
                        
                    }
                }
                
            })
            
        }
        
        
        
    }


}



