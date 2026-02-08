#include "World.h"
#include "Human.h"
#include <iostream>
#include <fstream>
using namespace std;

World::World(int rows, int columns) : rows(rows), columns(columns) {
    grid = new Organism**[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new Organism*[columns];
        for (int j = 0; j < columns; j++) {
            grid[i][j] = nullptr;
        }
    }
}

World::~World() {
    for (int i = 0; i < organismCount; ++i) {
        delete organisms[i];
    }
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

bool World::inBounds(int x, int y) const {
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}

bool World::isFree(int x, int y) const {
    return inBounds(x, y) && grid[x][y] == nullptr;
}

int World::getRows() const {
    return rows;
}

int World::getColumns() const {
    return columns;
}

Organism* World::getOrganism(int x, int y) const {
    if (!inBounds(x,y)) return nullptr;
    return grid[x][y];
}

void World::setOrganism(Organism* organism, int x, int y) {
    if (inBounds(x,y)) {
        grid[x][y] = organism;
    }
}

void World::addOrganism(Organism* organism) {
    if (organismCount < MAX_ORGANISMS) {
        organisms[organismCount++] = organism;
    } else {
        report("No more organisms can be added.");
    }
}

void World::removeOrganism(Organism* organism) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j] == organism) {
                grid[i][j] = nullptr;
            }
        }
    }

    for (int i = 0; i < organismCount; i++) {
        if (organisms[i] == organism) {
            delete organisms[i];
            organisms[i] = organisms[organismCount - 1];
            organisms[organismCount - 1] = nullptr;
            --organismCount;
            return;
        }
    }
}

void World::report(const string& message) {
    log[logIndex] = message;
    if (++logIndex == LOG_SIZE) logIndex = 0;
}

void World::drawLog() const {
    int idx = logIndex;
    for (int i = 0; i < LOG_SIZE; i++) {
        const string& line = log[idx];
        if (!line.empty()) {
            cout << line << "\n";
        }
        if (++idx == LOG_SIZE) idx = 0;
    }
}

void World::drawWorld() const {
    cout << "\x1B[2J\x1B[H";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (grid[i][j]) {
                cout << grid[i][j]->draw();
            } else {
                cout << '.';
            }
        }
        cout << "\n";
    }
    cout << "Jan Matusiak, 203290" << '\n';
    cout << "Round: " << turn << '\n';
    cout << "---- Events ----\n";
    drawLog();
}

void World::makeTurn() {
    turn++;
    for (int i = 0; i < organismCount - 1; i++) {
        int top = i;
        for (int j = i + 1; j < organismCount; j++) {
            Organism* a = organisms[j];
            Organism* b = organisms[top];
            if (a->getInitiative() > b->getInitiative() || (a->getInitiative() == b->getInitiative() && a->getAge() > b->getAge())) {
                top = j;
            }
        }
        if (top != i) {
            Organism* temp = organisms[i];
            organisms[i] = organisms[top];
            organisms[top] = temp;
        }
    }

    int organismCountNow = organismCount;

    for (int i = 0; i < organismCountNow; i++) {
        Organism* organism = organisms[i];
        if (!organism->isDead()) {
            organism->action();
            organism->incrementAge();
        }
    }

    for (int i = 0; i < organismCount; ) {
        if(organisms[i]->isDead() && organisms[i]->getSpecies() != Species::HUMAN){
            removeOrganism(organisms[i]);
        }
        else {
            i++;
        }
    }
}

void World::setLastKey(int k) {
    lastKey = k; 
}

int World::getLastKey() const { 
    return lastKey; 
}

bool World::saveToFile(const std::string &filename) const {
    std::ofstream out(filename);
    if (!out) return false;
    out << rows << ' ' << columns << '\n';
    out << turn << ' ' << organismCount << '\n';
    for (int i = 0; i < organismCount; i++) {
        organisms[i]->save(out);
    }
    return true;
}

bool World::loadFromFile(const std::string &filename) {
    std::ifstream in(filename);
    if (!in) return false;

    for (int i = 0; i < organismCount; i++) {
        delete organisms[i];
    }
    organismCount = 0;

    for (int i = 0; i < rows; i++) delete[] grid[i];
    delete[] grid;


    int newRows, newCols, newCount;
    in >> newRows >> newCols >> turn >> newCount;
    if (!in) return false;

    rows = newRows;
    columns = newCols;

    grid = new Organism**[rows];

    for (int i = 0; i < rows; i++) {
        grid[i] = new Organism*[columns];
        for (int j = 0; j < columns; j++){
            grid[i][j] = nullptr;
        }
    }

    for (int i = 0; i < newCount; i++) {
        Organism* organism = Organism::load(this, in);
        if (!organism) return false;
    }

    return true;
}

Human* World::assignHuman() const {
    for (int i = 0; i < organismCount; ++i) {
        if (organisms[i]->getSpecies() == Species::HUMAN)
            return static_cast<Human*>(organisms[i]);
    }
    return nullptr;
}
