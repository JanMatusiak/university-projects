#ifndef WOLF_H
#define WOLF_H
#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(int x, int y, World* world);
    Wolf(World* world);
    virtual ~Wolf() override;

    virtual char draw() const override;
    virtual Wolf* breed(int x, int y) const override;

    static Wolf* loadFrom(World* world, std::istream &in);
} ;

#endif