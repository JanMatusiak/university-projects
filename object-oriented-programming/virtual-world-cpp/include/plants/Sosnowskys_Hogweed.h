#ifndef SOSNOWSKYS_HOGWEED_H
#define SOSNOWSKYS_HOGWEED_H
#include "Plant.h"

class Sosnowskys_Hogweed : public Plant {
public:
    Sosnowskys_Hogweed(int x, int y, World* world);
    Sosnowskys_Hogweed(World* world);
    virtual ~Sosnowskys_Hogweed() override;

    virtual void action() override;
    virtual void collision(Organism* other) override;
    virtual char draw() const override;
    virtual Sosnowskys_Hogweed* sow(int x, int y) const override;

    static Sosnowskys_Hogweed* loadFrom(World* world, std::istream &in);

} ;

#endif