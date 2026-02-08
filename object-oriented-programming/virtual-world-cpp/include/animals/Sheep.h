#ifndef SHEEP_H
#define SHEEP_H
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(int x, int y, World* world);
    Sheep(World* world);
    virtual ~Sheep() override;

    virtual char draw() const override;
    virtual Sheep* breed(int x, int y) const override;

    static Sheep* loadFrom(World* world, std::istream &in);
} ;

#endif