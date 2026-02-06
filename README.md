# university-projects
A curated collection of my university coursework projects from Data Engineering at Gdańsk University of Technology. Includes selected assignments in Basics of Computer Programming (C/C++), Algorithms &amp; Data Structures (Stack/Heap/Trie in C++), Object-Oriented Programming (C++/Java/Python), Databases (ERD/SQL) and Software Engineering (UML).

## Table of contents
[Basics of Computer Programming](#basics-of-computer-programming)
* [Jumping Frog (C procedural programming)](#jumping-frog)
* [Snake Game (C++ procedural programming](#snake-game)

[Algorithms &amp; Data Structures](#algorithms--data-structures)
* [Stack Processor](#stack-processor)
* [Binary Heap](#binary-heap)
* [Trie](#trie)

[Object-Oriented Programming](#object-oriented-programming)
* [Virtual World Simulator (C++ / console)](#virtual-world-simulator-c--console)
* [Virtual World Simulator (Java / Swing GUI)](#virtual-world-simulator-java--swing-gui)
* [Virtual World Simulator (Python / GUI)](#virtual-world-simulator-python--gui)

[Databases](#databases)
* [Shipping Line Database](#shipping-line-database)

[Software Engineering](#software-engineering)
* [High-School E-Learning Platform (UML in Enterprise Architect)](#high-school-e-learning-platform-uml-in-enterprise-architect)

## Basics of Computer Programming

### [Jumping Frog](basics-of-computer-programming/frogger)
This is a terminal-based “Frogger” style action game implemented in C as part of my Basics of Computer Programming coursework.   
The game uses ncurses for text graphics and event-driven input: you control a frog with the arrow keys and try to reach the safe zone while avoiding moving obstacles (cars) across multiple lanes.  
The gameplay parameters (e.g., time limit, car length/speed, and colors) are configurable via a config.txt file located in the same folder.   
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

### [Snake Game](basics-of-computer-programming/snake-game)
## Snake (C++ / SDL2) — Coursework Game Implementation

This project is an implementation of the classic Snake game in C++ using the provided SDL2-based helper framework from the course instruction. The game renders a board and an information panel, supports keyboard control, and tracks gameplay state over time. The instruction forbids using the C++ STL types like string/vector and recommends C-style file I/O for persistence.  
**Platform:** implemented and tested on Linux Ubuntu in Virtual Machine

**Features:**
* Basic game UI: visible board area plus a side area for status information; key handling for Esc (exit) and n (new game) 
* Snake movement controlled with arrow keys; no board wrapping; if the snake hits the border and the player does not turn, it automatically turns to a valid direction (right if possible, otherwise left) 
* Self-collision detection; on collision the game ends and the player can exit or start a new game 
* Elapsed time display and an on-screen list of completed requirements (mandatory and optional) 
* Blue dot that spawns randomly; eating it increases snake length and spawns a new dot 
* Speedup over time (configurable interval and factor) 
* Red dot bonus that appears for a limited time; includes a progress bar; bonus randomly applies either shortening the snake or slowing it down 
* Points system for eating blue and red dots 
* Persistent top-3 best scores stored in a file; displayed after the game ends; prompts for a name if a score qualifies

**To run (Linux):**
```
TODO
```

## Algorithms &amp; Data Structures  

### [Stack Processor](algorithms-and-data-structures/stack-processor)  

This project is an emulator of a fictional stack-based processor called Stack Translator Of Symbols (AaD5). The emulator reads a program (a sequence of single-character instructions) and an input stream, then executes the program using three core components: program memory, an instruction pointer, and a stack.  
Unlike typical stack machines, this processor’s stack elements are lists of characters. Some lists represent numbers (digits with an optional trailing - sign, stored least-significant digit first), while others represent arbitrary symbol sequences. The instruction set supports stack manipulation, character I/O, numeric comparisons, jumps, and arithmetic.  

**Features:**
- Full interpreter loop for a one-character instruction set (up to 20,000 instructions)
- Stack operations: push/pop/duplicate/swap/copy-from-depth (' , : ; @)
- Data operations on character lists: append, split first char, concatenate (# $ + literal characters)
- Character I/O: read from provided input (.), write first char of top list (>)
- Numeric operations on encoded lists: negation/abs (- ^), comparisons (< =), addition (+)
- Control flow: instruction pointer value (~) and conditional jump (?)
- Debug/inspection instruction: print full stack state (&)
- Implemented under constraints typical for A&DS coursework (limited loops, recursion emphasis; no STL containers except basic I/O, no arrays except for program/input storage)

**Input / Output:**  
Input: 
```
'123'-456&+&
```
Output:  
```
1: 321  
0: 654-  
0: 333-
```

### [Binary Heap](algorithms-and-data-structures/binary-heap)  

This project solves a shortest-path problem on a 2D grid where each cell has a non-negative **height**. Moving to a side-adjacent cell has a cost that depends on elevation:  
* if you move from height B to A and A > B, the move costs (A − B + 1) minutes
* otherwise (A ≤ B), the move costs 1 minute

In addition to normal movement, the map may contain one-way lifts. A lift transports you from a start cell to a destination cell in a fixed travel time, but it can only depart at minutes that are multiples of a given interval. If you arrive at a lift at time t, you may need to wait until the next departure time, then add the travel time.  
The solution uses a priority-queue approach (implemented with a binary heap) to efficiently compute the minimum time from the start to the destination (all values fit in int).

**Features:**  
- Grid shortest-path computation with elevation-dependent edge weights
- Lift edges with **waiting time** based on departure intervals
- Efficient processing using a **binary heap** priority queue (Dijkstra-style)

**Input / Output:**  

Input:  
```txt
9 8 0 0 8 7 0
0 0 0 0 0 0 0 0 8 
0 9 9 9 9 9 9 9 0 
0 1 0 1 0 0 0 9 0 
0 9 0 0 0 1 0 9 0 
0 9 1 1 1 1 0 9 0 
0 9 0 0 0 0 0 9 0 
0 9 9 9 9 1 9 9 0 
8 0 0 0 0 0 0 0 0 
```
Output:  
```txt
18
```

## [Trie](algorithms-and-data-structures/trie)  

This project implements a trie-based structure for storing integer keys from a sparse universe as an alternative to hash tables with better worst-case access guarantees. The trie is defined by two parameters n and k: the root has n children, and each child has k children, continuing by repeatedly selecting the next node using modular indexing.  
Insertion starts at the root. If the current node is empty, the key is stored there. Otherwise, the next node is chosen by computing x mod n at the first level, then repeating div mod k on deeper levels until an empty node is found. Lookup follows the same traversal pattern and succeeds if the key is encountered; reaching an empty node means the key is not present.  
Deletion finds the node containing the key. If the node is a leaf, it is deleted directly. If it is an internal node, the implementation selects a deletion candidate leaf by always searching to the left (leftmost external descendant), copies the candidate’s key into the original node, and deletes the candidate leaf. The project supports printing the trie in preorder, which is sensitive to the deletion strategy used.  

**Features:**  
* I x: insert key x (prints “x exist” if already present)
* L x: lookup key x (prints “x exist” or “x not exist”)
* D x: delete key x (prints “x not exist” if missing; otherwise no output)
* P: print keys in preorder traversal

**Input / Output:**  
Input:  
```txt
29
0 511
8 4

I 3
I 31
I 150
I 190
I 130
I 174
I 81
I 30
I 203
P
L 32
L 30
L 150
D 150
L 150
I 150
L 150
D 3
L 3
I 3
L 3
D 3
L 3
D 30
L 30
I 30
L 30
D 30
L 30
```

  
Output:  
```txt
3 81 130 203 150 174 190 30 31 
32 not exist
30 exist
150 exist
150 not exist
150 exist
3 not exist
3 exist
3 not exist
30 not exist
30 exist
30 not exist
```

## Object-Oriented Programming

### [Virtual World Simulator (C++ / console)](object-oriented-programming/virtual-world-cpp)

A turn-based 2D virtual world simulator implemented in C++, visualized in the console using ASCII symbols. The world is represented as an NxM grid where each organism occupies one cell. During each turn, organisms act in initiative/age order; animals move and collide, plants spread, and fights/breeding affect the world state.    

**Features:**
- Console visualization (ASCII map + event log)
- Turn system (initiative + age ordering)
- Animals + plants with unique behaviors (movement, collisions, special rules)
- Human controlled via arrow keys + special ability
- Breeding (animals) and sowing (plants)
- Save/Load game state to/from file

### [Virtual World Simulator (Java / Swing GUI)](object-oriented-programming/virtual-world-java)

A Java implementation of the same virtual world simulator, this time with a GUI built in Swing. The application provides GUI controls for advancing turns and managing the simulation, and it displays a message/log area for events (fights, plant consumption, spawning, etc.).     

**Features:**
- Swing-based grid visualization + event log panel
- Turn progression via GUI controls
- All required animals and plants + Human with special ability
- Save/Load world state to/from file
- Add organism by clicking a free cell (choose species/type)

### [Virtual World Simulator (Python / GUI)](object-oriented-programming/virtual-world-python)

A Python version of the virtual world simulator, implemented with a GUI (library of choice). The simulation follows the same turn-based rules (initiative/age ordering, collisions, organism behaviors), includes a Human controlled by arrow keys, and supports saving/loading the state.    
  
**Features:**
- GUI visualization of the grid + event/messages area
- Turn progression via GUI
- Required animals (including cyber-sheep) and plants
- Human controlled by arrow keys + special ability
- Save/Load world state to/from file
- Add organism by clicking a free cell (choose species/type)

## Databases  

### [Shipping Line Database](databases/shipping-line-db)

This laboratory project is a complete database design and implementation for a shipping line domain. It covers the full workflow taught in the Databases labs: conceptual modeling (ERD), translating the model into a relational schema, implementing it in SQL, populating it with data, writing non-trivial queries, and preparing scripts that demonstrate transactional processing and isolation-level behavior.    

**What’s included in this project:**
* ERD diagram (conceptual model) and relational schema derived from it (tables, keys, relationships)
* DDL scripts: CREATE TABLE with primary keys, foreign keys, constraints (NOT NULL, CHECK, UNIQUE) 
* DML scripts: INSERT statements to populate the database with subject-related data 
* Update and delete scripts demonstrating referential integrity effects (including cascade scenarios, if enabled) 
* Drop scripts to cleanly remove database objects
* A set of 10 business-oriented SELECT queries, including a view, joins, subqueries, aggregates, grouping, and ordering (each query documented with a short explanation) 
* Transactional processing scripts to showcase how concurrent operations behave under different isolation levels


## Software Engineering

### [High-School E-Learning Platform (UML in Enterprise Architect)](software-engineering/high-school-e-learning-platform)

This repository contains a complete set of analysis and design artifacts created as part of the Software Engineering laboratory. The project was completed in a 3-person team (me + two colleagues) and models a high-school e-learning platform, from initial scope definition to detailed UML design.   

**What’s included in this project:**
* Vision Document for the e-learning platform, describing the problem context, goals, scope, functional/non-functional requirements, and constraints (PDF in the repo) 
* Use case model: actors (e.g., student/teacher/admin), selected use cases, relationships (include/extend), and structured use case descriptions (in the EA file) 
* Class diagram defining core domain concepts and relationships typical for an e-learning system (users/roles, courses, lessons, assignments, submissions, grading, etc.) 
* Dynamic modeling package with the required UML behavioral diagrams:

  * 3 sequence diagrams for selected use cases
  * 1 collaboration diagram
  * 1 activity diagram
  * 1 state diagram for a chosen class with more complex lifecycle/behavior 

**Repository contents:**
* Enterprise Architect project file with all UML diagrams and use case descriptions
* Vision Document exported as PDF




 
