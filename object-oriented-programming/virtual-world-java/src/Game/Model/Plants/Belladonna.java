package Game.Model.Plants;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Belladonna extends Plant {
    Random random = new Random();

    public Belladonna(int x, int y, World world){
        super(Species.BELLADONNA, x, y, 99, world, 1);
    }

    public Belladonna(World world){
        super(Species.BELLADONNA, 0, 0, 99, world, 1);
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

    public void collision(Organism other){
        world.report("Belladonna killed " + other.getSpecies().displayName() + "!");
        markDead();
        other.markDead();
        world.setOrganism(null, y, x);
        world.setOrganism(null, other.getY(), other.getX());
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Belladonna sow(int y, int x){
        return new Belladonna(x, y, world);
    }
}
