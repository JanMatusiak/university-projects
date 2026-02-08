#include "Wolf.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Wolf::Wolf(int x, int y, World* world) 
    : Animal(Species::WOLF, x, y, 9, 5, world, 0, true) {}

Wolf::Wolf(World* world)
    : Animal(Species::WOLF, 0, 0, 9, 5, world, 0, true) 
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

Wolf::~Wolf() {}

char Wolf::draw() const {
    return 'W';
}

Wolf* Wolf::breed(int x, int y) const {
    Wolf* offspring = new Wolf(x, y, world);
    offspring->setBreedCooldown();
    return offspring;
}

Wolf* Wolf::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Wolf* wolf = new Wolf(s_x, s_y, world);
    wolf->strength = s_strength;
    wolf->initiative = s_initiative;
    wolf->age = s_age;
    wolf->breedCooldown = s_breedCooldown;
    wolf->canBreed = bool(s_canBreed);
    return wolf;
}