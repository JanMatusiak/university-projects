#ifndef BELLADONNA_H
#define BELLADONNA_H
#include "Plant.h"

class Belladonna : public Plant {
public:
    Belladonna(int x, int y, World* world);
    Belladonna(World* world);
    virtual ~Belladonna() override;

    virtual void collision(Organism* other) override;
    virtual char draw() const override;
    virtual Belladonna* sow(int x, int y) const override;

    static Belladonna* loadFrom(World* world, std::istream &in);

} ;

#endif