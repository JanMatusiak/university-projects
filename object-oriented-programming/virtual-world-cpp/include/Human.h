#ifndef HUMAN_H
#define HUMAN_H

#include "Animal.h"
#include "World.h"

class Human : public Animal {
private:
    bool abilityActive = false;
    int abilityCooldown = 0;
    int baseStrength = 5;
public:
    Human(int x, int y, World* world);
    virtual ~Human() override;

    virtual void action() override;
    virtual void specialAbility();
    virtual char draw() const override;
    virtual Animal* breed(int x, int y) const override;

    void save(std::ostream &out) const override;
    static Human* loadFrom(World* world, std::istream &in);

} ;

#endif