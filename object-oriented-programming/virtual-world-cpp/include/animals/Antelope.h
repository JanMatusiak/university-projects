#ifndef ANTELOPE_H
#define ANTELOPE_H
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(int x, int y, World* world);
    Antelope(World* world);
    virtual ~Antelope() override;

    virtual void action() override;
    virtual void collision(Organism* organism) override;
    virtual char draw() const override;
    virtual Antelope* breed(int x, int y) const override;

    static Antelope* loadFrom(World* world, std::istream &in);
} ;

#endif