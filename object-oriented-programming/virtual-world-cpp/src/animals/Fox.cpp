#include "Fox.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Fox::Fox(int x, int y, World* world) 
    : Animal(Species::FOX, x, y, 3, 7, world, 0, true) {}

Fox::Fox(World* world)
    : Animal(Species::FOX, 0, 0, 3, 7, world, 0, true) 
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

Fox::~Fox() {}

void Fox::action() {
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
        Organism* destination = world->getOrganism(newX, newY);
        if(destination && destination->getStrength() > getStrength()){
            continue;
        }
        moveOrganism(newX, newY);
        world->report("Fox moved!");
        return;
    }
    world->report("Fox sensed danger and stayed put!");
}

char Fox::draw() const {
    return 'F';
}

Fox* Fox::breed(int x, int y) const {
    Fox* offspring = new Fox(x, y, world);
    offspring->setBreedCooldown();
    return offspring;
}

Fox* Fox::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Fox* fox = new Fox(s_x, s_y, world);
    fox->strength = s_strength;
    fox->initiative = s_initiative;
    fox->age = s_age;
    fox->breedCooldown = s_breedCooldown;
    fox->canBreed = bool(s_canBreed);
    return fox;
}