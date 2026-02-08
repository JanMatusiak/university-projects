package Game.Model.Plants;

import Game.Model.Organism;
import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.util.Random;

public class SosnowskysHogweed extends Plant {
    Random random = new Random();

    public SosnowskysHogweed(int x, int y, World world){
        super(Species.SOSNOWSKYS_HOGWEED, x, y, 10, world, 1);
    }

    public SosnowskysHogweed(World world){
        super(Species.SOSNOWSKYS_HOGWEED, 0, 0, 10, world, 1);
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

    public void action(){
        int[] dx = {0, 1, 1, 1, 0, -1, -1, -1};
        int[] dy = {1, 1, 0, -1, -1, -1, 0, 1};
        int newX, newY;
        for(int i = 0; i < 8; i++){
            newX = getX() + dx[i];
            newY = getY() + dy[i];
            if(!world.inBounds(newY, newX)) continue;
            Organism neighbour = world.getOrganism(newY, newX);
            if(neighbour != null && (neighbour.getSpecies() != Species.SOSNOWSKYS_HOGWEED &&
                    neighbour.getSpecies() != Species.BELLADONNA &&
                            neighbour.getSpecies() != Species.GUARANA &&
                                    neighbour.getSpecies() != Species.SOW_THISTLE &&
                                            neighbour.getSpecies() != Species.GRASS)){
                world.report("Sosnowsky's Hogweed killed " + neighbour.getSpecies().displayName() + "!");
                neighbour.markDead();
                world.setOrganism(null, newY, newX);
            }
        }

        for(int i = 0; i < sowAttempts; i++){
            int direction = random.nextInt(4);
            newX = x + dx[direction];
            newY = y + dy[direction];
            if(world.inBounds(newY, newX) && world.getOrganism(newY, newX) == null && random.nextInt(2) == 0){
                sow(newY, newX);
                return;
            }
        }
    }

    public final Color draw(){
        return species.displayColor();
    }

    public SosnowskysHogweed sow(int y, int x){
        return new SosnowskysHogweed(x, y, world);
    }
}
