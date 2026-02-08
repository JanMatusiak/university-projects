#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Organism.h"

#define MAX_ORGANISMS 6400
#define LOG_SIZE 20

class Human;

class World {
private:
    Organism*** grid;
    int rows, columns;
    Organism* organisms[MAX_ORGANISMS];
    int organismCount = 0;
    std::string log[LOG_SIZE];
    int logIndex = 0;
    int turn = 0;
    int lastKey = 0;

public:
    World(int rows, int columns);
    ~World();

    bool inBounds(int x, int y) const;
    bool isFree(int x, int y) const;

    int getRows() const;
    int getColumns() const;
    Organism* getOrganism(int x, int y) const;
    void setOrganism(Organism* organism, int x, int y);

    void addOrganism(Organism* organism);
    void removeOrganism(Organism* organism);

    void report(const std::string& message);
    void drawLog() const;

    void drawWorld() const;
    void makeTurn();

    void setLastKey(int k);
    int getLastKey() const; 

    bool saveToFile(const std::string &file) const;
    bool loadFromFile(const std::string &file);

    Human* assignHuman() const;

};

#endif
