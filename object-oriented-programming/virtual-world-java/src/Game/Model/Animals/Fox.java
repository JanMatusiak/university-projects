package Game.Model.Animals;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Fox extends Animal {

    Random random = new Random();
    public Fox(int x, int y, World world){
        super(Species.FOX, x, y, 3, 7, world, 0, true);
    }

    public Fox(World world){
        super(Species.FOX, 0, 0, 3, 7, world, 0, true);
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
        if(!canBreed){
            --breedCooldown;
            if(breedCooldown == 0){
                canBreed = true;
            }
        }
        for(int i = 0; i < 4; i++){
            int[] dx = {0, 1, 0, -1};
            int[] dy = {1, 0, -1, 0};
            int direction = random.nextInt(4);
            int newX = x + dx[direction];
            int newY = y + dy[direction];
            Organism destination = world.getOrganism(newY, newX);
            if(destination != null && destination.getStrength() > getStrength()){
                continue;
            }
            moveOrganism(newY, newX);
            world.report("Fox moved!");
            return;
        }
        world.report("Fox sensed danger and stayed put!");
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Fox breed(int y, int x){
        Fox offspring = new Fox(x, y, world);
        offspring.setBreedCooldown();
        return offspring;
    }
}
