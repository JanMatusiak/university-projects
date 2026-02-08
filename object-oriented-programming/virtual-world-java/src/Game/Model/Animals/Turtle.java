package Game.Model.Animals;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Turtle extends Animal {

    Random random = new Random();
    public Turtle(int x, int y, World world){
        super(Species.TURTLE, x, y, 2, 1, world, 0, true);
    }

    public Turtle(World world){
        super(Species.TURTLE, 0, 0, 2, 1, world, 0, true);
        int width = world.getWidth();
        int height = world.getHeight();

        int newX, newY;

        do {
            newX = random.nextInt(width);
            newY = random.nextInt(height);
        } while(!world.isFree(newY, newX));

        world.setOrganism(null, y, x);
        x = newX;
        y = newY;
        world.setOrganism(this, y, x);
    }

    public void action() {
        if(random.nextInt(4) == 0){
            super.action();
        } else {
            if(!canBreed){
                --breedCooldown;
                if(breedCooldown == 0){
                    canBreed = true;
                }
            }
            world.report("Turtle stayed put!");
        }
    }

    public void collision(Organism other) {
        if(other.getStrength() < 5 && other.getSpecies() != Species.TURTLE){
            world.report("Turtle defended itself against " + other.getSpecies().displayName());
            return;
        }
        super.collision(other);
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Turtle breed(int y, int x){
        Turtle offspring = new Turtle(x, y, world);
        offspring.setBreedCooldown();
        return offspring;
    }
}
