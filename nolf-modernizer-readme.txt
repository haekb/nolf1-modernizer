No One Lives Forever Modernizer (v1.005 Modern)
-----------------------------------------------
https://heythere.coffee/nolf/

The goal of NOLF Modernizer is to help fix some long standing bugs, and update some more outdated features of the game.

-- How To Install

Place all the files in your No One Lives Forever game directory. 
Then launch NOLF.exe, and click "Advanced", and then "Customize". 
Simply "Add" the Modernizer.rez file, and click "Ok", then launch the game!

It's important that you don't run this mod with any other mods that may have modified the game code. 

-- Features

 - Cap framerate during menus and gameplay to 60fps
 - Fixed the mouse stutter
 - Optimized performance in select cases
 - Jukebox to play some of your favourite in-game tunes
 - Supports the Game of the Year edition

--  Additional Config Commands

We've added new autoexec.cfg commands! 

Some of these will show up in your autoexec.cfg as you set them, but if it's missing you can simply add it yourself.

"FramerateLock"			    - Locks the framerate if the value is 1. (Default is 1)
"ShowFramerate"			    - Displays the framerate if the value is 1. (Default is 0)
"OldMouseLook"			    - Uses the old mouse look code if the value is 1. (Default is 0)
"NoFunMenus"			    - Only displays the default main menu if the value is 1. (Default is 0)
"RestrictCinematicsTo4x3"	- Adds black bars onto the sides of cinematics on a non 4x3 resolution, if the value is 1. (Default is 0)
"QuickSwitch"			    - Instantly switch between weapons, if the value is 1. (Default is 0)
"UIScale"			        - Scales the in-game HUD. (Default is 0.5)
"UseGotyMenu"			    - Switch between the original main menu and the GOTY version. (Default is based on your version)

Most of these commands are also available in their respective options menu.

-- Known Bugs

Unfortuantely we can't fix everything! Here's a list of known bugs.

Bug: Some geometry may cause the player to be pushed or be hard to traverse
There seems to be an issue with the underlying physics engine. We've corrected most of the game breaking issues, but if you find any terrain or doorways that impossible to enter please let us know!

Bug: Game runs really fast on unlocked framerates
The game was designed to work at a locked 60 fps. It is possible to correct most of the speed up issues, but that would be incredibly time consuming, and some of the issues are due to how the engine itself handles physics and sound. 

Bug: I can't run resolutions higher than 1920x1080
There's a small issue with Direct3D where it doesn't like things higher than 2000 pixels. A simple fix is to download and install (most) of this mod: https://nolfgirl.net/Unityhq/forums/files/file/147-nolf-widescreen-fix-for-goty-edition/ Just don't enable the .rez file! 

Bug: Dynamic lighting (flashlights) cause my framerate to dip below 60
On the few systems we tested we encountered an issue with DGVoodoo2. If you're running that software, I'd reccomend you disable it when using this patch.