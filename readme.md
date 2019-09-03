# No One Lives Forever Modernizer

[![Build Status](https://dev.azure.com/heytherecoffee/NOLF-Modernizer/_apis/build/status/haekb.nolf1-modernizer?branchName=master)](https://dev.azure.com/heytherecoffee/NOLF-Modernizer/_build/latest?definitionId=3&branchName=master)

The goal of NOLF Modernizer is to help fix some long standing bugs, and update some more outdated features of the game.

This project is a work in progress.

## Features
 - Cap framerate during menus and gameplay to 60fps
 - Fixed the mouse stutter
 - Optimized some fill rendering
 - Fixed slow text rendering

## Additional Config Commands
The following are new config commands:
  - `FramerateLock`           - INT - Locks the framerate if the value is 1. (Default is 1)
  - `ShowFramerate`           - INT - Displays the framerate if the value is 1. (Default is 0)
  - `OldMouseLook`            - INT - Uses the old mouse look code if the value is 1. (Default is 0)
  - `NoFunMenus`              - INT - Only displays the default main menu if the value is 1. (Default is 0)
  - `RestrictCinematicsTo4x3` - INT - Adds black bars onto the sides of cinematics on a non 4x3 resolution, if the value is 1. (Default is 0)
  - `QuickSwitch`             - INT - Instantly switch between weapons, if the value is 1. (Default is 0)
  - `UIScale`                 - FLOAT - Scales the in-game HUD. (Default is 0.5)

Most of these commands are also available in their respective options menu.

## Building
You can now compile it using Visual Studio 2019 (Requires C++ and MFC), thanks to the NOLF2's sdk including some key files. They're all included and ready to compile.

The following build configurations are setup to build: 
 - Debug
 - Final Release

If you experience any issues, feel free to open an issue.

## D3D and 2048 pixel limit

I recommend using the following mod's dll, ren, and exe for developing and playing NOLF! (Just don't enable the .rez file!)
https://nolfgirl.net/Unityhq/forums/files/file/147-nolf-widescreen-fix-for-goty-edition/

This allows for resolutions higher like 2560x1440 to be used. 

Also this mod was developed using these files. :)

## DGVoodoo2

I don't recommend using this application. I've fixed the majority of the slowdowns caused by old d3d techniques. And (at least on my machine) DGVoodoo2 would cause dynamic lights to absolutely destroy my framerate!

## License
This code is still bound to the original EULA found in the NO ONE LIVES FOREVER Source Code v1.003. This can be viewed in the readme.txt file.