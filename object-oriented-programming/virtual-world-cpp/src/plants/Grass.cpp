#include "Grass.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Grass::Grass(int x, int y, World* world)
    : Plant(Species::GRASS, x, y, 0, world, 1) {}

Grass::Grass(World* world)
    : Plant(Species::GRASS, 0, 0, 0, world, 1) 
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

Grass::~Grass() {}

char Grass::draw() const {
    return 'G';
}

Grass* Grass::sow(int x, int y) const {
    return new Grass(x, y, world);
}

Grass* Grass::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Grass* grass = new Grass(s_x, s_y, world);
    grass->strength = s_strength;
    grass->initiative = s_initiative;
    grass->age = s_age;
    grass->breedCooldown = s_breedCooldown;
    grass->canBreed = bool(s_canBreed);
    return grass;
}