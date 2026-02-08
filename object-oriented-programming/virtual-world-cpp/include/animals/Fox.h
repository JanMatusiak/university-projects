#ifndef FOX_H
#define FOX_H
#include "Animal.h"

class Fox : public Animal {
public:
    Fox(int x, int y, World* world);
    Fox(World* world);
    virtual ~Fox() override;

    virtual void action() override;
    virtual char draw() const override;
    virtual Fox* breed(int x, int y) const override;

    static Fox* loadFrom(World* world, std::istream &in);
} ;

#endif