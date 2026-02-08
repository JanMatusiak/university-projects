# human.py

from PyQt5.QtCore import Qt
from animals.animal import Animal
from species import Species
from math import inf

class Human(Animal):
    def __init__(self, x, y, world):
        super().__init__(Species.HUMAN, x, y, 5, 4, world)
        self._ability_active = False
        self._ability_cooldown = 0
        self._base_strength = self.strength

    def action(self):
        key = self._world.get_last_key()
        if key == 0:
            return self._world.set_last_key(0)
        if key == Qt.Key_Left:
            self.move_organism(self.x - 1, self.y)
        elif key == Qt.Key_Right:
            self.move_organism(self.x + 1, self.y)
        elif key == Qt.Key_Up:
            self.move_organism(self.x, self.y - 1)
        elif key == Qt.Key_Down:
            self.move_organism(self.x, self.y + 1)
        elif key == Qt.Key_A:
            self.special_ability()
            return
        else:
            return

        if self._ability_active:
            self._strength = max(self._strength - 1, self._base_strength)
            if self._strength == self._base_strength:
                self._ability_active = False
                self._ability_cooldown = 5
                self._world.report("Ability effect ended.")
        elif self._ability_cooldown > 0:
            self._ability_cooldown -= 1

    def can_use_ability(self) :
        return self._ability_active == False and self._ability_cooldown == 0

    @property
    def ability_active(self) :
        return self._ability_active

    @property
    def ability_cooldown(self) :
        return self._ability_cooldown

    def special_ability(self) :
        self._base_strength = self._strength
        self._strength += 5
        self._ability_active = True
        self._world.report("Ability is now active! Strength increased by 5.")

    def draw_color(self):
        return self.species.color

    def breed(self, x, y):
        return None
