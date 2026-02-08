#ifndef PLANT_H
#define PLANT_H
#include "Organism.h"
#include "World.h"

class Plant : public Organism {
protected:
    int sowAttempts;
public:
    Plant(Species species, int x, int y, int strength, World* world, int attempts);
    virtual ~Plant() override;

    virtual void action() override;
    virtual void collision(Organism* other) override;
    virtual Plant* sow(int x, int y) const = 0;
    void save(std::ostream &out) const override;
} ; 

#endif