#include "World.h"
#include "Organism.h"
#include "Species.h"
#include "Human.h"
#include "Wolf.h"
#include "Grass.h"
#include "Sheep.h"
#include "Sow_Thistle.h"
#include "Fox.h"
#include "Guarana.h"
#include "Turtle.h"
#include "Belladonna.h"
#include "Antelope.h"
#include "Sosnowskys_Hogweed.h"
#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

#define ROWS 40
#define COLUMNS 160

static int getch() { // proposed by ChatGPT to read input
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int c = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

static int readKey() { // implemented with the help of ChatGPT
    int c = getch();
    if (c == 0x1B && getch() == '[') {            
        switch (getch()) {
            case 'A': return 'U'; 
            case 'B': return 'D'; 
            case 'C': return 'R'; 
            case 'D': return 'L'; 
        }
    } 
    return c;                   
}

int main() {

    std::srand(unsigned(time(nullptr))); 

    World world(ROWS, COLUMNS);

    Human* player = new Human(ROWS/2, COLUMNS/2, &world);

    for(int i = 0; i < 3; i++){
        new Fox(&world);
        new Sheep(&world);
        new Wolf(&world);
        new Antelope(&world);
        new Turtle(&world);
    }

    for(int i = 0; i < 5; i++){
        new Grass(&world);
    }

    new Sow_Thistle(&world);
    new Guarana(&world);
    new Belladonna(&world);
    new Sosnowskys_Hogweed(&world);

    while(true){
        world.drawWorld();

        int key = readKey();  
        if (key == 'q' || key == 'Q') {
            world.report("Thank you for playing!");
            world.drawWorld();
            break; 
        }

        else if (key == 's' || key == 'S') {
            if (world.saveToFile("game.txt")) {
                world.report("Game saved.");
            } else {
                world.report("Save failed!");
            }
            world.drawWorld();
            continue;
        }

        else if (key == 'f' || key == 'F') {
            if (world.loadFromFile("game.txt")) {
                world.report("Game loaded.");
                player = world.assignHuman();
            } else {
                world.report("Load failed!");
            }
            world.drawWorld();
            continue;
        }

        else if(key == 'U' || key == 'D' || key == 'L' || key == 'R' || key == 'a' || key == 'A'){
            int x = player->getX();
            int y = player->getY();
            bool invalidMove = false;
            switch (key) {
                case 'U': if (x == 0) invalidMove = true; break;
                case 'D': if (x == ROWS - 1) invalidMove = true; break;
                case 'L': if (y == 0) invalidMove = true; break;
                case 'R': if (y == COLUMNS - 1) invalidMove = true; break;
                default: break;
            }

            if (invalidMove) {
                world.report("You can't go there!");
                world.setLastKey(0);
                continue;    
            } 
        }

        else {
            world.report("Invalid key - try again.");
            continue;
        }

        world.setLastKey(key);
        world.makeTurn();

        if(player->isDead()){
            world.report("You lost the game!");
            world.drawWorld();
            break;
        }
    }

    return 0;
}