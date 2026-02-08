#include "Sheep.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Sheep::Sheep(int x, int y, World* world) 
    : Animal(Species::SHEEP, x, y, 4, 4, world, 0, true) {}

Sheep::Sheep(World* world)
    : Animal(Species::SHEEP, 0, 0, 4, 4, world, 0, true) 
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

Sheep::~Sheep() {}

char Sheep::draw() const {
    return 'S';
}

Sheep* Sheep::breed(int x, int y) const {
    Sheep* offspring = new Sheep(x, y, world);
    offspring->setBreedCooldown();
    return offspring;
}

Sheep* Sheep::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Sheep* sheep = new Sheep(s_x, s_y, world);
    sheep->strength = s_strength;
    sheep->initiative = s_initiative;
    sheep->age = s_age;
    sheep->breedCooldown = s_breedCooldown;
    sheep->canBreed = bool(s_canBreed);
    return sheep;
}