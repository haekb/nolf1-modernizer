# No One Lives Forever Modernizer

The goal of NOLF Modernizer is to help fix some long standing bugs, and update some more outdated features of the game.

This project is a work in progress.

## Features
 - Cap framerate during menus and gameplay to 60fps
 - Fixed the mouse stutter
 - Optimized some fill rendering
 - Fixed slow text rendering

## Additional Config Commands
The following are new config commands:
  - `FramerateLock` - INT - Locks the framerate if the value is 1.
  - `ShowFramerate` - INT - Displays the framerate if the value is 1.
  - `OldMouseLook`  - INT - Uses the old mouse look code if the value is 1.

## Building
You can now compile it using Visual Studio 2017, thanks to the NOLF2's sdk including some key files. They're all included and ready to compile.

If you experience any issues, feel free to open an issue.

## License
This code is still bound to the original EULA found in the NO ONE LIVES FOREVER Source Code v1.003. This can be viewed in the readme.txt file.