from animals.animal import Animal
from species import Species
import random

class Fox(Animal) :

    def __init__(self, world, x = None, y = None) :
        if x == None and y == None :
            super().__init__(Species.FOX, 0, 0, 3, 7, world)
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
        
        super().__init__(Species.FOX, x, y, 3, 7, world)

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
            destination = self._world.get_organism(newX, newY)
            if destination != None and destination.strength > self.strength : continue
            self.move_organism(newX, newY)
            self._world.report(f"{self.species.display_name()} moved!")
            return
        self._world.report("Fox sensed danger and stayed put!")

    def collision(self, other):
        return super().collision(other)

    def draw_color(self):
        return self.species.color
    
    def breed(self, x, y):
        offspring = Fox(self._world, x, y)
        offspring.set_breed_cooldown()
        return offspring
