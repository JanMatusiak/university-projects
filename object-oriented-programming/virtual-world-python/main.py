import sys
from PyQt5.QtWidgets import QApplication
from world import World
from human import Human
from view import MainWindow
from population import Population

if __name__=="__main__":
    app = QApplication(sys.argv)
    world = World(70, 34)
    human = Human(world.width // 2, world.height // 2, world)
    Population(world)
    main = MainWindow(world, human)
    main.show()
    main.setFocus()
    sys.exit(app.exec_())
