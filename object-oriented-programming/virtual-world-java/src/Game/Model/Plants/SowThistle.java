package Game.Model.Plants;

import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class SowThistle extends Plant {
    Random random = new Random();

    public SowThistle(int x, int y, World world){
        super(Species.SOW_THISTLE, x, y, 0, world, 3);
    }

    public SowThistle(World world){
        super(Species.SOW_THISTLE, 0, 0, 0, world, 3);
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

    public SowThistle sow(int y, int x){
        return new SowThistle(x, y, world);
    }
}
