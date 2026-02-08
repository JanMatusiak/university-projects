#include "Organism.h"
#include "World.h"
#include <iostream>
#include "Human.h"
#include "Wolf.h"
#include "Grass.h"
#include "Sheep.h"
#include "Sow_Thistle.h"
#include "Fox.h"
#include "Guarana.h"
#include "Turtle.h"
#include "Belladonna.h"
#include "Antelope.h"
#include "Sosnowskys_Hogweed.h"

Organism::Organism(Species species, int x, int y, int strength, int initiative, World* world, int breedCooldown, bool canBreed)
  : species(species), x(x), y(y), strength(strength), initiative(initiative), world(world), breedCooldown(breedCooldown), canBreed(canBreed)
{
    world->setOrganism(this, x, y);
    world->addOrganism(this);
}

Organism::~Organism() {}

void Organism::moveOrganism(int newX, int newY) {
    Organism* occupant = world->getOrganism(newX, newY);
    if (occupant) {
        occupant->collision(this);
    } else {
        world->setOrganism(nullptr, x, y);
        x = newX;
        y = newY;
        world->setOrganism(this, x, y);
    }
}

int Organism::getX() const { return x; }
int Organism::getY() const { return y; }
int Organism::getStrength() const { return strength; }
int Organism::getInitiative() const { return initiative; }
int Organism::getAge() const { return age; }
Species Organism::getSpecies() const { return species; }
void Organism::incrementAge() { age++; }
void Organism::incrementStrength(int number) { strength+=number; }
bool Organism::isDead() const { return dead; }
void Organism::markDead() { dead = true; }
bool Organism::checkCanBreed() { return canBreed; }
void Organism::setBreedCooldown() { 
    breedCooldown = 3; 
    canBreed = false;
}

Organism* Organism::load(World* world, std::istream &in) {
    int s_species;
    in >> s_species;                
    Species species = static_cast<Species>(s_species);
    switch (species) {
        case Species::HUMAN: return Human::loadFrom(world, in);
        case Species::WOLF: return Wolf::loadFrom(world, in);
        case Species::SHEEP: return Sheep::loadFrom(world, in);
        case Species::FOX: return Fox::loadFrom(world, in);
        case Species::TURTLE: return Turtle::loadFrom(world, in);
        case Species::ANTELOPE: return Antelope::loadFrom(world, in);
        case Species::GRASS: return Grass::loadFrom(world, in);
        case Species::SOW_THISTLE: return Sow_Thistle::loadFrom(world, in);
        case Species::GUARANA: return Guarana::loadFrom(world, in);
        case Species::BELLADONNA: return Belladonna::loadFrom(world, in);
        case Species::SOSNOWSKYS_HOGWEED: return Sosnowskys_Hogweed::loadFrom(world, in);
    }
    return nullptr;
}
