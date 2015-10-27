-- FILE: main.lua
-- DESCRIPTION: start the app, declare some variables, and setup the player save file


-- APP OPTIONS
_APPNAME = "Pirates vs Ninjas"
_FONT = "PTSerif-Regular"
_SHOOTUPGRADECOST = 35
_LIVESUPGRADECOST = 100
_SHOWADS = true 
_SHOOTLEVELMAX = 10
_LIVESLEVELMAX = 10


-- CONSTANT VALUES
_CX = display.contentWidth * 0.5  
_CY = display.contentHeight * 0.5
_CW = display.contentWidth
_CH = display.contentHeight
_TOP = display.screenOriginY
_LEFT = display.screenOriginX
_RIGHT = display.viewableContentWidth - _LEFT
_BOTTOM = display.viewableContentHeight - _TOP



-- hide the status bar
display.setStatusBar(display.HiddenStatusBar)

-- include composer
local composer = require "composer"


-- include load/save library from coronarob
loadsave = require("loadsave")

-- load up audios
_BACKGROUNDMUSIC = audio.loadStream("audio/background-music.mp3")
_THROW = audio.loadSound("audio/throw.wav")
_ENEMYHIT = audio.loadSound("audio/enemy-hit.wav")
_PLAYERHIT = audio.loadSound("audio/player-hit.mp3")
_GAMEOVER = audio.loadSound("audio/game-over.wav")
_CLICK = audio.loadSound("audio/click.mp3")
_FIRE = audio.loadSound("audio/fire.wav")
_MACHINEGUN = audio.loadSound("audio/machineGun.wav")

-- set up a saved file for our user
user = loadsave.loadTable("user.json") -- look for a file called " user.json"
if (user == nil) then
	user = {}  -- create a table
	user.money = 100
	user.gun = 0
	user.shootlevel = 0
	--user.shootlevelMax = 15
	user.liveslevel = 0
	--user.liveslevelMax = 15
	user.playsound = true
	loadsave.saveTable(user, "user.json") -- loadsave is library
end


composer.gotoScene("scene_menu") -- tells us go to the scene named "scene_menu"



