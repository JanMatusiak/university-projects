package Game.Model.Animals;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.util.Random;

public abstract class Animal extends Organism {
    Random random = new Random();

    public Animal(Species species, int x, int y, int strength, int initiative, World world, int breedCooldown, boolean canBreed){
        super(species, x, y, strength, initiative, world, breedCooldown, canBreed);
    }

    public void action(){
        if(!canBreed){
            --breedCooldown;
            if(breedCooldown == 0){
                canBreed = true;
            }
        }
        for(int i = 0; i < 4; i++){
            int[] dy = {1, 0, -1, 0};
            int[] dx = {0, 1, 0, -1};
            int direction = random.nextInt(4);
            int newX = x + dx[direction];
            int newY = y + dy[direction];
            if(!world.inBounds(newY, newX)) continue;
            moveOrganism(newY, newX);
            world.report(species.displayName() + " moved!");
            return;
        }
    }

    public void collision(Organism other){
        if(getSpecies() == other.getSpecies()){
            int[] dy = {1, 0, -1, 0};
            int[] dx = {0, 1, 0, -1};
            int newY, newX;
            for(int i = 0; i < 4; i++) {
                newY = y + dy[i];
                newX = x + dx[i];
                if (world.isFree(newY, newX) && this.checkCanBreed() && other.checkCanBreed()) {
                    breed(newY, newX);
                    this.setBreedCooldown();
                    other.setBreedCooldown();
                    world.report(species.displayName() + " offspring appeared!");
                    break;
                }
            }
        }

        else if(getStrength() > other.getStrength()){
            world.report(species.displayName() + " killed " + other.getSpecies().displayName() + "!");
            other.markDead();
            world.setOrganism(null, y, x);
            y = other.getY();
            x = other.getX();
            world.setOrganism(this, y, x);
        }

        else {
            world.report(other.getSpecies().displayName() + " killed " + species.displayName() + "!");
            markDead();
            world.setOrganism(null, y, x);
            other.moveOrganism(y, x);
        }
    }

    public abstract Animal breed(int y, int x);
}
