package halfbyte.game.tprg.battle.ability;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;

import java.util.List;

import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.Utils;
import halfbyte.game.tprg.battle.Battle;
import halfbyte.game.tprg.battle.Entity;

public class AbilityHeal extends Ability{
    public AbilityHeal(Entity owner) {
        super("Heal", 1, 4, owner);
    }

    @Override
    public void computeTargets(List<AbilityTarget> list, Battle battle, int sourceX, int sourceY) {
        // loop all entities
        for (Entity entity : battle.getEntities()){
            // check alive and same team
            if (entity.getIsAlive() && entity.getTeamId() == this.m_owner.getTeamId()){
                // check distance and hp percent
                if (Utils.manhattanDistance(entity, this.m_owner) <= this.m_range && entity.getHpPercent() <= 0.80f) {
                     // we can heal this one
                    list.add(new AbilityTarget(this, entity.getTileX(), entity.getTileY(), 100));
                }
            }
        }
    }

    @Override
    public Action generateAction(Battle battle, AbilityTarget abilityTarget) {
        // get the entity at the target
        Entity entity = battle.getEntityAtTilePosition(abilityTarget.destTileX, abilityTarget.destTileY);

        // validate entity
        if (entity == null || entity.getIsAlive() == false){
            return null;
        }

        // action time
        return Actions.sequence(
                // bump up
                Actions.moveBy(0, Config.TILE_SIZE / 2, 0.25f),

                // heal
                new Action() {
                    @Override
                    public boolean act(float delta) {
                        int amount = Utils.randomInt(3, 5);
                        entity.heal(amount);
                        return true;
                    }
                },

                // bump back
                Actions.moveTo(this.m_owner.getTileX() * Config.TILE_SIZE, this.m_owner.getTileY() * Config.TILE_SIZE, 0.25f)
        );
    }
}
