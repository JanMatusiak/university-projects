from PyQt5.QtCore import Qt, QRect
from PyQt5.QtGui  import QPainter, QColor
from PyQt5.QtWidgets import (
    QWidget, QMainWindow, QTextEdit, QLabel, QFileDialog,
    QInputDialog, QVBoxLayout, QHBoxLayout
)
from species import Species
from world import World

CELL = 20

class WorldWidget(QWidget):
    def __init__(self, world):
        super().__init__()
        self.world = world
        self.setFixedSize(world.width * CELL, world.height * CELL)

    def paintEvent(self, event):
        painter = QPainter(self)
        for x in range(self.world.width):
            for y in range(self.world.height):
                org = self.world.get_organism(x, y)
                board = QRect(x * CELL, y * CELL, CELL, CELL)
                if org:
                    painter.fillRect(board, org.species.display_color())
                    painter.setPen(Qt.black)
                else:
                    painter.setPen(Qt.lightGray)
                painter.drawRect(board)

    def mousePressEvent(self, event):
        cell_x, cell_y = event.x()//CELL, event.y()//CELL
        if not self.world.is_free(cell_x, cell_y):
            return

        options = [species for species in Species if species.cls is not None]
        items = [species.display for species in options]

        choice, ok = QInputDialog.getItem(
            self,
            "Add Organism",
            "Which creature?",
            items, 0, False
        )
        if not (ok and choice):
            return

        spec = options[items.index(choice)]
        spec.cls(self.world, cell_x, cell_y)

        self.update()

class MainWindow(QMainWindow):
    def __init__(self, world, player):
        super().__init__()
        self.world = world
        self.player = player
        self.world.add_listener(self.log_message)

        self.widget = WorldWidget(world)
        self.widget.setFocusPolicy(Qt.StrongFocus)
        self.widget.setFocus()
        self.log = QTextEdit()
        self.log.setReadOnly(True)
        self.round = QLabel("Round: 0")

        south = QHBoxLayout()
        south.addWidget(self.round)
        south.addWidget(self.log)

        layout = QVBoxLayout()
        layout.addWidget(self.widget)
        layout.addLayout(south)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)
        self.setWindowTitle("Jan Matusiak, 203290")

    def log_message(self, msg):
        self.log.append(msg)

    def keyPressEvent(self, event):
        if self.player.is_dead():
            return
        
        key = event.key()
        if key == Qt.Key_S:
            path, _ = QFileDialog.getSaveFileName(self, "Save")
            if path:
                self.world.save(path)

        elif key == Qt.Key_L:
            path, _ = QFileDialog.getOpenFileName(self, "Load")
            if path:
                self.world = World.load(path)
                self.world.add_listener(self.log_message)
                self.player = self.world.assign_human()
                self.widget.world = self.world
                self.update_view()
        else:
            accepted = False

            current_x, current_y = self.player.x, self.player.y

            if key in (Qt.Key_Left, Qt.Key_Right, Qt.Key_Up, Qt.Key_Down):
                if key == Qt.Key_Left:
                    new_x, new_y = current_x - 1, current_y
                elif key == Qt.Key_Right:
                    new_x, new_y = current_x + 1, current_y
                elif key == Qt.Key_Up:
                    new_x, new_y = current_x, current_y - 1
                else: 
                    new_x, new_y = current_x, current_y + 1

                if self.world.in_bounds(new_x, new_y):
                    self.world.set_last_key(key)
                    accepted = True
                else:
                    self.world.report("Invalid move!")  
                    accepted = False

            elif key == Qt.Key_A:
                if self.player.can_use_ability():
                    self.world.set_last_key(key)
                    accepted = True
                else:
                    self.world.report("Ability not ready!")
                    accepted = False

            if accepted:
                self.world.make_turn()
                self.update_view()

    def update_view(self):
        self.round.setText(f"Round: {self.world.turn}")
        self.log.setPlainText("\n".join(self.world.get_history()))
        self.widget.update()
