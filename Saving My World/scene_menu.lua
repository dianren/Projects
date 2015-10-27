-- FILE: secne_menu
-- DESCRIPTION: start the menu and allow sound on/off

local composer = require( "composer" )

local scene = composer.newScene()

local widget = require "widget"  -- include a "widget" library
widget.setTheme("widget_theme_ios7")




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
    {name = "fight", start = 1, count = 9, time = 700, loopCount = 0},
    
}



local dragonSheetData = {
    width = 428,
    height = 345,
    numFrames = 2,
    sheetContentWidth = 856,
    sheetContentHeight = 345
}
local dragonSheet = graphics.newImageSheet("images/menuscreen/menu_dragon1.png", dragonSheetData)
local dragonSequenceData = {
    {name = "dragonFiring", start = 1, count = 2, time = 1200, loopCount = 0} -- 0 means infinity
}
-- -----------------------------------------------------------------------------------------------------------------
-- All code outside of the listener functions will only be executed ONCE unless "composer.removeScene()" is called.
-- -----------------------------------------------------------------------------------------------------------------

-- local forward references should go here
local button_play, button_buy, button_sounds

local moveMyDragon, moveMyFireman

local fighterMan, dragon

user = loadsave.loadTable("user.json")

local function onPlayTouch(event) -- parameter event can tell us the label, location, state(began, moved, ended) and so on of button
    if (event.phase == "ended") then
        audio.play(_CLICK)
        composer.gotoScene("scene_game", "slideLeft")
    end
end

local function onBuyTouch(event) 
    if (event.phase == "ended") then
        audio.play(_CLICK)
        composer.gotoScene("scene_buy", "slideUp")
    end
end

local function onSoundsTouch(event) 
    if (event.phase == "ended") then
        if (user.playsound == true) then
            -- mute the game
            audio.setVolume(0) 
            button_sounds.alpha = 0.5  -- alpha means transparent
            user.playsound = false
        else 
            -- unmute the game
            audio.setVolume(0.5)
            button_sounds.alpha = 1
            user.playsound = true
        end
        loadsave.saveTable(user, "user.json")
    end
end
-- -------------------------------------------------------------------------------


-- "scene:create()"
function scene:create( event )

    local sceneGroup = self.view

    -- Initialize the scene here.
    -- Example: add display objects to "sceneGroup", add touch listeners, etc.

    local background = display.newImageRect(sceneGroup, "images/menuscreen/newBackground.png", 1480, 960)
    background.x = _CX 
    background.y = _CY

    --local backgroundOverlay = display.newImageRect(sceneGroup, "images/menuscreen/menu_bg_overlay.png", 1425, 950)
  	--backgroundOverlay.x = _CX
    --backgroundOverlay.y = _CY

    local gameTitle = display.newImageRect(sceneGroup, "images/menuscreen/menu_title.png", 622, 300)
    gameTitle.x = _CX
    gameTitle.y = _CH * 0.1  -- dynamic position 

    --local myDragon = display.newImageRect(sceneGroup, "images/menuscreen/menu_dragon.png", 428, 345)
    --myDragon.x = _LEFT - myDragon.width-- will not appear on screen
    --myDragon.y = _CH * 0.7

    --local myFireman = display.newImageRect(sceneGroup, "images/menuscreen/menu_fireman.png", 330, 356)
    --myFireman.x = _RIGHT + myFireman.width  -- will not appear on screen
    --myFireman.y = _CH * 0.7


    -- create buttons
    button_play = widget.newButton {
        width = 140,
        height = 140,
        defaultFile = "images/menuscreen/menu_play.png",
        --overFile = "images/menuscreen/btn_play_over.png", -- means you touch the button, the image will appear
        onEvent = onPlayTouch -- not created quite yet
    }
    button_play.x = _CX
    button_play.y = gameTitle.y + gameTitle.height / 2
    sceneGroup:insert(button_play)


    button_buy = widget.newButton {
        width = 120,
        height = 120,
        defaultFile = "images/menuscreen/menu_buy.png",
        onEvent = onBuyTouch -- not created quite yet
    }
    button_buy.anchorX = 1  -- change the center to the rightbottom
    button_buy.anchorY = 1
    button_buy.x = _RIGHT
    button_buy.y = _BOTTOM
    sceneGroup:insert(button_buy)


    button_sounds = widget.newButton {
        width = 78,
        height = 79,
        defaultFile = "images/menuscreen/btn_music.png",
        overFile = "images/menuscreen/btn_music_over.png", -- means you touch the button, the image will appear
        onEvent = onSoundsTouch -- not created quite yet
    }
    button_sounds.x = _LEFT + 75
    button_sounds.y = _TOP + 75
    sceneGroup:insert(button_sounds)



    ----------
    fighterMan = display.newSprite(fighterSheet, fighterSequenceData)
    fighterMan.x = 720
    fighterMan.y = _CH * 0.8
    sceneGroup:insert(fighterMan)
    fighterMan:setSequence("fight")
    fighterMan:play()


    ---------
    dragon = display.newSprite(dragonSheet, dragonSequenceData)
    dragon.x = 350
    dragon.y = _CH * 0.7
    sceneGroup:insert(dragon)
    dragon:setSequence("dragonFiring")
    dragon:play()


    -- Transition means movement
    --moveMyFireman = transition.to(myFireman, {x = 850, delay = 500})
    --moveMyDragon = transition.to(myDragon, {x = 380, delay = 500})
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

        --audio.play(_BACKGROUNDMUSIC, {channel = 1, loops = -1, fadein = 50})

        local prevScene = composer.getSceneName("previous")
        if(prevScene) then
            composer.removeScene(prevScene)
        end
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