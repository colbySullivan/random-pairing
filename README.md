# random-pairing
Janky program to randomly sort students into desks in this one specific classroom.

# Controls
- Escape to exit program
- Press and release space bar to reshuffle

## Issues and plans
Take all of these with a grain of salt as this was just a for fun afternoon project and my ambitions are bound to change
- Currently the script occupies the top left first but there are plans to make it more spaced out
- Only the current lab is accessable but if required there is room for the other lab
- There are plans to make modifying students easier
- Random could be better but it works


# Running

## Makefile run
To compile
```
g++ -c main.cpp -I"SFML-2.6.0\include"
```

Create runnable exe
```
g++ main.o -o main -L"SFML-2.6.0\lib" -lsfml-graphics -lsfml-window -lsfml-system
```

If make is installed on your device then run the following command

```
make
```
To get rid of the main.o file run
```
make clean
```

# Scripts
Commands to build statically and dynamically are provided.

### Static build
```
.\static.bat
```
### Dynamic build
```
.\dynamic.bat
```
### Remove main.o
```
.\clean.bat
```

# Dependencies
Install of SMFL is required to compile the program but main exe should run stand alone if resource and csv are in the same file.

https://www.sfml-dev.org/download.php

Make sure to place the folder into the C drive or replace the location in the run/compile commands.
