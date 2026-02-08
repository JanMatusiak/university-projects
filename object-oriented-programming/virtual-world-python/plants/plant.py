from abc import abstractmethod
from organism import Organism
import random

class Plant(Organism) :

    def __init__(self, species, x, y, strength, world, attempts):
        super().__init__(species, x, y, strength, 0, world, True, 0)
        self._sow_attempts = attempts

    
    def action(self) :
        dy = [1, 0, -1, 0]
        dx = [0, 1, 0, -1]
        for i in range(4) :
            direction = random.randint(0, 3)
            newY = self.y + dy[direction]
            newX = self.x + dx[direction]
            if(self._world.in_bounds(newX, newY) and self._world.get_organism(newX, newY) == None and random.randint(0, 1) % 2 == 0) :
                self.sow(newX, newY)
                return
    
    def collision(self, other) :
        self._world.report(f"{other.species.display_name()} ate {self._species.display_name()}!")
        self.mark_dead()
        self._world.set_organism(None, self.x, self.y)
        other.move_organism(self.x, self.y)

    @abstractmethod
    def sow(x, y) :
        pass
    