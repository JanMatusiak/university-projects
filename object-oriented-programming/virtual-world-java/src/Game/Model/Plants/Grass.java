package Game.Model.Plants;

import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Grass extends Plant {
    Random random = new Random();

    public Grass(int x, int y, World world){
        super(Species.GRASS, x, y, 0, world, 1);
    }

    public Grass(World world){
        super(Species.GRASS, 0, 0, 0, world, 1);
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

    public final Color draw(){
        return species.displayColor();
    }

    public Grass sow(int y, int x){
        return new Grass(x, y, world);
    }
}
