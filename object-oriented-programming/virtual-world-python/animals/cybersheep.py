from animals.animal import Animal
from species import Species
import random

class Cybersheep(Animal) :

    def __init__(self, world, x = None, y = None) :
        if x == None and y == None :
            super().__init__(Species.CYBERSHEEP, 0, 0, 11, 4, world)
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
        
        super().__init__(Species.CYBERSHEEP, x, y, 11, 4, world)

    def action(self):
        hogweeds = [
            (org.x, org.y)
            for org in self._world.organisms
            if org.species == Species.SOSNOWSKYS_HOGWEED
        ]

        if not hogweeds:
            super().action()
            return

        current_x, current_y = self.x, self.y
        closest_x, closest_y = min(
            hogweeds,
            key=lambda p: abs(p[0] - current_x) + abs(p[1] - current_y)
        )

        dx = 0 if closest_x == current_x else (1 if closest_x > current_x else -1)
        dy = 0 if closest_y == current_y else (1 if closest_y > current_y else -1)
        new_x, new_y = current_x + dx, current_y + dy

        if self._world.in_bounds(new_x, new_y):
            self.move_organism(new_x, new_y)
            self._world.report(f"{self.species.display_name()} moves toward Sosnowsky's Hogweed!")
        else:
            return

    def collision(self, other):
        if other.species == Species.SOSNOWSKYS_HOGWEED :
            self._world.report("Cybersheep ate Sosnowsky's Hogweed!")
            other.mark_dead()
            self._world.set_organism(None, self.x, self.y)
            self._y = other.y
            self._x = other.x
            self._world.set_organism(self, self.x, self.y)
        else :
            return super().collision(other)

    def draw_color(self):
        return self.species.color
    
    def breed(self, x, y):
        return None
