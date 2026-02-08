from abc import abstractmethod
from organism import Organism
import random

class Animal(Organism) :

    def __init__(self, species, x, y, strength, initiative, world):
        super().__init__(species, x, y, strength, initiative, world, True, 0)

    
    def action(self) :
        if not self._can_breed :
            self._breed_cooldown-=1
            if self._breed_cooldown == 0 :
                self._can_breed = True

        dy = [1, 0, -1, 0]
        dx = [0, 1, 0, -1]
        for i in range(4) :
            direction = random.randint(0, 3)
            newX = self._x + dx[direction]
            newY = self._y + dy[direction]
            if not self._world.in_bounds(newX, newY) : continue
            self.move_organism(newX, newY)
            self._world.report(f"{self.species.display_name()} moved!")
            return
    
    def collision(self, other) :
        dy = [1, 0, -1, 0]
        dx = [0, 1, 0, -1]
        if self.species == other.species :
            for i in range(4) :
                newY = self.y + dy[i]
                newX = self.x + dx[i]
                if (self._world.is_free(newX, newY) and self.check_can_breed() and other.check_can_breed()) :
                    self.breed(newX, newY)
                    self.set_breed_cooldown()
                    other.set_breed_cooldown()
                    self._world.report(f"{self._species.display_name()} offspring appeared!")
                    break
        elif(self.strength > other.strength) :
            self._world.report(f"{self.species.display_name()} killed {other.species.display_name()}!")
            other.mark_dead()
            self._world.set_organism(None, self.x, self.y)
            self._y = other.y
            self._x = other.x
            self._world.set_organism(self, self.x, self.y)
        else :
            self._world.report(other.species.display_name() + " killed " + self.species.display_name() + "!")
            self.mark_dead()
            self._world.set_organism(None, self.x, self.y)
            other.move_organism(self.x, self.y)

    @abstractmethod
    def breed(self, x, y) :
        pass
    