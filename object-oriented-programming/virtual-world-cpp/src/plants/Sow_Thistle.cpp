#include "Sow_Thistle.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Sow_Thistle::Sow_Thistle(int x, int y, World* world)
    : Plant(Species::SOW_THISTLE, x, y, 0, world, 3) {}

Sow_Thistle::Sow_Thistle(World* world)
    : Plant(Species::SOW_THISTLE, 0, 0, 0, world, 3) 
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

Sow_Thistle::~Sow_Thistle() {}

char Sow_Thistle::draw() const {
    return 'H';
}

Sow_Thistle* Sow_Thistle::sow(int x, int y) const {
    return new Sow_Thistle(x, y, world);
}

Sow_Thistle* Sow_Thistle::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Sow_Thistle* sow_thistle = new Sow_Thistle(s_x, s_y, world);
    sow_thistle->strength = s_strength;
    sow_thistle->initiative = s_initiative;
    sow_thistle->age = s_age;
    sow_thistle->breedCooldown = s_breedCooldown;
    sow_thistle->canBreed = bool(s_canBreed);
    return sow_thistle;
}