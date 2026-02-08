#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"
#include "World.h"

class Animal : public Organism {
public:
    Animal(Species species, int x, int y, int strength, int initiative, World* world, int breedCooldown, bool canBreed);
    virtual ~Animal() override;

    virtual void action() override;
    virtual void collision(Organism* other) override;
    virtual Animal* breed(int x, int y) const = 0;
    void save(std::ostream &out) const override;
} ;

#endif