#ifndef SPECIES_H
#define SPECIES_H
#include <string>

enum Species {
    HUMAN,
    WOLF,
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    GRASS,
    SOW_THISTLE,
    GUARANA,
    BELLADONNA,
    SOSNOWSKYS_HOGWEED
} ;

inline std::string speciesToString(Species s) {
    switch (s) {
        case Species::HUMAN:             return "Human";
        case Species::WOLF:              return "Wolf";
        case Species::SHEEP:             return "Sheep";
        case Species::FOX:               return "Fox";
        case Species::TURTLE:            return "Turtle";
        case Species::ANTELOPE:          return "Antelope";
        case Species::GRASS:             return "Grass";
        case Species::SOW_THISTLE:       return "Sow Thistle";
        case Species::GUARANA:           return "Guarana";
        case Species::BELLADONNA:        return "Belladonna";
        case Species::SOSNOWSKYS_HOGWEED:return "Sosnowsky's Hogweed";
    }
    return "Unknown";
}

#endif 