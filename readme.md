# No One Lives Forever Modernizer

[![Build Status](https://dev.azure.com/heytherecoffee/NOLF-Modernizer/_apis/build/status/haekb.nolf1-modernizer?branchName=master)](https://dev.azure.com/heytherecoffee/NOLF-Modernizer/_build/latest?definitionId=3&branchName=master)

The goal of NOLF Modernizer is to help fix some long standing bugs, and update some more outdated features of the game.

## Features

 - Working multiplayer out of the box
 - Cap framerate during menus and gameplay to 60fps
 - Fixed the mouse stutter
 - Optimized performance in select cases
 - Jukebox to play some of your favourite in-game tunes
 - Supports the Game of the Year edition

## Patch 1

 - Fixed a bug with defusing bombs and activating some switches.

## Patch 2

- Added `NoRawInput` to disable mouse raw input.
- Fixed missing continue button on mission summary screen.
- Improved loading screen time (...that I broke, oops!)
- Fixed some invisible impassible geometry.
- Added a experimental developer console, can be toggled on/off with tilde. (`~`)
- Fixed a crash in the weapons hotkey screen.

## Patch 3

- Bumped version to 1.006.
- Patched out GameSpy from dedicated/hosted servers and the server browser.
- Fixed a bug in ai path finding causing values to not always be accurate.
- Fixed a silent out of range bug that could cause enemies to disappear and travel to a nearby galaxy at FTL speed!
- Made the console key rebindable. (It's at the very bottom of the custom controls list.)
- Added Big Head Mode! It's currently a little buggy, but humourous. Check the console command list on how to enable it.
- Included some patched binaries to help improve compatibility. 
- Added a windowed mode toggle to the display options.
- Added anisotropic filtering to advanced performance options.
- Fixed shadows disappearing between cutscenes and saved games.
- Added a "Blackscreen Fix" work around for Intel HD graphics chips in Display options.

## Patch 4
- Re-worked jukebox into an attribute file. 
- Added missing ambient track for the Main Theme to the Jukebox.


## Additional Config/Console Commands

The following are new config/console commands:
  - `FramerateLock`           - INT - Locks the framerate if the value is 1. (Default is 1)
  - `ShowFramerate`           - INT - Displays the framerate if the value is 1. (Default is 0)
  - `OldMouseLook`            - INT - Uses the old mouse look code if the value is 1. (Default is 0)
  - `NoFunMenus`              - INT - Only displays the default main menu if the value is 1. (Default is 0)
  - `RestrictCinematicsTo4x3` - INT - Adds black bars onto the sides of cinematics on a non 4x3 resolution, if the value is 1. (Default is 0)
  - `QuickSwitch`             - INT - Instantly switch between weapons, if the value is 1. (Default is 0)
  - `UIScale`                 - FLOAT - Scales the in-game HUD. (Default is 0.5)
  - `UseGotyMenu`             - INT - Switch between the original main menu and the GOTY version. (Default is based on your version)
  - `NoRawInput`              - INT - Disables raw mouse input. (Default is 0)
  - `ConsoleBackdrop`         - INT - Swap between 3 different console backdrops: (0) demo, (1) blanktag, and (2) black. (Default is 0)
  - `BigHeadMode`             - INT - Enable or Disable BigHeadMode. (Default is 0)
  - `DisplayTriggers`         - INT - Shows or Hides a physical representation of level triggers. (Default is 0)
  - `EnableScreenTinting`     - INT - Enable or disable native screen tinting. Disabling will activate an alternate screen tinting. (Default is 1)
  - `EnableLightScale`        - INT - Enable or disable light scaling. (Default is 1)


Most of these commands are also available in their respective options menu.

## Building

You can now compile it using Visual Studio 2019 (Requires C++ and MFC), thanks to the NOLF2's sdk including some key files. They're all included and ready to compile.

The following build configurations are setup to build: 
 - Debug
 - Final Release

If you experience any issues, feel free to open an issue.

## Contributing

Simply fork and submit a PR (preferbly with a matching issue ticket!) 

Try to keep to the original coding style, with descriptive commit messages. (Unlike some of my original commits!)

## Localization

There have been community efforts to localize Modernizer into other languages. And while I don't have the time to directly help in these efforts, here are some steps you can do you to localize and distribute your localization patch!

First off modify the string table located in CRes.dll (Client Resource). This can be done with the latest version of Visual Studio 2019 and this source code. You may also attempt to use other programs to modify the string table directly in the dll. 

Secondly there are some additional strings in Jukebox.txt located here: https://github.com/haekb/nolf1-modernizer/blob/master/ASSETS/Attributes/Jukebox.txt) 

Finally compile your new CRes.dll and the modified attribute file into its own rez using LithRez.exe (from the SDK) and make sure it loads after Modernizer.rez.

## D3D and 2048 pixel limit

You can grab a patched d3d.ren, and d3dim700.dll from the ASSETS folder or from a release of NOLF Modernizer.

## DGVoodoo2

I don't recommend using this application. I've fixed the majority of the slowdowns caused by old d3d techniques. And (at least on my machine) DGVoodoo2 would cause dynamic lights to absolutely destroy my framerate!

## License

This code is still bound to the original EULA found in the NO ONE LIVES FOREVER Source Code v1.003. This can be viewed in the readme.txt file.