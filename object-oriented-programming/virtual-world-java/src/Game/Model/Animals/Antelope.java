package Game.Model.Animals;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class Antelope extends Animal {

    Random random = new Random();
    public Antelope(int x, int y, World world){
        super(Species.ANTELOPE, x, y, 4, 4, world, 0, true);
    }

    public Antelope(World world){
        super(Species.ANTELOPE, 0, 0, 4, 4, world, 0, true);
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
            int[] dx = {0, 2, 0, -2};
            int[] dy = {2, 0, -2, 0};
            int direction = random.nextInt(4);
            int newX = x + dx[direction];
            int newY = y + dy[direction];
            if (!world.inBounds(newY, newX)) continue;
            moveOrganism(newY, newX);
            world.report("Antelope moved!");
            return;
        }
    }

    public void collision(Organism other){
        if(getSpecies() == other.getSpecies()){
            int[] dx = {0, 1, 0, -1};
            int[] dy = {1, 0, -1, 0};
            int newX, newY;
            for(int i = 0; i < 4; i++){
                newX = x + dx[i];
                newY = y + dy[i];
                if(world.isFree(newY, newX) && this.checkCanBreed() && other.checkCanBreed()){
                    breed(newY, newX);
                    this.setBreedCooldown();
                    other.setBreedCooldown();
                    world.report( "Antelope offspring appeared!");
                    break;
                }
            }
        }
        else {
            if(random.nextInt(2) == 0){
                if(getStrength() > other.getStrength()){
                    world.report( "Antelope killed " + other.getSpecies().displayName() + "!");
                    other.markDead();
                    world.setOrganism(null, y, x);
                    x = other.getX();
                    y = other.getY();
                    world.setOrganism(this, y, x);
                }

                else {
                    world.report(other.getSpecies().displayName() + " killed Antelope!");
                    markDead();
                    world.setOrganism(null, y, x);
                    other.moveOrganism(y, x);
                }
            }
            else {
                int[] dx = {0, 1, 0, -1};
                int[] dy = {1, 0, -1, 0};
                int newX, newY;
                for(int i = 0; i < 4; i++){
                    newX = getX() + dx[i];
                    newY = getY() + dy[i];
                    if(world.isFree(newY, newX)){
                        world.setOrganism(other, y, x);
                        x = newX;
                        y = newY;
                        world.setOrganism(this, y, x);
                        world.report("Antelope escaped the fight!");
                        return;
                    } else {
                        world.report("There was nowhere to escape - antelope was killed by " + other.getSpecies().displayName());
                        markDead();
                        world.setOrganism(null, y, x);
                        other.moveOrganism(y, x);
                    }
                }
            }
        }
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Antelope breed(int y, int x){
        Antelope offspring = new Antelope(x, y, world);
        offspring.setBreedCooldown();
        return offspring;
    }
}
