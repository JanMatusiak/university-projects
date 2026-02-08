from collections import deque
import pickle
from species import Species

class World :
    LOG_SIZE = 50

    def __init__(self, width, height) :
        self._width = width
        self._height = height
        self.grid = [[None]*height for _ in range(width)]
        self.organisms = []
        self._turn = 0
        self.history = deque(maxlen = self.LOG_SIZE)
        self.listener = None
        self._last_key = 0

    @property
    def width(self) :
        return self._width
    
    @property
    def height(self) :
        return self._height
    
    @property
    def turn(self) :
        return self._turn
    
    def in_bounds(self, x, y) :
        return (0 <= x < self._width and 0 <= y < self._height)
    
    def is_free(self, x, y) :
        return (self.in_bounds(x,y) and self.grid[x][y] is None)
    
    def get_organism(self, x, y) :
        return (self.grid[x][y] if self.in_bounds(x, y) else None)
    
    def set_organism(self, organism, x, y) :
        self.grid[x][y] = organism

    def add_organism(self, organism) :
        self.organisms.append(organism)

    def report(self, msg: str):
        self.history.append(msg)
        if self.listener: self.listener(msg)

    def add_listener(self, fn):
        self.listener = fn

    def get_history(self):
        return list(self.history)

    def make_turn(self):
        self._turn += 1
        for org in list(self.organisms):
            if not org.is_dead():
                org.action()
                org.increment_age()

        survivors = []
        for org in self.organisms:
            if org.is_dead():
                if self.get_organism(org.x, org.y) is org:
                    self.set_organism(None, org.x, org.y)
            else:
                survivors.append(org)
        self.organisms = survivors


    def set_last_key(self, key) :
        self._last_key = key

    def get_last_key(self) :
        return self._last_key
    
    def save(self, path):
            saved_listener = self.listener
            self.listener = None

            with open(path, "wb") as f:
                pickle.dump(self, f)

            self.listener = saved_listener


    @classmethod
    def load(cls, path) :
        with open(path, "rb") as file:
            world = pickle.load(file)

        world.listener = None
        return world
    
    def assign_human(self):
        for org in self.organisms:
            if org.species == Species.HUMAN:
                return org
        raise RuntimeError("No human found in loaded world!")

