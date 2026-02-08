from plants.plant import Plant
from species import Species
import random

class Sosnowskys_Hogweed(Plant) :

    def __init__(self, world, x = None, y = None) :
        if x == None and y == None :
            super().__init__(Species.SOSNOWSKYS_HOGWEED, 0, 0, 10, world, 1)
            width = world.width
            height = world.height

            while(True):
                new_x = random.randint(0, width - 1)
                new_y = random.randint(0, height - 1)
                if self._world.is_free(new_x, new_y) :
                    break
                else :
                    continue

            self._world.set_organism(None, self.x, self.y)
            self._x = new_x
            self._y = new_y
            self._world.set_organism(self, self.x, self.y)
            return
        
        super().__init__(Species.SOSNOWSKYS_HOGWEED, x, y, 10, world, 1)

    def action(self) :
        dx = [0, 1, 1, 1, 0, -1, -1, -1]
        dy = [1, 1, 0, -1, -1, -1, 0, 1]
        dx2 = [0, 1, 0, -1]
        dy2 = [1, 0, -1, 0]
        for i in range(8) :
            newX = self.x + dx[i]
            newY = self.y + dy[i]
            if self._world.in_bounds(newX, newY) == False : continue 
            neighbour = self._world.get_organism(newX, newY)
            if neighbour != None and neighbour.species != Species.SOSNOWSKYS_HOGWEED and neighbour.species != Species.BELLADONNA and neighbour.species != Species.GUARANA and neighbour.species != Species.SOW_THISTLE and neighbour.species != Species.GRASS and neighbour.species != Species.CYBERSHEEP :
                self._world.report(f"Sosnowsky's Hogweed killed {neighbour.species.display_name()} !")
                neighbour.mark_dead()
                self._world.set_organism(None, newX, newY)
        
        for i in range(self._sow_attempts) : 
            direction = random.randint(0, 3)
            newX = self.x + dx2[direction]
            newY = self.y + dy2[direction]
            if self._world.in_bounds(newX, newY) and self._world.get_organism(newX, newY) == None and random.randint(0, 2) == 0 :
                self.sow(newX, newY)
                return

    def collision(self, other):
        return super().collision(other)

    def draw_color(self):
        return self.species.color
    
    def sow(self, x, y):
        return Sosnowskys_Hogweed(self._world, x, y)
