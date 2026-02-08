package Game.Model;

import java.awt.*;
import java.io.Serializable;

public abstract class Organism implements Serializable {

    protected Species species;
    protected int y;
    protected int x;
    protected int strength;
    protected int initiative;
    protected int age = 0;
    protected boolean dead = false;
    protected World world;
    protected int breedCooldown;
    protected boolean canBreed;

    public Organism(Species species, int x, int y, int strength, int initiative, World world, int breedCooldown, boolean canBreed){
        this.species = species;
        this.y = y;
        this.x = x;
        this.strength = strength;
        this.initiative = initiative;
        this.world = world;
        this.breedCooldown = breedCooldown;
        this.canBreed = canBreed;

        world.setOrganism(this, y, x);
        world.addOrganism(this);
    }

    public abstract void action();
    public abstract void collision(Organism other);
    public abstract Color draw();

    public void moveOrganism(int newY, int newX){
        Organism occupant = world.getOrganism(newY, newX);
        if (occupant != null) {
            occupant.collision(this);
        } else {
            world.setOrganism(null, y, x);
            y = newY;
            x = newX;
            world.setOrganism(this, y, x);
        }
    }

    public final int getY() { return y; }
    public final int getX() { return x; }
    public final int getStrength() { return strength; }
    public final int getInitiative() { return initiative; }
    public final int getAge() { return age; }
    public final Species getSpecies() { return species; }
    public void incrementAge() { age++; }
    public void incrementStrength(int number) { strength+=number; }
    public boolean isDead() { return dead; }
    public void markDead() { dead = true; }
    public boolean checkCanBreed() { return canBreed; }
    public void setBreedCooldown() {
        breedCooldown = 3;
        canBreed = false;
    }
}