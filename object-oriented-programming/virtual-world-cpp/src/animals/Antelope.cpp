#include "Antelope.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Antelope::Antelope(int x, int y, World* world) 
    : Animal(Species::ANTELOPE, x, y, 9, 5, world, 0, true) {}

Antelope::Antelope(World* world)
    : Animal(Species::ANTELOPE, 0, 0, 9, 5, world, 0, true) 
    {
        int rows = world->getRows();
        int columns = world->getColumns();

        int newX, newY;

        do{
            newX = rand() % rows;
            newY = rand() % columns;
        } while(!world->isFree(newX, newY));

        world->setOrganism(nullptr, x, y);
        x = newX;
        y = newY;
        world->setOrganism(this, x, y);
    }

Antelope::~Antelope() {}

void Antelope::action() {
    if(!canBreed){
        --breedCooldown;
        if(breedCooldown == 0){
            canBreed = true;
        }
    }
    for(int i = 0; i < 4; i++){
        int dx[4] = {0, 2, 0, -2};
        int dy[4] = {2, 0, -2, 0};
        int direction = rand() % 4;
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if (!world->inBounds(newX, newY)) continue;
        moveOrganism(newX, newY);
        world->report("Antelope moved!");
        return;
    }
}

void Antelope::collision(Organism* other){
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
    else{
        if(rand() % 2 == 0){
            if(getStrength() > other->getStrength()){
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
        else {
            int dx[4] = {0, 1, 0, -1};
            int dy[4] = {1, 0, -1, 0};
            int newX, newY;
            for(int i = 0; i < 4; i++){
                newX = getX() + dx[i];
                newY = getY() + dy[i];
                if(world->isFree(newX, newY)){
                    world->setOrganism(other, x, y);
                    x = newX;
                    y = newY;
                    world->setOrganism(this, x, y);
                    world->report("Antelope escaped the fight!");
                    return;
                } else {
                    world->report("There was nowhere to escape - antolope was killed by " + speciesToString(other->getSpecies()));
                    markDead();
                    world->setOrganism(nullptr, x, y);
                    other->moveOrganism(x, y);
                }
            }
        }
    }
}

char Antelope::draw() const {
    return 'A';
}

Antelope* Antelope::breed(int x, int y) const {
    Antelope* offspring = new Antelope(x, y, world);
    offspring->setBreedCooldown();
    return offspring;
}

Antelope* Antelope::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Antelope* antelope = new Antelope(s_x, s_y, world);
    antelope->strength = s_strength;
    antelope->initiative = s_initiative;
    antelope->age = s_age;
    antelope->breedCooldown = s_breedCooldown;
    antelope->canBreed = bool(s_canBreed);
    return antelope;
}