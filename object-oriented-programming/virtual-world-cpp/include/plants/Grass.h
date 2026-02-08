#ifndef GRASS_H
#define GRASS_H
#include "Plant.h"

class Grass : public Plant {
public:
    Grass(int x, int y, World* world);
    Grass(World* world);
    virtual ~Grass() override;

    virtual char draw() const override;
    virtual Grass* sow(int x, int y) const override;

    static Grass* loadFrom(World* world, std::istream &in);

} ;

#endif