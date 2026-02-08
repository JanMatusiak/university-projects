package Game.Model.Plants;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.util.Random;

public abstract class Plant extends Organism {
    Random random = new Random();
    protected final int sowAttempts;

    public Plant(Species species, int x, int y, int strength, World world, int attempts){
        super(species, x, y, strength, 0, world, 0, true);
        this.sowAttempts = attempts;
    }

    public void action(){
        int[] dy = {1, 0, -1, 0};
        int[] dx = {0, 1, 0, -1};
        for(int i = 0; i < sowAttempts; i++){
            int direction = random.nextInt(4);
            int newY = y + dy[direction];
            int newX = x + dx[direction];
            if(world.inBounds(newY, newX) && world.getOrganism(newY, newX) == null && random.nextInt(2) % 2 == 0){
                sow(newY, newX);
                return;
            }
        }
    }

    public void collision(Organism other){
        world.report(other.getSpecies().displayName() + " ate " + species.displayName());
        markDead();
        world.setOrganism(null, y, x);
        other.moveOrganism(y, x);
    }

    public abstract Plant sow(int y, int x);
}
