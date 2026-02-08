#include "Belladonna.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Belladonna::Belladonna(int x, int y, World* world)
    : Plant(Species::BELLADONNA, x, y, 99, world, 1) {}

Belladonna::Belladonna(World* world)
    : Plant(Species::BELLADONNA, 0, 0, 99, world, 1) 
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

Belladonna::~Belladonna() {}

void Belladonna::collision(Organism* other){
    world->report("Belladonna killed " + speciesToString(other->getSpecies()) + "!");
    markDead();
    other->markDead();
    world->setOrganism(nullptr, x, y);
    world->setOrganism(nullptr, other->getX(), other->getY());
}

char Belladonna::draw() const {
    return 'B';
}

Belladonna* Belladonna::sow(int x, int y) const {
    return new Belladonna(x, y, world);
}

Belladonna* Belladonna::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Belladonna* belladonna = new Belladonna(s_x, s_y, world);
    belladonna->strength = s_strength;
    belladonna->initiative = s_initiative;
    belladonna->age = s_age;
    belladonna->breedCooldown = s_breedCooldown;
    belladonna->canBreed = bool(s_canBreed);
    return belladonna;
}