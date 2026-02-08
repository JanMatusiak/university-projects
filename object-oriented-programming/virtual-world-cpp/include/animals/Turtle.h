#ifndef TURTLE_H
#define TURTLE_H
#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(int x, int y, World* world);
    Turtle(World* world);
    virtual ~Turtle() override;

    virtual void action() override;
    virtual void collision(Organism* organism) override;
    virtual char draw() const override;
    virtual Turtle* breed(int x, int y) const override;
    
    static Turtle* loadFrom(World* world, std::istream &in);
} ;

#endif