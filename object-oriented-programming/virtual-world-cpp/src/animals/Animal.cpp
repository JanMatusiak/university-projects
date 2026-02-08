#include "Animal.h"
#include "World.h"
#include <cstdlib>
#include <string>
#include <iostream>

Animal::Animal(Species species, int x, int y, int strength, int initiative, World* world, int breedCooldown, bool canBreed)
    : Organism(species, x, y, strength, initiative, world, breedCooldown, canBreed) {}

Animal::~Animal() {}

void Animal::action(){
    if(!canBreed){
        --breedCooldown;
        if(breedCooldown == 0){
            canBreed = true;
        }
    }
    for(int i = 0; i < 4; i++){
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int direction = rand() % 4;
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (!world->inBounds(newX, newY)) continue;
        moveOrganism(newX, newY);
        world->report(speciesToString(getSpecies()) + " moved!");
        return;
    }
}

void Animal::collision(Organism* other){
    if(getSpecies() == other->getSpecies()){
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int newX, newY;
        for(int i = 0; i < 4; i++){
            newX = x + dx[i];
            newY = y + dy[i];
            if(world->isFree(newX, newY) && this->checkCanBreed() && other->checkCanBreed()){
                breed(newX, newY);
                this->setBreedCooldown();
                other->setBreedCooldown();
                world->report(speciesToString(getSpecies()) + " offspring appeared!");
                break;
            }
        }
        return;
    }

    else if(getStrength() > other->getStrength()){
        world->report(speciesToString(getSpecies()) + " killed " + speciesToString(other->getSpecies()) + "!");
        other->markDead();
        world->setOrganism(nullptr, x, y);
        x = other->getX();
        y = other->getY();
        world->setOrganism(this, x, y);
    }
    
    else {
        world->report(speciesToString(other->getSpecies()) + " killed " + speciesToString(getSpecies()) + "!");
        markDead();
        world->setOrganism(nullptr, x, y);
        other->moveOrganism(x, y);
    }
}

void Animal::save(std::ostream &out) const {
    out << int(getSpecies()) << ' ' << x << ' ' << y << ' ';
    out << strength << ' ' << initiative << ' ' << age << ' ';
    out << breedCooldown << ' ' << int(canBreed) << '\n';
}


