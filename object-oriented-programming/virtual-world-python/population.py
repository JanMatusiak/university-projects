from animals.wolf import Wolf
from plants.grass import Grass
from animals.sheep import Sheep
from plants.sow_thistle import Sow_Thistle
from animals.fox import Fox
from plants.guarana import Guarana
from animals.turtle import Turtle
from plants.belladonna import Belladonna
from animals.antelope import Antelope
from plants.sosnowskys_hogweed import Sosnowskys_Hogweed
from animals.cybersheep import Cybersheep

class Population :
    def __init__(self, world):
        for i in range(2) :
            Sheep(world)
            Turtle(world)
            Antelope(world)
            Fox(world)

        Wolf(world)
        Grass(world)
        Sow_Thistle(world)
        Guarana(world)
        Belladonna(world)
        Sosnowskys_Hogweed(world)
        Cybersheep(world)