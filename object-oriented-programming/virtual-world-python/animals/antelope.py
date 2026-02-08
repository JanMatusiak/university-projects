from animals.animal import Animal
from species import Species
import random

class Antelope(Animal) :

    def __init__(self, world, x = None, y = None) :
        if x == None and y == None :
            super().__init__(Species.ANTELOPE, 0, 0, 4, 4, world)
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
        
        super().__init__(Species.ANTELOPE, x, y, 4, 4, world)

    def action(self) :
        if not self._can_breed :
            self._breed_cooldown-=1
            if self._breed_cooldown == 0 :
                self._can_breed = True

        dy = [2, 0, -2, 0]
        dx = [0, 2, 0, -2]
        for i in range(4) :
            direction = random.randint(0, 3)
            newX = self._x + dx[direction]
            newY = self._y + dy[direction]
            if not self._world.in_bounds(newX, newY) : continue
            self.move_organism(newX, newY)
            self._world.report("Antelope moved!")
            return

    def collision(self, other):
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
        else :
            if random.randint(0, 1) == 0 :
                if self.strength > other.strength :
                    self._world.report(f"Antelope killed {other.species.display_name()}!")
                    other.mark_dead()
                    self._world.set_organism(None, self.x, self.y)
                    self._y = other.y
                    self._x = other.x
                    self._world.set_organism(self, self.x, self.y)
                else :
                    self._world.report(f"{other.species.display_name()} killed Antelope!")
                    self.mark_dead()
                    self._world.set_organism(None, self.x, self.y)
                    other.move_organism(self.x, self.y)
            else :
                for i in range(4) :
                    newY = self.y + dy[i]
                    newX = self.x + dx[i]
                    if self._world.is_free(newX, newY) :
                        self._world.set_organism(other, self.x, self.y)
                        x = newX
                        y = newY
                        self._world.set_organism(self, self.x, self.y)
                        self._world.report("Antelope escaped the fight")
                        return
                    else :
                        self._world.report(f"There was nowhere to escape - Antelope was killed by {other.species.display_name()}")
                        self.mark_dead()
                        self._world.set_organism(None, self.x, self.y)
                        other.move_organism(self.x, self.y)

    def draw_color(self):
        return self.species.color
    
    def breed(self, x, y):
        offspring = Antelope(self._world, x, y)
        offspring.set_breed_cooldown()
        return offspring
