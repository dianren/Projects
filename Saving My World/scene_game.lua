-- FILE: scene_game.lua
-- DESCRIPTION: allow the play the game


local composer = require( "composer" )

local scene = composer.newScene()


local widget = require "widget"
widget.setTheme ("widget_theme_ios7")


local physics = require "physics"  -- include physics library
physics.start() -- should be called before any physics function
physics.setGravity(0,0) -- set gravity of this object is x component is 0 and y is also 0




-- fighter
local fighterSheetData = {
    width = 179, 
    height = 190, 
    numFrames = 9, 
    sheetContentWidth = 1611, 
    sheetContentHeight = 190
}

local fighterSheet = graphics.newImageSheet("images/characters/fireman.png", fighterSheetData)

-- defines two animation 
local fighterSequenceData = { 
    {name = "fight", start = 1, count = 9, time = 700, loopCount = 1},
    
}


--------- the dragons ------------
local dragon1SheetData = {
    width = 332,
    height = 158,
    numFrames = 12,
    sheetContentWidth = 3984,
    sheetContentHeight = 158
}
local dragon1Sheet = graphics.newImageSheet("images/characters/dragon1.png", dragon1SheetData)
local dragon1SequenceData = {
    {name = "dragon1Flying", start = 1, count = 12, time = 700, loopCount = 0} -- 0 means infinity
}


local dragon2SheetData = {
    width = 198,
    height = 150,
    numFrames = 7,
    sheetContentWidth = 1386,
    sheetContentHeight = 150
}
local dragon2Sheet = graphics.newImageSheet("images/characters/dragon2.png", dragon2SheetData)
local dragon2SequenceData = {
    {name = "dragon2Flying", start = 1, count = 7, time = 700, loopCount = 0} -- 0 means infinity
}


local dragon3SheetData = {
    width = 400,
    height = 386,
    numFrames = 4,
    sheetContentWidth = 1600,
    sheetContentHeight = 386
}
local dragon3Sheet = graphics.newImageSheet("images/characters/dragon3.png", dragon3SheetData)
local dragon3SequenceData = {
    {name = "dragon3Flying", start = 1, count = 4, time = 700, loopCount = 0} -- 0 means infinity
}


local dragon4SheetData = {
    width = 390,
    height = 390,
    numFrames = 4,
    sheetContentWidth = 1560,
    sheetContentHeight = 390
}
local dragon4Sheet = graphics.newImageSheet("images/characters/dragon4.png", dragon4SheetData)
local dragon4SequenceData = {
    {name = "dragon4Flying", start = 1, count = 4, time = 700, loopCount = 0} -- 0 means infinity
}


local dragon5SheetData = {
    width = 220,
    height = 200,
    numFrames = 8,
    sheetContentWidth = 1760,
    sheetContentHeight = 200
}
local dragon5Sheet = graphics.newImageSheet("images/characters/dragon5.png", dragon5SheetData)
local dragon5SequenceData = {
    {name = "dragon5Flying", start = 1, count = 8, time = 700, loopCount = 0} -- 0 means infinity
}





-- last is poof
local poofSheetData = {
    width = 165,
    height = 180, 
    numFrames = 5,
    sheetContentWidth = 825,
    sheetContentHeight = 180
}

local poofSheet = graphics.newImageSheet("images/characters/poof.png", poofSheetData)

local poofSequenceData = {
    {name = "disapear", start = 1, count = 5, time = 250, loopCount = 1}
}



--- blood sheet ----
local bloodSheetData = {
    width = 165,
    height = 180, 
    numFrames = 6,
    sheetContentWidth = 990,
    sheetContentHeight = 180
}

local bloodSheet = graphics.newImageSheet("images/characters/blood.png", bloodSheetData)


-- -----------------------------------------------------------------------------------------------------------------
-- All code outside of the listener functions will only be executed ONCE unless "composer.removeScene()" is called.
-- -----------------------------------------------------------------------------------------------------------------

-- local forward references should go here
local lane = {} -- create a table that will hold four lanes

local player, tmr_playerShoot, playerMoney, playerGun
local playerShootSpeed = 1250 -- user.shootlevel * 100
local playerShootSpeedUp = 200
local playerEarnedMoney = 10 -- the money earned when a pirate was hit

local lives = {} -- create a table that can hold lives
local livesCount = 5

local bullets = {}
local bulletCounter = 0
local bulletTransition = {}
local bulletTransitionCounter = 0

local enemy = {}
local enemyCounter = 0
local enemySendSpeed = 75
local enemyTravelSpeed = 3500  -- how long enemies travel across the screen
local enemyIncrementSpeed = 1.5 
local enemyMaxSendSpeed = 20

local gun = {}
local gunCounter = 0
local gunTransition = {}
local gunTransitionCounter = 0

local poof = {}
local poofCounter = 0

local blood = {}


local timeCounter = 0
local gunSendingTimeCounter = 0
local tmr_speedUp
local pauseGame = false
local pauseBackground, button_pause, pauseText, pause_returnToMenu, pauseReminder

local onGameOver, gameOverBox, gameoverBackground, button_returnToMenu, button_speedUp
local isSpeedUp = false

local house1, house2, house3, house4
-- -------------------------------------------------------------------------------


-- "scene:create()"
function scene:create( event )

    local sceneGroup = self.view

    -- Initialize the scene here.
    -- Example: add display objects to "sceneGroup", add touch listeners, etc.
    local function returnToMenu(event) 
        if(event.phase == "ended") then
            audio.play(_CLICK)
            composer.gotoScene("scene_menu", "slideLeft")
        end

    end

    local function playerShoot()
        audio.play(_FIRE)
        bulletCounter = bulletCounter + 1
        bullets[bulletCounter] = display.newImageRect(sceneGroup, "images/characters/bullet.png", 24,8)
        bullets[bulletCounter].x = player.x - player.width / 2
        bullets[bulletCounter].y = player.y - 25
        bullets[bulletCounter].id = "bullet"
        physics.addBody(bullets[bulletCounter])
        sceneGroup:insert(bullets[bulletCounter])
        bullets[bulletCounter].isSensor = true

        --  time means from one side of screen to another side
        bulletTransition[bulletCounter] = transition.to(bullets[bulletCounter], {x = -200, time = 700, onComplete = function(self)
            if(self ~= nil) then
                display.remove(self)
            end
        end})


        -- perform ninja's motion
        player:setSequence("fight")
        player:play()

    end

    local function onLaneTouch(event)
        local index = event.target.id

        if (event.phase == "began") then
            transition.to(player, {y = lane[index].y, time = 100})
        end

    end



    local function sendEnemies()

        --print(timeCounter)
        --------------- send enemies --------------
        timeCounter = timeCounter + 1
        if(timeCounter % enemySendSpeed == 0) then
            enemyCounter = enemyCounter + 1
            enemySendSpeed = enemySendSpeed - enemyIncrementSpeed

            if(enemySendSpeed <= enemyMaxSendSpeed) then
                enemySendSpeed = enemyMaxSendSpeed
            end

            local temp = math.random(1, 5)
            if(temp == 1) then
                enemy[enemyCounter] = display.newSprite(dragon1Sheet, dragon1SequenceData)
            elseif(temp == 2) then
                enemy[enemyCounter] = display.newSprite(dragon2Sheet, dragon2SequenceData)
            elseif(temp == 3) then
                enemy[enemyCounter] = display.newSprite(dragon3Sheet, dragon3SequenceData)
            elseif(temp == 4) then
                enemy[enemyCounter] = display.newSprite(dragon4Sheet, dragon4SequenceData)
            elseif(temp == 5) then
                enemy[enemyCounter] = display.newSprite(dragon5Sheet, dragon5SequenceData)
            end

            enemy[enemyCounter].x = _LEFT - 50
            enemy[enemyCounter].y = lane[math.random(1, 4)].y
            enemy[enemyCounter].id = "enemy"
            physics.addBody(enemy[enemyCounter])
            enemy[enemyCounter].isFixedRotation = true
            sceneGroup:insert(enemy[enemyCounter])


            transition.to(enemy[enemyCounter], {x = _RIGHT + 50, time = enemyTravelSpeed, onComplete = function(self)
                if(self ~= nil) then
                    display.remove(self)
                end
            end})

            if(temp == 1) then
                enemy[enemyCounter]:setSequence("dragon1Flying")
            elseif(temp == 2) then
                enemy[enemyCounter]:setSequence("dragon2Flying")
            elseif(temp == 3) then
                enemy[enemyCounter]:setSequence("dragon3Flying")
            elseif(temp == 4) then
                enemy[enemyCounter]:setSequence("dragon4Flying")
            else 
                enemy[enemyCounter]:setSequence("dragon5Flying")
            end
            enemy[enemyCounter]:play()
        end

    end


    --------------------  send guns which can get bonus ----------------------
    local function sendGun() 
        gunSendingTimeCounter = gunSendingTimeCounter + 1
        if(gunSendingTimeCounter % 500 == 0) then

            gunCounter = gunCounter + 1
            gun[gunCounter] = display.newImageRect(sceneGroup, "images/characters/gunSymbol.png", 134,110)
            gun[gunCounter].x = _LEFT - 50
            gun[gunCounter].y = lane[math.random(1, 4)].y
            gun[gunCounter].id = "gun"
            physics.addBody(gun[gunCounter])
            sceneGroup:insert(gun[gunCounter])
            gun[gunCounter].isSensor = true
            gunTransition[gunCounter] = transition.to(gun[gunCounter], {x = _RIGHT + 50, time = 2000, onComplete = function(self)
                if(self ~= nil) then
                    display.remove(self)
                end
            end})
        end
    end



    ------------- hit functions --------------------------

    ------ when gun hit the player ----------------------
    local function gunHitPlayer() 
        audio.play(_ENEMYHIT)

        player.x = _RIGHT - player.width
        player.alpha = 1

        user.gun = user.gun + 1
        playerGun.text = ":  "..user.gun
        loadsave.saveTable(user, "user.json")

    end 



    ------- when enemy hit the house  ----------------------
    local function enemyHitHouse1(x, y) 
        audio.play(_ENEMYHIT)

        house1.x = _RIGHT - 50
        house1.alpha = 1

        displayPoofSheet(x, y)
        -- display the poof sheet
        
        timer.performWithDelay(200, removePoof, 1)

        lives[livesCount].alpha = 0
        livesCount = livesCount - 1
        if(livesCount <= 0) then
            onGameOver()
        end
    end 


    local function enemyHitHouse2(x, y) 
        audio.play(_ENEMYHIT)

        house2.x = _RIGHT - 50
        house2.alpha = 1

        displayPoofSheet(x, y)
        -- display the poof sheet
        
        timer.performWithDelay(200, removePoof, 1)

        lives[livesCount].alpha = 0
        livesCount = livesCount - 1
        if(livesCount <= 0) then
            onGameOver()
        end
    end 

    local function enemyHitHouse3(x, y) 
        audio.play(_ENEMYHIT)

        house3.x = _RIGHT - 50
        house3.alpha = 1

        displayPoofSheet(x, y)
        -- display the poof sheet
        
        timer.performWithDelay(200, removePoof, 1)

        lives[livesCount].alpha = 0
        livesCount = livesCount - 1
        if(livesCount <= 0) then
            onGameOver()
        end
    end 

    local function enemyHitHouse4(x, y) 
        audio.play(_ENEMYHIT)

        house4.x = _RIGHT - 50
        house4.alpha = 1

        displayPoofSheet(x, y)
        -- display the poof sheet
        
        timer.performWithDelay(200, removePoof, 1)

        lives[livesCount].alpha = 0
        livesCount = livesCount - 1
        if(livesCount <= 0) then
            onGameOver()
        end
    end 



    --------- when enemy hit the player -------------------
    local function playerHit()
        audio.play(_PLAYERHIT)

        -- when two physics body collision, they will push each other. This line of code is let the player stay at original place
        player.x = _RIGHT - player.width
        player.alpha = 1

        -- hit, will lose one heart
        lives[livesCount].alpha = 0
        livesCount = livesCount - 1
        if(livesCount <= 0) then
            onGameOver()
        end
    end



    ---------- when bullet hit the enemy ---------------
    local function enemyHit(x, y)
        
        

        audio.play(_ENEMYHIT)

        -- update money
        user.money = user.money + playerEarnedMoney
        playerMoney.text = "$"..user.money
        loadsave.saveTable(user, "user.json")
        --user = loadsave.loadTable("user.json")

         

        blood = display.newSprite(bloodSheet, poofSequenceData)
        blood.x = x
        blood.y = y
        sceneGroup:insert(blood)
        blood:setSequence("disapearBlood")
        blood:play()

        -- display the poof sheet
        
        timer.performWithDelay(200, removeBlood, 1)



    end

    function removeBlood() 
        if(blood ~= nil) then
            display.remove(blood)
        end
    end


    function displayPoofSheet(x, y) 

        poof = display.newSprite(poofSheet, poofSequenceData)
        poof.x = x
        poof.y = y
        sceneGroup:insert(poof)
        poof:setSequence("disapear")
        poof:play()

    end

    function removePoof()
        if(poof ~= nil) then
            display.remove(poof)
        end
    end



    


    ----------------- collision function -----------------
    local function onCollision(event)
        local function removeOnHouse1Hit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
                enemyHitHouse1(event.object1.x, event.object1.y)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
                enemyHitHouse1(event.object1.x, event.object2.y)
            end

        end


        local function removeOnHouse2Hit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
                enemyHitHouse2(event.object1.x, event.object1.y)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
                enemyHitHouse2(event.object1.x, event.object2.y)
            end

        end


        local function removeOnHouse3Hit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
                enemyHitHouse3(event.object1.x, event.object1.y)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
                enemyHitHouse3(event.object1.x, event.object2.y)
            end

        end


        local function removeOnHouse4Hit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
                enemyHitHouse4(event.object1.x, event.object1.y)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
                enemyHitHouse4(event.object1.x, event.object2.y)
            end

        end




        local function removeOnEnemyHit(object1, object2)
            
            display.remove(object1)
            display.remove(object2)
            
            if(object1.id == "enemy") then
                enemyHit(event.object1.x, event.object1.y)
            else
                enemyHit(event.object2.x, event.object2.y)
            end
        end 

        local function removeOnPlayerHit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
            end
        end

        local function removeOnGunHit(object1, object2)
            if(object1 ~= nil and object1.id == "gun") then
                display.remove(object1)
            end

            if(object2 ~= nil and object2.id == "gun") then
                display.remove(object2)
            end
        end


        local function removeOnHouseHit(object1, object2)
            if(object1 ~= nil and object1.id == "enemy") then
                display.remove(object1)
            end

            if(object2 ~= nil and object2.id == "enemy") then
                display.remove(object2)
            end
        end


        local function showPlayHit() 
            player:setSequence("hurt")
            player:play()
            player.alpha = 0.5
            local tmr_onPlayerHit = timer.performWithDelay(100, playerHit, 1)
        end

        if((event.object1.id == "bullet" and event.object2.id == "enemy") or (event.object2.id == "bullet" and event.object1.id == "enemy")) then
            
            removeOnEnemyHit(event.object1, event.object2)

        elseif(event.object1.id == "enemy" and event.object2.id == "player") then
            showPlayHit()
            removeOnPlayerHit(event.object1, nil)
        elseif(event.object2.id == "enemy" and event.object1.id == "player") then
            showPlayHit()
            removeOnPlayerHit(nil, event.object2)
        elseif(event.object1.id == "gun" and event.object2.id == "player") then
            gunHitPlayer()
            removeOnGunHit(event.object1, nil)
        elseif(event.object2.id == "gun" and event.object1.id == "player") then
            gunHitPlayer()
            removeOnGunHit(nil, event.object2)
        elseif((event.object1.id == "house1" and event.object2.id == "enemy") or (event.object2.id == "house1" and event.object1.id == "enemy")) then
            removeOnHouse1Hit(event.object1, event.object2)
        elseif((event.object1.id == "house2" and event.object2.id == "enemy") or (event.object2.id == "house2" and event.object1.id == "enemy")) then
            removeOnHouse2Hit(event.object1, event.object2)
        elseif((event.object1.id == "house3" and event.object2.id == "enemy") or (event.object2.id == "house3" and event.object1.id == "enemy")) then
            removeOnHouse3Hit(event.object1, event.object2)
        elseif((event.object1.id == "house4" and event.object2.id == "enemy") or (event.object2.id == "house4" and event.object1.id == "enemy")) then
            removeOnHouse4Hit(event.object1, event.object2)
        
        end

    end




----------------pause the game -------------------------------------
    local function onPauseTouch(event)
        if(event.phase == "began") then 
            audio.play(_CLICK)
            if(pauseGame == false) then
                --the game is running and we should pause
                pauseGame = true
                physics.pause()
                timer.cancel(tmr_playerShoot)
                Runtime:removeEventListener("enterFrame", sendEnemies)
                Runtime:removeEventListener("enterFrame", sendGun)
                Runtime:removeEventListener("collision", onCollision)

                transition.pause()

                for i = 1, #lane do
                    lane[i]:removeEventListener("touch", onLaneTouch)
                end

                for i = 1, #enemy do 
                    if(enemy[i].isPlaying == true) then
                        enemy[i]:pause()
                    end
                end

                pauseBackground = display.newRect(sceneGroup, 0, 0, _CW * 1.25, _CH * 1.25)
                pauseBackground.x = _CX
                pauseBackground.y = _CY
                pauseBackground:setFillColor(0)
                pauseBackground.alpha = 0.6
                pauseBackground:addEventListener("touch", onPauseTouch)


                pauseText = display.newText(sceneGroup, "Game Pause", 0, 0, _FONT, 90)
                pauseText.x = _CX
                pauseText.y = _CY - pauseText.height


                pauseReminder = display.newText(sceneGroup, "Return To Game", 0, 0, _FONT, 56)
                pauseReminder.x = button_pause.x + 275
                pauseReminder.y = button_pause.y


                pause_returnToMenu = widget.newButton {
                    width = 200,
                    height = 200,
                    defaultFile = "images/gamescreen/backtoMenu.png",
                    onEvent = returnToMenu
                }
                pause_returnToMenu.x = _CX
                pause_returnToMenu.y = pauseText.y + pause_returnToMenu.height
                sceneGroup:insert(pause_returnToMenu)


                button_pause:toFront() -- let button of pause in front of background
            else

                -- the game is paused, and we should unpause it 
                pauseGame = false
                physics.start()
                Runtime:addEventListener("enterFrame", sendEnemies)
                Runtime:addEventListener("enterFrame", sendGun)
                Runtime:addEventListener("collision", onCollision)
                tmr_playerShoot = timer.performWithDelay(playerShootSpeed, playerShoot, 0)
                transition.resume()

                for i = 1, #lane do
                    lane[i]:addEventListener("touch", onLaneTouch)
                end

                for i = 1, #enemy do 
                    if(enemy[i].isPlaying == false) then
                        enemy[i]:play()
                    end
                end

                display.remove(pauseBackground)
                display.remove(pauseText)
                display.remove(pause_returnToMenu)
                display.remove(pauseReminder)
            end

            return true
        end

        
    end



    function onGameOver() 
        audio.play(_GAMEOVER)

        if(tmr_playerShoot) then
            timer.cancel(tmr_playerShoot)
        end

        Runtime:removeEventListener("enterFrame", sendEnemies)
        Runtime:removeEventListener("enterFrame", sendGun)
        Runtime:removeEventListener("collision", onCollision)

        transition.pause()

        for i = 1, #lane do
            lane[i]:removeEventListener("touch", onLaneTouch)
        end

        for i = 1, #enemy do 
            if(enemy[i] ~= nil) then
                display.remove(enemy[i])
            end
        end

        gameoverBackground = display.newRect(sceneGroup, 0, 0, _CW * 1.25, _CH * 1.25)
        gameoverBackground.x = _CX
        gameoverBackground.y = _CY
        gameoverBackground:setFillColor(0) -- set background to black
        gameoverBackground.alpha = 0.6

        gameOverBox = display.newText(sceneGroup, "Game Over", 0, 0, _FONT, 90)
        gameOverBox.x =_CX
        gameOverBox.y = _CY - gameOverBox.height


        gameOver_returnToMenu = widget.newButton {
            width = 200,
            height = 200,
            defaultFile = "images/gamescreen/backtoMenu.png",
            onEvent = returnToMenu
        }
        gameOver_returnToMenu.x = _CX
        gameOver_returnToMenu.y = gameOverBox.y + gameOver_returnToMenu.height
        sceneGroup:insert(gameOver_returnToMenu)

    end
    



    local function onSpeedUpTimeInterval(event) 
        audio.play(_CLICK)
        if(event.phase == "ended") then
            if(isSpeedUp == false and user.gun > 0) then
                -- speed up ---
                timer.cancel(tmr_playerShoot)
                tmr_playerShoot = timer.performWithDelay(playerShootSpeedUp, playerShoot, 0)

                -- update user.gun -----
                user.gun = user.gun - 1
                playerGun.text = ":  "..user.gun
                loadsave.saveTable(user, "user.json")


                button_speedUp.alpha = 0.5
                isSpeedUp = true

                -- 8 secondes for speed up fire -----
                timer.performWithDelay(8000, becomeOriginal, 1)
            end

        end
    end


    function becomeOriginal()
        --print("sssssssssssss")
        isSpeedUp = false
        button_speedUp.alpha = 1
        timer.cancel(tmr_playerShoot)
        tmr_playerShoot = timer.performWithDelay(playerShootSpeed, playerShoot, 0)
    end






    --  add background image
    local background = display.newImageRect(sceneGroup, "images/gamescreen/story-background.png", 1425, 925)
    background.x = _CX
    background.y = _CY

    -- add four lanes
    for i = 1, 4 do 
        lane[i] = display.newImageRect(sceneGroup, "images/gamescreen/grass1.png", 1425, 200)
        lane[i].x = _CX
        lane[i].y = 200 * i - 100
        lane[i].id = i
        lane[i]:addEventListener("touch", onLaneTouch)
    end 

    -- add lives
    for i = 1, livesCount do
        lives[i] = display.newImageRect(sceneGroup, "images/gamescreen/heart.png", 50, 51)
        lives[i].x = _LEFT + i * 60 -20
        lives[i].y = _BOTTOM - 35

    end

    -- add pause button
    button_pause = display.newImageRect(sceneGroup, "images/gamescreen/playing_pause.png", 75, 75)
    button_pause.x = _LEFT + button_pause.width * 0.6
    button_pause.y = _TOP + button_pause.height * 0.6
    button_pause:addEventListener("touch", onPauseTouch)





    -- add speed up button
    button_speedUp = display.newImageRect(sceneGroup, "images/characters/gunSymbol.png", 134, 110)
    button_speedUp.x = _CX
    button_speedUp.y = button_pause.y
    button_speedUp:addEventListener("touch", onSpeedUpTimeInterval)





    

    --physics.setDrawMode("hybrid") // this line of code display the body area of this object

    -- add a player wall, when the pirate hit, will lose a heart
    --playerWall = display.newRect(sceneGroup, 0, 0, 50, _CH)
    --playerWall.x = _RIGHT + 75
    --playerWall.y = _CY
    --playerWall.id = "player"
    --physics.addBody(playerWall)

    -- add houses
    house1 = display.newImageRect(sceneGroup, "images/characters/house1.png", 100, 195)
    house1.x = _RIGHT - 50
    house1.y = lane[1].y
    house1.id = "house1"
    sceneGroup:insert(house1)
    physics.addBody(house1)
    
    
    house2 = display.newImageRect(sceneGroup, "images/characters/house2.png", 100, 195)
    house2.x = _RIGHT - 50
    house2.y = lane[2].y
    house2.id = "house2"
    sceneGroup:insert(house2)
    physics.addBody(house2)


    house3 = display.newImageRect(sceneGroup, "images/characters/house3.png", 100, 195)
    house3.x = _RIGHT - 50
    house3.y = lane[3].y
    house3.id = "house3"
    sceneGroup:insert(house3)
    physics.addBody(house3)



    house4 = display.newImageRect(sceneGroup, "images/characters/house4.png", 100, 195)
    house4.x = _RIGHT - 50
    house4.y = lane[4].y
    house4.id = "house4"
    sceneGroup:insert(house4)
    physics.addBody(house4)


    -- add ninja
    --player = display.newSprite(ninjaSheet, ninjaSequenceData)
    player = display.newSprite(fighterSheet, fighterSequenceData)
    player.x = house1.x - house1.width - 10
    player.y = lane[1].y
    player.id = "player"
    sceneGroup:insert(player)
    physics.addBody(player)


    -- add player money
    playerMoney = display.newText(sceneGroup, "$"..user.money, 0, 0, _FONT, 70)
    playerMoney.anchorX = 1  -- change the center to the rightbottom
    playerMoney.anchorY = 1
    playerMoney.x = house4.x - house4.width / 2
    playerMoney.y = _BOTTOM
    --playerMoney.x = _CX
    --playerMoney.y = _TOP + 35



    -- add player guns
    playerGun = display.newText(sceneGroup, ":  "..user.gun, 0, 0, _FONT, 70)
    playerGun.x = _CX + button_speedUp.width 
    playerGun.y = button_pause.y


    -- add a timer to call playshoot function
    tmr_playerShoot = timer.performWithDelay(playerShootSpeed, playerShoot, 0) -- 0 means infinity

    -- call send enemies
    Runtime:addEventListener("enterFrame", sendEnemies) -- runtime often with "enterFrame"

    -- call send gun
    Runtime:addEventListener("enterFrame", sendGun)

    -- call the collision
    Runtime:addEventListener("collision", onCollision)

end


-- "scene:show()"
function scene:show( event )

    local sceneGroup = self.view
    local phase = event.phase

    if ( phase == "will" ) then
        -- Called when the scene is still off screen (but is about to come on screen).
    elseif ( phase == "did" ) then
        -- Called when the scene is now on screen.
        -- Insert code here to make the scene come alive.
        -- Example: start timers, begin animation, play audio, etc.
    end
end


-- "scene:hide()"
function scene:hide( event )

    local sceneGroup = self.view
    local phase = event.phase

    if ( phase == "will" ) then
        -- Called when the scene is on screen (but is about to go off screen).
        -- Insert code here to "pause" the scene.
        -- Example: stop timers, stop animation, stop audio, etc.
    elseif ( phase == "did" ) then
        -- Called immediately after scene goes off screen.
    end
end


-- "scene:destroy()"
function scene:destroy( event )

    local sceneGroup = self.view

    -- Called prior to the removal of scene's view ("sceneGroup").
    -- Insert code here to clean up the scene.
    -- Example: remove display objects, save state, etc.
end


-- -------------------------------------------------------------------------------

-- Listener setup
scene:addEventListener( "create", scene )
scene:addEventListener( "show", scene )
scene:addEventListener( "hide", scene )
scene:addEventListener( "destroy", scene )

-- -------------------------------------------------------------------------------

return scene