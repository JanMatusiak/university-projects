package Game.Model;

import java.awt.*;
import java.io.Serializable;

public enum Species implements Serializable {
    HUMAN ("Human", new Color(255, 215, 0)),
    WOLF ("Wolf", Color.GRAY),
    SHEEP ("Sheep", Color.WHITE),
    FOX ("Fox", new Color(226, 88, 34)),
    TURTLE ("Turtle", new Color(62, 142, 65)),
    ANTELOPE ("Antelope", new Color(160, 82, 45)),
    GRASS ("Grass", Color.GREEN),
    SOW_THISTLE ("Sow Thistle", new Color(187, 222, 251)),
    GUARANA ("Guarana", new Color(173, 20, 87)),
    BELLADONNA ("Belladonna", new Color(74, 20, 140)),
    SOSNOWSKYS_HOGWEED ("Sosnowsky's Hogweed", new Color(27, 94, 32));

    private final String display;
    private final Color color;

    Species(String display, Color color) {
        this.display = display;
        this.color = color;
    }

    public String displayName(){
        return display;
    }

    public Color displayColor(){
        return color;
    }
}
