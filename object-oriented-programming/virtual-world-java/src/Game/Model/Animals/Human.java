package Game.Model.Animals;

import Game.Model.Species;
import Game.Model.World;

import java.awt.*;
import java.awt.event.KeyEvent;

import static java.lang.Math.max;

public class Human extends Animal {
    private boolean abilityActive;
    private int abilityCooldown;
    private int baseStrength;

    public Human(int x, int y, World world){
        super(Species.HUMAN, x, y, 5, 4, world, 0, true);
        this.abilityActive = false;
        this.abilityCooldown = 0;
        this.baseStrength = 5;
    }

    public void action() {
        int key = world.getLastKey();
        if(key == 0) return;
        world.setLastKey(0);
        switch (key) {
            case KeyEvent.VK_LEFT: moveOrganism(y, x-1); break;
            case KeyEvent.VK_RIGHT: moveOrganism(y, x+1); break;
            case KeyEvent.VK_UP: moveOrganism(y-1, x); break;
            case KeyEvent.VK_DOWN: moveOrganism(y+1, x); break;
            case KeyEvent.VK_A: specialAbility(); return;
            default: return;
        }
        if (abilityActive) {
            strength = max(strength-1, baseStrength);
            if (strength == baseStrength) {
                abilityActive = false;
                abilityCooldown = 5;
                world.report("Ability effect ended.");
            }
        } else if (abilityCooldown > 0) {
            abilityCooldown--;
        }
    }

    public Boolean canUseAbility(){
        return (getAbilityCooldown() || abilityActive) ;
    }

    public Boolean getAbilityCooldown(){
        return (abilityCooldown > 0);
    }

    public Boolean getAbilityActive(){
        return abilityActive;
    }

    public void specialAbility() {
        baseStrength = strength;
        strength+=5;
        abilityActive = true;
        world.report("Ability is now active! Strength increased by 5.");
    }

    public final Color draw(){
        return species.displayColor();
    }

    public Human breed(int y, int x){
        return null;
    }
}

