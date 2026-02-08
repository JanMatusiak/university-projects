#include "Human.h"
#include "World.h"
#include "Species.h"
#include <cstdio>
#include <iostream>

Human::Human(int x, int y, World* world) 
        : Animal(Species::HUMAN, x, y, 5, 4, world, 0, true),
        abilityActive(false),
        abilityCooldown(0),
        baseStrength(5)
        {}

Human::~Human() {}

void Human::action() {
    int key = world->getLastKey();
    switch (key) {
        case 'U': moveOrganism(x-1, y); break;
        case 'D': moveOrganism(x+1, y); break;
        case 'L': moveOrganism(x, y-1); break;
        case 'R': moveOrganism(x, y+1); break;
        case 'a': specialAbility(); return;
        default:  return;
    }
    if (abilityActive) {
        strength = std::max(strength-1, baseStrength);
        if (strength == baseStrength) {
            abilityActive = false;
            abilityCooldown = 5;
            world->report("Ability effect ended.");
        }
    } else if (abilityCooldown > 0) {
        abilityCooldown--;
    }
}

void Human::specialAbility() {
    if (abilityCooldown > 0 ) {
        world->report("You have to wait for the ability.");
        return;
    } 

    if (abilityActive) {
        world->report("The ability has already been activated.");
        return;
    }

    baseStrength = strength;
    strength+=5;
    abilityActive = true;
    world->report("Ability is now active! Strength increased by 5.");
}

char Human::draw() const {
    return '$';
}

Animal* Human::breed(int, int) const {
    return nullptr;
}

void Human::save(std::ostream &out) const {
    out << int(getSpecies()) << ' ' << x << ' ' << y << ' ';
    out << strength << ' ' << initiative << ' ' << age << ' ';
    out << breedCooldown << ' ' << int(canBreed) << ' ';
    out << int(abilityActive) << ' ' << abilityCooldown << ' ' << baseStrength << '\n';
}

Human* Human::loadFrom(World* world, std::istream &in) {
    int s_x, s_y, s_strength, s_initiative, s_age, s_breedCooldown, s_canBreed, s_abilityActive, s_abilityCooldown, s_baseStrength;
    in >> s_x >> s_y >> s_strength >> s_initiative >> s_age >> s_breedCooldown >> s_canBreed >> s_abilityActive >> s_abilityCooldown >> s_baseStrength;
    Human* human = new Human(s_x, s_y, world);
    human->strength = s_strength;
    human->initiative = s_initiative;
    human->age = s_age;
    human->breedCooldown = s_breedCooldown;
    human->canBreed = bool(s_canBreed);
    human->abilityActive = bool(s_abilityActive);
    human->abilityCooldown = s_abilityCooldown;
    human->baseStrength = s_baseStrength;
    return human;
}
