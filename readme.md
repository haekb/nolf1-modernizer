# No One Lives Forever Modernizer

The goal of NOLF Modernizer is to help fix some long standing bugs, and update some more outdated features of the game.

This project is heavily WIP.

## Features
 - Cap framerate during cinematics to ensure they play out correctly
 - Fixed the mouse stutter

## Building
Sadly you'll have to dig up your old copy of Visual C++ 6.0. I did try to make it compile under Visual Studio 2017, but there's some tricky linker errors that I couldn't solve.

You may need to modify your global include directory list, to include `./LIBS/SDL2-2.0.10/include`, but other than that it should be good to go! Either unrez the entire game, or just make a new rez file and make sure the game loads that file last!

## License
This code is still bound to the original EULA found in the NO ONE LIVES FOREVER Source Code v1.003. This can be viewed in the readme.txt file.