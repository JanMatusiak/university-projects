package Game.Model.Plants;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Guarana extends Plant {
    Random random = new Random();

    public Guarana(int x, int y, World world){
        super(Species.GUARANA, x, y, 0, world, 1);
    }

    public Guarana(World world){
        super(Species.GUARANA, 0, 0, 0, world, 1);
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
        world.report(other.getSpecies().displayName() + " ate Guarana and got its strength incremented by 3!");
        markDead();
        world.setOrganism(null, y, x);
        other.moveOrganism(y, x);
        other.incrementStrength(3);
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Guarana sow(int y, int x){
        return new Guarana(x, y, world);
    }
}
