from animals.animal import Animal
from species import Species
import random

class Wolf(Animal) :

    def __init__(self, world, x = None, y = None) :
        if x == None and y == None :
            super().__init__(Species.WOLF, 0, 0, 9, 5, world)
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
        
        super().__init__(Species.WOLF, x, y, 9, 5, world)

    def action(self) :
        return super().action()

    def collision(self, other):
        return super().collision(other)

    def draw_color(self):
        return self.species.color
    
    def breed(self, x, y):
        offspring = Wolf(self._world, x, y)
        offspring.set_breed_cooldown()
        return offspring
