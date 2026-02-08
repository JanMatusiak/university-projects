package Game.Model;

import Game.Model.Animals.Human;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.function.Consumer;

public class World implements Serializable {

    private static final int MAX_ORGANISMS = 6400;
    private static final int LOG_SIZE = 50;
    private final Organism[][] grid;
    private final int width;
    private final int height;
    private int round = 0;
    private int lastKey = 0;
    private final List<Organism> organisms = new ArrayList<>();
    private final Deque<String> history = new ArrayDeque<>(LOG_SIZE);
    private transient Consumer<String> listener;

    public World(int width, int height){
        this.width = width;
        this.height = height;
        this.grid = new Organism[height][width];
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getRound() {
        return round;
    }

    public boolean inBounds(int y, int x){
        return (y >= 0 && y < height && x >= 0 && x < width);
    }

    public boolean isFree(int y, int x){
        return (inBounds(y, x) && grid[y][x] == null);
    }

    public Organism getOrganism(int y, int x){
        if(!inBounds(y, x)) return null;
        return grid[y][x];
    }

    public void setOrganism(Organism organism, int y, int x){
        if(inBounds(y, x)){
            grid[y][x] = organism;
        }
    }

    public void addOrganism(Organism organism) {
        if (organisms.size() < MAX_ORGANISMS) {
            organisms.add(organism);
        }
    }

    public void makeTurn(){
        round++;
        organisms.sort(Comparator.comparingInt(Organism::getInitiative).reversed()
                .thenComparingInt(Organism::getAge).reversed());

        for(Organism organism : new ArrayList<>(organisms)){
            if(!organism.isDead()){
                organism.action();
                organism.incrementAge();
            }
        }
        organisms.removeIf(organism -> organism.isDead() && organism.getSpecies() != Species.HUMAN);
    }

    public void setLastKey(int k) {
        lastKey = k;
    }

    public final int getLastKey() {
        return lastKey;
    }

    public void saveToFile(Path file) throws IOException {
        try (ObjectOutputStream oos = new ObjectOutputStream(Files.newOutputStream(file))) {
            oos.writeObject(this);
        }
    }

    public static World loadFromFile(Path file) throws IOException, ClassNotFoundException {
        try (ObjectInputStream ois = new ObjectInputStream(Files.newInputStream(file))) {
            return (World) ois.readObject();
        }
    }

    public void setReportListener(Consumer<String> listener){
        this.listener = listener;
    }

    public void report(String msg) {
        if (history.size() == LOG_SIZE) history.removeFirst();
        history.addLast(msg);
        if (listener != null) listener.accept(msg);
    }

    public List<String> getHistorySnapshot() {
        return new ArrayList<>(history);
    }

    public Human assignHuman() {
        for (Organism organism : organisms) {
            if (organism instanceof Human) return (Human)organism;
        }
        return null;
    }
}