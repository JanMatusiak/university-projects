#include "Sosnowskys_Hogweed.h"
#include "World.h"
#include "Species.h"
#include <iostream>

Sosnowskys_Hogweed::Sosnowskys_Hogweed(int x, int y, World* world)
    : Plant(Species::SOSNOWSKYS_HOGWEED, x, y, 10, world, 1) {}

Sosnowskys_Hogweed::Sosnowskys_Hogweed(World* world)
    : Plant(Species::SOSNOWSKYS_HOGWEED, 0, 0, 10, world, 1) 
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

Sosnowskys_Hogweed::~Sosnowskys_Hogweed() {}

void Sosnowskys_Hogweed::action(){
    int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int newX, newY;
    for(int i = 0; i < 8; i++){
        newX = getX() + dx[i];
        newY = getY() + dy[i];
        if(!world->inBounds(newX, newY)) continue; 
        Organism* neighbour = world->getOrganism(newX, newY);
        if(neighbour && (neighbour->getSpecies() != Species::SOSNOWSKYS_HOGWEED && 
                        neighbour->getSpecies() != Species::BELLADONNA && 
                        neighbour->getSpecies() != Species::GUARANA && 
                        neighbour->getSpecies() != Species::SOW_THISTLE && 
                        neighbour->getSpecies() != Species::GRASS)){
            world->report("Sosnowsky's Hogweed killed " + speciesToString(neighbour->getSpecies()) + "!");
            neighbour->markDead();
            world->setOrganism(nullptr, newX, newY);
        }
    }

    for(int i = 0; i < sowAttempts; i++){
        int direction = rand() % 4;
        int newX = x + dx[direction];
        int newY = y + dy[direction];
        if(world->inBounds(newX, newY) && world->getOrganism(newX, newY) == nullptr && rand() % 2 == 0){
            sow(newX, newY);
            return;
        }
    }
}

void Sosnowskys_Hogweed::collision(Organism* other){
    world->report((speciesToString(other->getSpecies())) + " ate " + (speciesToString(getSpecies())) + " and died!");
    markDead();
    other->markDead();
    world->setOrganism(nullptr, x, y);
    world->setOrganism(nullptr, other->getX(), other->getY());
}

char Sosnowskys_Hogweed::draw() const {
    return 'O';
}

Sosnowskys_Hogweed* Sosnowskys_Hogweed::sow(int x, int y) const {
    return new Sosnowskys_Hogweed(x, y, world);
}

Sosnowskys_Hogweed* Sosnowskys_Hogweed::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed;
    Sosnowskys_Hogweed* sosnowskys_hogweed = new Sosnowskys_Hogweed(s_x, s_y, world);
    sosnowskys_hogweed->strength = s_strength;
    sosnowskys_hogweed->initiative = s_initiative;
    sosnowskys_hogweed->age = s_age;
    sosnowskys_hogweed->breedCooldown = s_breedCooldown;
    sosnowskys_hogweed->canBreed = bool(s_canBreed);
    return sosnowskys_hogweed;
}