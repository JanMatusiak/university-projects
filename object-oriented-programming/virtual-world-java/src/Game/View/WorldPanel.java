package Game.View;

import Game.Model.Animals.*;
import Game.Model.Plants.*;
import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public final class WorldPanel extends JPanel {
    private static final int CELL = 20;
    private World world;

    public WorldPanel(World world) {
        this.world = world;
        mouseListener();
    }

    public void setWorld(World newWorld) {
        this.world = newWorld;
        revalidate();
        repaint();
    }

    @Override protected void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        for (int y = 0; y < world.getHeight(); y++) {
            for (int x = 0; x < world.getWidth(); x++) {
                Organism organism = world.getOrganism(y, x);
                int px = x * CELL;
                int py = y * CELL;

                if (organism != null) {
                    Species species = organism.getSpecies();
                    graphics.setColor(species.displayColor());
                    graphics.fillRect(px, py, CELL, CELL);
                    graphics.setColor(Color.BLACK);
                    graphics.drawRect(px, py, CELL, CELL);
                } else {
                    graphics.setColor(Color.LIGHT_GRAY);
                    graphics.drawRect(px, py, CELL, CELL);
                }
            }
        }
    }

    @Override public Dimension getPreferredSize() {
        return new Dimension(world.getWidth() * CELL,
                world.getHeight() * CELL);
    }

    private void mouseListener() {
        addMouseListener(new MouseAdapter() {
            @Override public void mouseClicked(MouseEvent e) {
                int cellX = e.getX() / CELL;
                int cellY = e.getY() / CELL;
                if (!world.isFree(cellY, cellX)) return;

                JFrame frame = (JFrame) SwingUtilities.getWindowAncestor(WorldPanel.this);

                List<Species> optionsList = new ArrayList<>(Arrays.asList(Species.values()));
                optionsList.remove(Species.HUMAN);
                Species[] options = optionsList.toArray(new Species[0]);

                Species pick = (Species) JOptionPane.showInputDialog(
                        frame,
                        "Pick the organism",
                        "Add Organism",
                        JOptionPane.PLAIN_MESSAGE,
                        null,
                        options,
                        options[0]
                );
                if (pick == null) return;
                switch (pick) {
                    case WOLF -> new Wolf(cellX, cellY, world);
                    case SHEEP -> new Sheep(cellX, cellY, world);
                    case ANTELOPE -> new Antelope(cellX, cellY, world);
                    case TURTLE -> new Turtle(cellX, cellY, world);
                    case FOX -> new Fox(cellX, cellY, world);
                    case BELLADONNA -> new Belladonna(cellX, cellY, world);
                    case GRASS -> new Grass(cellX, cellY, world);
                    case GUARANA -> new Guarana(cellX, cellY, world);
                    case SOSNOWSKYS_HOGWEED -> new SosnowskysHogweed(cellX, cellY, world);
                    case SOW_THISTLE -> new SowThistle(cellX, cellY, world);
                }
                repaint();
            }
        });
    }
}
