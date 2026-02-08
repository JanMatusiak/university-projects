#ifndef ORGANISM_H
#define ORGANISM_H

#include "Species.h"

class World;

class Organism {
protected:
    Species species;
    int x, y;
    int strength;
    int initiative;
    int age = 0;
    bool dead = false;
    World* world = nullptr;
    int breedCooldown;
    bool canBreed;

public:
    Organism(Species species, int x, int y, int strength, int initiative, World* world, int breedCooldown, bool canBreed);
    virtual ~Organism();

    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual char draw() const = 0;

    void moveOrganism(int newX, int newY);

    int getX() const;
    int getY() const;
    int getStrength() const;
    int getInitiative() const;
    int getAge() const;
    Species getSpecies() const;

    void incrementAge();
    void incrementStrength(int number);

    bool isDead() const;
    void markDead();
    virtual bool checkCanBreed();
    virtual void setBreedCooldown();

    virtual void save(std::ostream &out) const = 0;
    static Organism* load(World* world, std::istream &in);
};

#endif 
