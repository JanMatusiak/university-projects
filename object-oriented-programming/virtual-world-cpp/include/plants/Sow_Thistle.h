#ifndef SOW_THISTLE_H
#define SOW_THISTLE_H
#include "Plant.h"

class Sow_Thistle : public Plant {
public:
    Sow_Thistle(int x, int y, World* world);
    Sow_Thistle(World* world);
    virtual ~Sow_Thistle() override;

    virtual char draw() const override;
    virtual Sow_Thistle* sow(int x, int y) const override;

    static Sow_Thistle* loadFrom(World* world, std::istream &in);

} ;

#endif