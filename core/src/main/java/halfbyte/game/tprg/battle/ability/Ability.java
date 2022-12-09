package halfbyte.game.tprg.battle.ability;

import com.badlogic.gdx.scenes.scene2d.Action;
import java.util.List;
import halfbyte.game.tprg.battle.Battle;
import halfbyte.game.tprg.battle.Entity;

public abstract class Ability {
    public static class AbilityTarget{
        public Ability ability;
        public int destTileX;
        public int destTileY;
        public int score;

        public AbilityTarget(Ability ability, int destTileX, int destTileY, int score){
            this.ability = ability;
            this.destTileX = destTileX;
            this.destTileY = destTileY;
            this.score = score;
        }
    }

    // variables
    private String m_name;
    private int m_cost;
    protected int m_range;
    protected Entity m_owner;

    // methods
    public Ability(String name, int cost, int range, Entity owner){
        this.m_name = name;
        this.m_cost = cost;
        this.m_range = range;
        this.m_owner = owner;
    }

    public abstract void computeTargets(List<AbilityTarget> list, Battle battle, int sourceX, int sourceY);

    public abstract Action generateAction(Battle battle, AbilityTarget abilityTarget);
}
