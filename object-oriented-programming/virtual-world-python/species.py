from enum import Enum
from PyQt5.QtGui import QColor
from importlib import import_module

class Species(Enum):
    HUMAN = ("Human", None, QColor(50, 50, 200))
    WOLF = ("Wolf", "animals.wolf.Wolf", QColor(120, 120, 120))
    SHEEP = ("Sheep", "animals.sheep.Sheep", QColor(240, 240, 240))
    FOX = ("Fox", "animals.fox.Fox", QColor(200, 100, 50))
    TURTLE = ("Turtle", "animals.turtle.Turtle", QColor(0, 150, 0))
    ANTELOPE = ("Antelope", "animals.antelope.Antelope", QColor(200, 200, 50))
    CYBERSHEEP = ("Cybersheep", "animals.cybersheep.Cybersheep", QColor(100, 100, 255))
    GRASS = ("Grass", "plants.grass.Grass", QColor(0, 200, 0))
    SOW_THISTLE = ("Sow Thistle", "plants.sow_thistle.Sow_Thistle", QColor(150,200,150))
    GUARANA = ("Guarana", "plants.guarana.Guarana", QColor(255, 100, 100))
    BELLADONNA = ("Belladonna", "plants.belladonna.Belladonna", QColor(100, 0, 0))
    SOSNOWSKYS_HOGWEED = ("Sosnowsky's Hogweed", "plants.sosnowskys_hogweed.Sosnowskys_Hogweed", QColor(0, 100, 0))

    def __init__(self, display, cls_path, color):
        self.display   = display
        self._cls_path = cls_path
        self.color = color

    def display_name(self):
        return self.display

    def display_color(self):
        return self.color

    @property
    def cls(self):
        if self._cls_path is None:
            return None
        module_path, class_name = self._cls_path.rsplit(".", 1)  
        module = import_module(module_path)
        return getattr(module, class_name)
