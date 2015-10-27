//
//  ViewController.swift
//  Memorable Places
//
//  Created by DIAN REN on 9/20/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit
import MapKit


class ViewController: UIViewController, CLLocationManagerDelegate {

    @IBOutlet weak var map: MKMapView!
    
    
    var manager:CLLocationManager!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        manager = CLLocationManager()
        
        manager.delegate = self
        
        manager.desiredAccuracy = kCLLocationAccuracyBest

        
        if activePlace == -1 {/// 当表里面没有地址的时候
            
            manager.requestWhenInUseAuthorization()
            
            manager.startUpdatingLocation()
            
        } else {
            
            // string can not be convert to double, but NSString can. So, we should first convert string to NSString
            let latitude = NSString(string: places[activePlace]["latitude"]!).doubleValue
            
            let longitude = NSString(string: places[activePlace]["longitude"]!).doubleValue
            
            var latDelta:CLLocationDegrees = 0.01
            
            var lonDelta:CLLocationDegrees = 0.01
            
            var coordinate = CLLocationCoordinate2DMake(latitude, longitude)
            
            var span:MKCoordinateSpan = MKCoordinateSpanMake(latDelta, lonDelta)
            
            var region:MKCoordinateRegion = MKCoordinateRegionMake(coordinate, span)
            
            self.map.setRegion(region, animated: true)
            
            var annotation = MKPointAnnotation()
            
            annotation.coordinate = coordinate
            
            annotation.title = places[activePlace]["name"]
            
            self.map.addAnnotation(annotation)
            
        }
        
        
        
        
        
        
        
        
        
        
        
        /// long press action to store a user's location
        
        var uilpgr = UILongPressGestureRecognizer(target: self, action: "action:")
        
        uilpgr.minimumPressDuration = 1.5
        
        map.addGestureRecognizer(uilpgr)
    
    }
    
    func action(gestureRecognizer:UIGestureRecognizer) {
        
        // if a press is too long, we can add two or more locations. So, here is the code to handle this condition
        
        if gestureRecognizer.state == UIGestureRecognizerState.Began {// can sure only add one annotation
            
            var touchPoint = gestureRecognizer.locationInView(self.map)
            
            var newCoordinate = self.map.convertPoint(touchPoint, toCoordinateFromView: self.map)
            
            
            ///  show the address of annotition
            
            var location = CLLocation(latitude: newCoordinate.latitude, longitude: newCoordinate.longitude)
            
            CLGeocoder().reverseGeocodeLocation(location, completionHandler:  { (placemarks, error) -> Void in
                
                var title = ""
                
                if error == nil {
                    
                    if let p = CLPlacemark(placemark: placemarks?[0] as CLPlacemark) {
                        
                        var subThoroughfare:String = ""
                        
                        var thoroughfare:String = ""
                        
                        if p.subThoroughfare != nil {
                            
                            subThoroughfare = p.subThoroughfare
                            
                        }
                        
                        if p.thoroughfare != nil {
                            
                            thoroughfare = p.thoroughfare
                            
                        }
                        
                        title = "\(subThoroughfare) \(thoroughfare)"
                    }
                    
                    
                }
                
                if title == "" {
                    
                    title = "Added \(NSDate())"
                    
                }
                
                
                /// add this address to dictionary
                places.append(["name": title, "latitude": "\(newCoordinate.latitude)", "longitude": "\(newCoordinate.longitude)"])
                
                
                //// permanent storeage /////
                
                NSUserDefaults.standardUserDefaults().setObject(places, forKey: "dictionary") // each time should update NSUser
                
                
                
                var annotation = MKPointAnnotation()
                
                annotation.coordinate = newCoordinate
                
                annotation.title = title
                
                self.map.addAnnotation(annotation)
                
                
            })
            
            
        }
        
    }
    
    
    
    
    func locationManager(manager: CLLocationManager!, didUpdateLocations locations: [AnyObject]!) {
        
        var userLocation:CLLocation = locations[0] as CLLocation
        
        var latitude = userLocation.coordinate.latitude
        
        var longitude = userLocation.coordinate.longitude
        
        var latDelta:CLLocationDegrees = 0.01
        
        var lonDelta:CLLocationDegrees = 0.01
        
        var coordinate = CLLocationCoordinate2DMake(latitude, longitude)
        
        var span:MKCoordinateSpan = MKCoordinateSpanMake(latDelta, lonDelta)
    
        var region:MKCoordinateRegion = MKCoordinateRegionMake(coordinate, span)
        
        self.map.setRegion(region, animated: true)
    
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

