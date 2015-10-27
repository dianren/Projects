local composer = require( "composer" )

local scene = composer.newScene()

-- -----------------------------------------------------------------------------------------------------------------
-- All code outside of the listener functions will only be executed ONCE unless "composer.removeScene()" is called.
-- -----------------------------------------------------------------------------------------------------------------

-- local forward references should go here
local widget = require "widget"
widget.setTheme("widget_theme_ios7")

user = loadsave.loadTable("user.json")

local button_upgrade1, button_upgrade2, button_menu, sceneTitle, warningMessage, button_buy
local item, button_returnToMenu, gun, userGunText, userText, gunText
-- -------------------------------------------------------------------------------

-- FUNCTIONS
local function returnToMenu( event ) 
    if (event.phase == "ended") then
        audio.play(_CLICK)
        composer.gotoScene("scene_menu", "slideDown")
    end
end

local function hideWarningMessage()
    warningMessage.alpha = 0
end



local function onBuyingTouch(event) 
    if(event.phase == "ended") then
        audio.play(_CLICK)
        if(user.money >= 150) then
            user.money = user.money - 150
            sceneTitle.text = "Your money : $"..user.money
            user.gun = user.gun + 1
            userGunText.text = ""..user.gun
            loadsave.saveTable(user, "user.json")
            user = loadsave.loadTable("user.json")
        else
            warningMessage.alpha = 1
            local timeOfWarningmessage = timer.performWithDelay(1000, hideWarningMessage, 1)
        end
    end
end   


-- "scene:create()"
function scene:create( event )

    local sceneGroup = self.view

    -- Initialize the scene here.
    -- Example: add display objects to "sceneGroup", add touch listeners, etc.
    local background = display.newImageRect(sceneGroup, "images/gamescreen/shopping_bg.png", 1425, 950)
    background.x = _CX 
    background.y = _CY

    sceneTitle = display.newText(sceneGroup, "Your money : $"..user.money, 0, 0, _FONT, 110)
    sceneTitle.x = _CX
    sceneTitle.y = _TOP + 70

    item = display.newText(sceneGroup, "item", 0, 0, _FONT, 90)
    item.x = _LEFT + 300
    item.y = sceneTitle.y + 200


    gun = display.newImageRect(sceneGroup, "images/gamescreen/gunSymbol.png", 268, 220)
    gun.x = item.x  -- will not appear on screen
    gun.y = item.y + gun.height

    gunText = display.newText(sceneGroup, ": $150", 0, 0, _FONT, 70)
    gunText.x = gun.x + gun.width
    gunText.y = gun.y

    
    ---------------------
    userText = display.newText(sceneGroup, "You have", 0, 0, _FONT, 90)
    userText.x = _RIGHT - 300
    userText.y = item.y

    userGunText = display.newText(sceneGroup, ""..user.gun, 0, 0, _FONT, 70)
    userGunText.x = userText.x
    userGunText.y = gunText.y



    --- buy button ---
    ------
    button_buy = widget.newButton {
        width = 120,
        height = 120,
        defaultFile = "images/menuscreen/menu_buy.png",
        onEvent = onBuyingTouch -- not created quite yet
    }
    button_buy.x = gun.x
    button_buy.y = gun.y + gun.height
    sceneGroup:insert(button_buy)


    --  return to menu button 
    button_returnToMenu = widget.newButton {
        width = 100,
        height = 100,
        defaultFile = "images/menuscreen/backtoMenu.png",
        onEvent = returnToMenu
    }
    button_returnToMenu.anchorX = 1
    button_returnToMenu.anchorY = 1
    button_returnToMenu.x = _RIGHT
    button_returnToMenu.y = _BOTTOM
    sceneGroup:insert(button_returnToMenu)



    -- warning message
    warningMessage = display.newText(sceneGroup, "Not enough money.", 0, 0, _FONT, 52)
    warningMessage.x = _CX
    warningMessage.y = sceneTitle.y + sceneTitle.height * 0.7
    warningMessage.alpha = 0


    
    
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