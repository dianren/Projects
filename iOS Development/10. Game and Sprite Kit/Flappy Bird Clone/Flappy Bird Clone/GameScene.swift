//
//  GameScene.swift
//  Flappy Bird Clone
//
//  Created by DIAN REN on 9/25/15.
//  Copyright (c) 2015 Appfish. All rights reserved.
//

import SpriteKit


///SKPhysicsContactDelegate  create a group of objects
class GameScene: SKScene, SKPhysicsContactDelegate{
    
    
    var score = 0
    var scoreLabel = SKLabelNode()
    
    var bird = SKSpriteNode()
    var bg = SKSpriteNode()
    
    let birdGroup:UInt32 = 1
    let objectGroup:UInt32 = 2
    
    var gameover = 0
    
    
    var movingObjects = SKNode()
    
    
    override func didMoveToView(view: SKView) {
        
        self.physicsWorld.contactDelegate = self
        
        self.physicsWorld.gravity = CGVectorMake(0, -5)
        
        self.addChild(movingObjects)
        ///  first create background then bird ///
        let bgTexture = SKTexture(imageNamed: "img/bg.png")
        
        let movebg = SKAction.moveByX(-bgTexture.size().width, y: 0, duration: 9)// this will move once
        let replacebg = SKAction.moveByX(bgTexture.size().width, y: 0, duration: 0)
        let movebgForever = SKAction.repeatActionForever(SKAction.sequence([movebg, replacebg]))

        
        for var i:CGFloat = 0; i < 3; i++ {
            
            bg = SKSpriteNode(texture: bgTexture)
            bg.position = CGPoint(x: bgTexture.size().width / 2 + bgTexture.size().width * i, y: CGRectGetMidY(self.frame))
            bg.size.height = self.frame.height
            
            // backgroud moving
            bg.runAction(movebgForever)
            
            movingObjects.addChild(bg)
            
        }
        
        
        
        
        
        
        let birdTexture1 = SKTexture(imageNamed: "img/flappy1.png")
        let birdTexture2 = SKTexture(imageNamed: "img/flappy2.png")
        
        let animation = SKAction.animateWithTextures([birdTexture1, birdTexture2], timePerFrame: 0.1)
        let makeBirdFlap = SKAction.repeatActionForever(animation)
        bird = SKSpriteNode(texture: birdTexture1)
        bird.position = CGPoint(x: CGRectGetMidX(self.frame), y: CGRectGetMidY(self.frame))
        bird.runAction(makeBirdFlap)
        
        // fall down ///
        bird.physicsBody = SKPhysicsBody(circleOfRadius: bird.size.height / 2)
        bird.physicsBody?.dynamic = true
        bird.physicsBody?.allowsRotation = false
        bird.physicsBody?.categoryBitMask = birdGroup
        //bird.physicsBody?.collisionBitMask = objectGroup
        bird.physicsBody?.contactTestBitMask = objectGroup
        bird.physicsBody?.collisionBitMask = gasGroup  // any objects with same collisionBitMask will not collite with eath other
        
        bird.zPosition = 10 /// default is 0
        
        self.addChild(bird)
        
        
        let ground = SKNode()
        ground.position = CGPointMake(0, 0) /// at bottom of screen
        ground.physicsBody = SKPhysicsBody(rectangleOfSize: CGSizeMake(self.frame.size.width, 1))
        ground.physicsBody?.dynamic = false
        ground.physicsBody?.categoryBitMask = objectGroup

        movingObjects.addChild(ground)
        
        
        var timer = NSTimer.scheduledTimerWithTimeInterval(6, target: self, selector: "makePipes", userInfo: nil, repeats: true)
    }
    
    
    func didBeginContact(contact: SKPhysicsContact) {
        print("contact")
        
        gameover = 1
        
        movingObjects.speed = 0
    }
    
    
    
    
    func makePipes() {
        
        if gameover == 0 {
        
        let gapHeight = bird.size.height * 4
        
        var heightAmount = arc4random() % UInt32(self.frame.size.height / 2)
        var pipeHeight = CGFloat(heightAmount) - self.frame.size.height / 4
        
        //// move pipe
        let movePipes = SKAction.moveByX(-self.frame.size.width * 2, y: 0, duration: NSTimeInterval(self.frame.size.width / 50))// this will move once
        
        var removePipes = SKAction.removeFromParent()
        let moveAndRemove = SKAction.sequence([movePipes, removePipes])
        
        //// add pipe /////
        let pipe1Texture = SKTexture(imageNamed: "img/pipe1.png")
        let pipe1 = SKSpriteNode(texture:pipe1Texture)
        pipe1.position = CGPoint(x: CGRectGetMidX(self.frame) + self.frame.size.width / 4, y: CGRectGetMidY(self.frame) + pipe1.size.height / 2 + gapHeight / 2 + pipeHeight)
        
        pipe1.zPosition = 5
        //print(pipe1.size.height / 2)
        pipe1.runAction(moveAndRemove)
        
        pipe1.physicsBody = SKPhysicsBody(rectangleOfSize: pipe1.size) /// create a physicsBody
        pipe1.physicsBody?.dynamic = false
        pipe1.physicsBody?.categoryBitMask = objectGroup
        movingObjects.addChild(pipe1)
        
        let pipe2Texture = SKTexture(imageNamed: "img/pipe2.png")
        let pipe2 = SKSpriteNode(texture:pipe2Texture)
        pipe2.position = CGPoint(x: CGRectGetMidX(self.frame) + self.frame.size.width / 4, y: CGRectGetMidY(self.frame) - pipe2.size.height / 2 - gapHeight / 2 + pipeHeight)
        
        pipe2.zPosition = 5
        pipe2.runAction(moveAndRemove)
        
        pipe2.physicsBody = SKPhysicsBody(rectangleOfSize: pipe2.size)
        pipe2.physicsBody?.dynamic = false
        pipe2.physicsBody?.categoryBitMask = objectGroup
        movingObjects.addChild(pipe2)
            
            
            var gap = SKNode()  /// gap between pipes
            gap.position = CGPoint(x: CGRectGetMidX(self.frame) + self.frame.size.width / 4, y: CGRectGetMidY(self.frame) + pipeHeight)
            gap.runAction(moveAndRemove)
            gap.physicsBody?.dynamic = false
            gap
            
        }

    }
    
    
    
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
       /* Called when a touch begins */
        
        
        if gameover == 0 {
            
            bird.physicsBody?.velocity = CGVectorMake(0, 0)
            bird.physicsBody?.applyImpulse(CGVectorMake(0, 50))
        }
        
    }
   
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
