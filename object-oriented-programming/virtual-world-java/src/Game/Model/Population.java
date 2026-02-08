package Game.Model;

import Game.Model.Animals.*;
import Game.Model.Plants.*;

public class Population {
    public static void populate(World world){
        new Wolf(world);
        new SowThistle(world);
        new Fox(world);
        new Guarana(world);
        new Turtle(world);
        new Belladonna(world);
        new Antelope(world);
        new SosnowskysHogweed(world);
        for(int i = 0; i < 2; i++){
            new Sheep(world);
            new Grass(world);
        }
    }
}
