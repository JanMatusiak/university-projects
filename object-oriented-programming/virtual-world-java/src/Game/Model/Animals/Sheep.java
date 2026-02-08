package Game.Model.Animals;

import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Sheep extends Animal {

    Random random = new Random();
    public Sheep(int x, int y, World world){
        super(Species.SHEEP, x, y, 4, 4, world, 0, true);
    }

    public Sheep(World world){
        super(Species.SHEEP, 0, 0, 4, 4, world, 0, true);
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

    public Sheep breed(int y, int x){
        Sheep offspring = new Sheep(x, y, world);
        offspring.setBreedCooldown();
        return offspring;
    }
}
