//
//  ViewController.swift
//  Map Demo
//
//  Created by DIAN REN on 9/19/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//




// Part 3: get User's location.
// step1: click rightmost named "Map Demo"
// step2: click "Build Phases"
// step3: click "Link Binary With Libraries", click " + "
// step4: search "location", and choose "CoreLocation.framework" and add
// step5: click rightmost named "Supporting Files" and click "info.plist". Now we can see a list
// step6: at "Main storyboard file base name", we click "+" in order to add two more key-value pairs
// step7: add key as " NSLocationWhenInUseUsageDescription" and add value as "Because I want to know where you are!"
// step8: add one more, add key as "NSLocationAlwaysUsageDescription" and add value as "because I always want to know where you are"

// step9: The difference between above two is that the first one means you ask permitation for user's location when the app is running. The second one means you ask for user's location whenever you wanted. So the second one, you really need be offered some navigation features or something really require their loacations in the background.






import UIKit
import MapKit   // control map view
import CoreLocation // identify user's location, the content of part3

class ViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate {

    @IBOutlet weak var map: MKMapView!
    
    
    // Part 3: get user's location ////////////////////////////
    
    
    var locationManager = CLLocationManager()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        
        /// a few setting
        locationManager.delegate = self  // means viewController gives to locationManage.delegate
        
        locationManager.desiredAccuracy = kCLLocationAccuracyBest // with the GPS
        
        locationManager.requestWhenInUseAuthorization() // when the app is running, you request
        
        locationManager.startUpdatingLocation() ///update the user's location
        
        
        
        
        
        
        
        
     ////// first part, using map /////////////////
        
        //  note the type, can not use float, should use CLLocationDegrees
        var latitude:CLLocationDegrees = 37.390094 // 纬度
        
        var longitude:CLLocationDegrees = -122.083522  // 经度
        
        var latDelta:CLLocationDegrees = 0.001  //Delta means the latitude difference between one side screen and other, means zoom screen
        
        //越大， 比如1， 你就会站在更高看，看总体轮廓。 越小， 你就看的越细节
        
        var lonDelta:CLLocationDegrees = 0.001
        
        var span:MKCoordinateSpan = MKCoordinateSpanMake(latDelta, lonDelta) // composed of latDelta and lonDelta
        
        var location:CLLocationCoordinate2D = CLLocationCoordinate2DMake(latitude, longitude) // composed of latitude and longitude
        
        var region:MKCoordinateRegion = MKCoordinateRegionMake(location, span) // composed of location and span
        
        map.setRegion(region, animated: false)
        
        
        
        
        //////// second part, add annotation ////////////////////
        
        var annotation = MKPointAnnotation()
        
        annotation.coordinate = location
        
        annotation.title = "Mountain view Public Labary"
        
        annotation.subtitle = "One day I'll go there..."
        
        map.addAnnotation(annotation)
        
        
        
        //////// A user can use long press will create a annotation  ////////////
        
        
        // self : means viewController
        // It's "action:", not "action". Because when this called, if it does not has ":", the function action will called without object sending in. With ":", when action called, the object will send in.
        // 冒号： colon； 逗号： comma； 分号：semicolon
        
        var uilpgr = UILongPressGestureRecognizer(target: self, action: "action:") // long press action
        
        uilpgr.minimumPressDuration = 2  // minimum time should press
        
        map.addGestureRecognizer(uilpgr)
        
        
    }
    
    
    // gestureRecognizer as an object will send in this function, it type is UIGestureRecognizer
    func action(gestureRecognizer: UIGestureRecognizer) {
        
        println("Gesture Recognize")
        
        var touchPoint = gestureRecognizer.locationInView(self.map)
        
        var newCoordinate:CLLocationCoordinate2D = map.convertPoint(touchPoint, toCoordinateFromView: self.map)
        
        
        // add annotation
        var annotation = MKPointAnnotation()
        
        annotation.coordinate = newCoordinate
        
        annotation.title = "New Place"
        
        annotation.subtitle = "One day I'll go there..."
        
        map.addAnnotation(annotation)
    }
    
    
    /// a function of part 3 ///
    func locationManager(manager: CLLocationManager!, didUpdateLocations locations: [AnyObject]!) {
        
        println(locations)
        
        var userLocation:CLLocation = locations[0] as CLLocation
        
        var latitude = userLocation.coordinate.latitude
        
        var longitude = userLocation.coordinate.longitude
        
        
        
        /// this part is same as first part ///
        
        var latDelta:CLLocationDegrees = 0.001  //Delta means the latitude difference between one side screen and other, means zoom screen
        
        //越大， 比如1， 你就会站在更高看，看总体轮廓。 越小， 你就看的越细节
        
        var lonDelta:CLLocationDegrees = 0.001
        
        var span:MKCoordinateSpan = MKCoordinateSpanMake(latDelta, lonDelta) // composed of latDelta and lonDelta
        
        var location:CLLocationCoordinate2D = CLLocationCoordinate2DMake(latitude, longitude) // composed of latitude and longitude
        
        var region:MKCoordinateRegion = MKCoordinateRegionMake(location, span) // composed of location and span
        
        self.map.setRegion(region, animated: false)
        
        

    }
    
    
    
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

