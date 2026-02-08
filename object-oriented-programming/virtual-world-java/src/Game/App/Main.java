package Game.App;

import Game.Model.Animals.Human;
import Game.Model.Population;
import Game.Model.World;
import Game.View.WorldPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

public final class Main {

    private static final int width = 70;
    private static final int height = 30;
    private static final Path SAVE_PATH = Paths.get("world.save");

    private static World world;
    private static Human player;
    private static WorldPanel panel;
    private static JTextArea logArea;
    private static JTextField roundField;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                createAndShowGui();
            } catch (Exception ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(null,
                        "Error starting application:\n" + ex.getMessage(),
                        "Startup Error", JOptionPane.ERROR_MESSAGE);
            }
        });
    }

    private static void createAndShowGui() {
        world = new World(width, height);
        player = new Human(world.getWidth()/2, world.getHeight()/2, world);
        Population.populate(world);

        JFrame frame = new JFrame("Jan Matusiak 203290");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        panel = new WorldPanel(world);

        logArea = new JTextArea(8, 50);
        logArea.setEditable(false);
        JScrollPane logScroll = new JScrollPane(logArea);

        roundField = new JTextField("Round: 0");
        roundField.setEditable(false);
        roundField.setHorizontalAlignment(JTextField.CENTER);

        JPanel southPanel = new JPanel(new BorderLayout());
        southPanel.add(roundField, BorderLayout.NORTH);
        southPanel.add(logScroll, BorderLayout.CENTER);

        frame.add(panel, BorderLayout.CENTER);
        frame.add(southPanel, BorderLayout.SOUTH);
        frame.pack();
        frame.setVisible(true);

        world.setReportListener(msg -> logArea.append(msg+"\n"));

        panel.setFocusable(true);
        panel.requestFocusInWindow();

        panel.addKeyListener(new KeyAdapter() {
            @Override public void keyPressed(KeyEvent e) {
                boolean accepted = switch (e.getKeyCode()) {
                    case KeyEvent.VK_UP -> {
                        boolean valid = player.getY() > 0;
                        if (valid) world.setLastKey(KeyEvent.VK_UP);
                        yield valid;
                    }
                    case KeyEvent.VK_DOWN -> {
                        boolean valid = player.getY() < world.getHeight() - 1;
                        if (valid) world.setLastKey(KeyEvent.VK_DOWN);
                        yield valid;
                    }
                    case KeyEvent.VK_LEFT -> {
                        boolean valid = player.getX() > 0;
                        if (valid) world.setLastKey(KeyEvent.VK_LEFT);
                        yield valid;
                    }
                    case KeyEvent.VK_RIGHT -> {
                        boolean valid = player.getX() < world.getWidth() - 1;
                        if (valid) world.setLastKey(KeyEvent.VK_RIGHT);
                        yield valid;
                    }
                    case KeyEvent.VK_A -> {
                        if (!player.canUseAbility()) {
                            world.setLastKey(KeyEvent.VK_A);
                            yield true;
                        } else {
                            if(player.getAbilityCooldown()){
                                world.report("You have to wait for the ability!");
                            }
                            else if(player.getAbilityActive()){
                                world.report("The ability is already active!");
                            }
                            world.setLastKey(0);
                            yield false;
                        }
                    }
                    case KeyEvent.VK_S -> {
                        try {
                            world.saveToFile(SAVE_PATH);
                            JOptionPane.showMessageDialog(frame,
                                    "Game saved to:\n" + SAVE_PATH.toAbsolutePath(),
                                    "Successful save", JOptionPane.INFORMATION_MESSAGE);
                        } catch (IOException ex) {
                            JOptionPane.showMessageDialog(frame,
                                    "Save failed:\n" + ex.getMessage(),
                                    "Error", JOptionPane.ERROR_MESSAGE);
                        }
                        yield false;
                    }
                    case KeyEvent.VK_L -> {
                        try {
                            world = World.loadFromFile(SAVE_PATH);
                            logArea.setText("");
                            panel.setWorld(world);
                            for (String line : world.getHistorySnapshot()) {
                                logArea.append(line + "\n");
                            }
                            world.setReportListener(msg -> logArea.append(msg+"\n"));
                            player = world.assignHuman();
                            roundField.setText("Round: " + world.getRound());
                            panel.repaint();
                            JOptionPane.showMessageDialog(frame,
                                    "Game loaded from:\n" + SAVE_PATH.toAbsolutePath(),
                                    "Successful load", JOptionPane.INFORMATION_MESSAGE);
                        } catch (IOException | ClassNotFoundException ex) {
                            JOptionPane.showMessageDialog(frame,
                                    "Load failed:\n" + ex.getMessage(),
                                    "Error", JOptionPane.ERROR_MESSAGE);
                        }
                        yield false;
                    }
                    default -> false;
                };

                if (accepted) {
                    world.makeTurn();
                    roundField.setText("Round: " + world.getRound());
                    panel.repaint();
                    if (player.isDead()) {
                        world.report("You lost the game.");
                        panel.removeKeyListener(this);
                    }
                }
            }
        });
    }
}