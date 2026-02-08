#include "Plant.h"
#include "World.h"
#include <cstdlib>
#include <string>
#include <iostream>

Plant::Plant(Species species, int x, int y, int strength, World* world, int attempts)
    : Organism(species, x, y, strength, 0, world, 0, true),
      sowAttempts(attempts) {}

Plant::~Plant() {}

void Plant::action(){
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    for(int i = 0; i < sowAttempts; i++){
        int direction = rand() % 4;
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if(world->inBounds(newX, newY) && world->getOrganism(newX, newY) == nullptr && rand() % 2 == 0){
            sow(newX, newY);
            return;
        }
    }
}

void Plant::collision(Organism* other){
    world->report((speciesToString(other->getSpecies())) + " ate " + (speciesToString(getSpecies())));
    markDead();
    world->setOrganism(nullptr, x, y);
    other->moveOrganism(x, y);
}

void Plant::save(std::ostream &out) const {
    out << int(getSpecies()) << ' ' << x << ' ' << y << ' ';
    out << strength << ' ' << initiative << ' ' << age << ' ';
    out << breedCooldown << ' ' << int(canBreed) << '\n';
}