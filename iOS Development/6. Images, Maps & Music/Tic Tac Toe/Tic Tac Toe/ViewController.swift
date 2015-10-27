//
//  ViewController.swift
//  Tic Tac Toe
//
//  Created by DIAN REN on 9/18/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    // 1 : nought    2: cross
    
    var activePlayer = 1
    
    var gameActive = true
    
    var gameState = [0, 0, 0, 0, 0, 0, 0, 0, 0]
    
    var winningCombinations = [[0, 1, 2], [3, 4, 5], [6, 7, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 4, 8], [2, 4, 6]]
    
    @IBOutlet weak var resultLabel: UILabel!
    
    @IBOutlet weak var plagAgainLabel: UIButton!
    
    @IBAction func playAgain(sender: AnyObject) {
        
        // grid state become to original
        
        activePlayer = 1
        
        gameActive = true
        
        gameState = [0, 0, 0, 0, 0, 0, 0, 0, 0]
        
        
        // reset 9 buttons to empty image, we use tags  //
        
        var button : UIButton
        
        
        /* 因为我们从0开始，就会有tag(0)，但是所有得button的default tag都是0， 所以不知道你确切指的哪个
            所以我们要改变button的 default tag*///
        
        for var i = 0; i < 9; i++ {
            
            button = view.viewWithTag(i) as UIButton!
        
            button.setImage(nil, forState: .Normal)
            
        }
        
        
        resultLabel.hidden = true
        
        plagAgainLabel.hidden = true
        
        
        resultLabel.center = CGPointMake(resultLabel.center.x - 400, resultLabel.center.y)
        
        plagAgainLabel.center = CGPointMake(plagAgainLabel.center.x - 400, plagAgainLabel.center.y)
    }

    @IBOutlet var button: UIButton!
    
    
    @IBAction func buttonPressed(sender: AnyObject) {
        
        
        
        if gameState[sender.tag] == 0  && gameActive == true {
            
            var image = UIImage()
        
            gameState[sender.tag] = activePlayer
        
            if activePlayer == 1 {
        
                image = UIImage(named: "nought.png")!
            
                activePlayer = 2
            
            } else {
            
                image = UIImage(named: "cross.png")!
            
                activePlayer = 1

            }
            
            sender.setImage(image, forState: .Normal)
            
            
            
            for comb in winningCombinations {
                
                if gameState[comb[0]] != 0 && gameState[comb[0]] == gameState[comb[1]] && gameState[comb[1]] == gameState[comb[2]] {
                    
                    
                    if gameState[comb[0]] == 1 {
                        
                        resultLabel.text = "noughts has won"
                        
                    } else {
                        
                        resultLabel.text = "cross has won"
                        
                    }
                    
                    
                    
                    ///// when the game is over, the winning image will apear and the playAgain button also will apear
                    
                    resultLabel.hidden = false
                    
                    plagAgainLabel.hidden = false

                    
                    UIView.animateWithDuration(0.5, animations: { () -> Void in
                        
                        self.resultLabel.center = CGPointMake(self.resultLabel.center.x + 400, self.resultLabel.center.y)
                        
                        self.plagAgainLabel.center = CGPointMake(self.plagAgainLabel.center.x + 400, self.plagAgainLabel.center.y)
                        
                    })
                    
                    gameActive = false
                    
                    break
                    
                }
            }
            
            

            
        }
        
        // if this condition, will perform the first one : button.setImage(image, forState: .Normal)
        
    }
    
    
    // original it hide, when you call it, it will appear
    override func viewDidLayoutSubviews() {
        
        
        
    }
    
    
    
    
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        resultLabel.hidden = true
        
        plagAgainLabel.hidden = true
        
        
        resultLabel.center = CGPointMake(resultLabel.center.x - 400, resultLabel.center.y)
        
        plagAgainLabel.center = CGPointMake(plagAgainLabel.center.x - 400, plagAgainLabel.center.y)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

