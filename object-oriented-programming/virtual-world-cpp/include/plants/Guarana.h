#ifndef GUARANA_H
#define GUARANA_H
#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(int x, int y, World* world);
    Guarana(World* world);
    virtual ~Guarana() override;

    virtual void collision(Organism* other) override;
    virtual char draw() const override;
    virtual Guarana* sow(int x, int y) const override;

    static Guarana* loadFrom(World* world, std::istream &in);

} ;

#endif