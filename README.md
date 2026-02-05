# university-projects
A curated collection of my university coursework projects from Data Engineering at Gdańsk University of Technology. Includes selected assignments in Basics of Computer Programming (C/C++), Algorithms &amp; Data Structures, Object-Oriented Programming (C++/Java/Python), Databases (ERD/SQL), Software Engineering (UML) and Statistics in Python.

## Table of contents
[Basics of Computer Programming](#basics-of-computer-programming)
* [Jumping Frog (C procedural programming)](#jumping-frog)


[Object-Oriented Programming](#object-oriented-programming)
* [Virtual World Simulator (C++ / console)](#virtual-world-simulator-c--console)
* [Virtual World Simulator (Java / Swing GUI)](#virtual-world-simulator-java--swing-gui)
* [Virtual World Simulator (Python / GUI)](#virtual-world-simulator-python--gui)


[Algorithms &amp; Data Structures](#algorithms--data-structures)

## Basics of Computer Programming

### [Jumping Frog](basics-of-computer-programming/frogger)
This is a terminal-based “Frogger” style action game implemented in C as part of my Basics of Computer Programming coursework.   
The game uses ncurses for text graphics and event-driven input: you control a frog with the arrow keys and try to reach the safe zone while avoiding moving obstacles (cars) across multiple lanes.  
The gameplay parameters (e.g., time limit, car length/speed, and colors) are configurable via a config.txt file located in the same folder.  
**Location:** basics-of-computer-programming/frogger  
**Platform:** implemented and tested on macOS  

**Features:**
- ncurses-based UI (game board + status/info area)
- keyboard controls (arrow keys)
- moving obstacles across lanes with collision detection
- configurable gameplay settings via config.txt (colors, speed, time limit, etc.)
- win/lose conditions with the option to restart

**To run (MacOS/Linux):**
```
gcc frogger.c -o frogger -lncurses
./frogger
```
(Ensure config.txt is in the same directory when running.)

## Object-Oriented Programming

### [Virtual World Simulator (C++ / console)](object-oriented-programming/virtual-world-cpp)

A turn-based 2D virtual world simulator implemented in C++, visualized in the console using ASCII symbols. The world is represented as an NxM grid where each organism occupies one cell. During each turn, organisms act in initiative/age order; animals move and collide, plants spread, and fights/breeding affect the world state.  
**Location:** object-oriented-programming/virtual-world-cpp   

**Features:**
- Console visualization (ASCII map + event log)
- Turn system (initiative + age ordering)
- Animals + plants with unique behaviors (movement, collisions, special rules)
- Human controlled via arrow keys + special ability
- Breeding (animals) and sowing (plants)
- Save/Load game state to/from file

### [Virtual World Simulator (Java / Swing GUI)](object-oriented-programming/virtual-world-java)

A Java implementation of the same virtual world simulator, this time with a GUI built in Swing. The application provides GUI controls for advancing turns and managing the simulation, and it displays a message/log area for events (fights, plant consumption, spawning, etc.).    
**Location:** object-oriented-programming/virtual-world-java    

**Features:**
- Swing-based grid visualization + event log panel
- Turn progression via GUI controls
- All required animals and plants + Human with special ability
- Save/Load world state to/from file
- Add organism by clicking a free cell (choose species/type)


### [Virtual World Simulator (Python / GUI)](object-oriented-programming/virtual-world-python)

A Python version of the virtual world simulator, implemented with a GUI (library of choice). The simulation follows the same turn-based rules (initiative/age ordering, collisions, organism behaviors), includes a Human controlled by arrow keys, and supports saving/loading the state.    
**Location:** object-oriented-programming/virtual-world-python  

  
**Features:**
- GUI visualization of the grid + event/messages area
- Turn progression via GUI
- Required animals (including cyber-sheep) and plants
- Human controlled by arrow keys + special ability
- Save/Load world state to/from file
- Add organism by clicking a free cell (choose species/type)


## Algorithms &amp; Data Structures
 
