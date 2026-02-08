#include "Turtle.h"
#include "World.h"
#include "Species.h"
#include <cstdlib>
#include <iostream>

Turtle::Turtle(int x, int y, World* world) 
    : Animal(Species::TURTLE, x, y, 2, 1, world, 0, true) {}

Turtle::Turtle(World* world)
    : Animal(Species::TURTLE, 0, 0, 2, 1, world, 0, true) 
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

Turtle::~Turtle() {}

void Turtle::action() {
    if(rand() % 4 == 0){
        Animal::action();
    } else {
        if(!canBreed){
            --breedCooldown;
            if(breedCooldown == 0){
                canBreed = true;
            }
        }
        world->report("Turtle stayed put!");
    }
}

void Turtle::collision(Organism* other) {
    if(other->getStrength() < 5 && other->getSpecies() != Species::TURTLE){
        world->report("Turtle defended itself against " + speciesToString(other->getSpecies()));
        return;
    } 
    Animal::collision(other);
}

char Turtle::draw() const {
    return 'T';
}

Turtle* Turtle::breed(int x, int y) const {
    Turtle* offspring = new Turtle(x, y, world);
    offspring->setBreedCooldown();
    return offspring;
}

Turtle* Turtle::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Turtle* turtle = new Turtle(s_x, s_y, world);
    turtle->strength = s_strength;
    turtle->initiative = s_initiative;
    turtle->age = s_age;
    turtle->breedCooldown = s_breedCooldown;
    turtle->canBreed = bool(s_canBreed);
    return turtle;
}