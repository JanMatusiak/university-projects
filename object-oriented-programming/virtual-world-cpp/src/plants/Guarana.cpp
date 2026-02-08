#include "Guarana.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Guarana::Guarana(int x, int y, World* world)
    : Plant(Species::GUARANA, x, y, 0, world, 1) {}

Guarana::Guarana(World* world)
    : Plant(Species::GUARANA, 0, 0, 0, world, 1) 
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

Guarana::~Guarana() {}

void Guarana::collision(Organism* other){
    world->report((speciesToString(other->getSpecies())) + " ate " + (speciesToString(getSpecies())));
    markDead();
    world->setOrganism(nullptr, x, y);
    other->moveOrganism(x, y);
    other->incrementStrength(3);
    world->report(speciesToString(other->getSpecies()) + " got its strength incremented by 3!");
}

char Guarana::draw() const {
    return 'U';
}

Guarana* Guarana::sow(int x, int y) const {
    return new Guarana(x, y, world);
}

Guarana* Guarana::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Guarana* guarana = new Guarana(s_x, s_y, world);
    guarana->strength = s_strength;
    guarana->initiative = s_initiative;
    guarana->age = s_age;
    guarana->breedCooldown = s_breedCooldown;
    guarana->canBreed = bool(s_canBreed);
    return guarana;
}