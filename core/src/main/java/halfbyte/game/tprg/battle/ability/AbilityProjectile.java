package halfbyte.game.tprg.battle.ability;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;

import java.util.List;

import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.Utils;
import halfbyte.game.tprg.battle.Battle;
import halfbyte.game.tprg.battle.Entity;

public class AbilityProjectile extends Ability{
    // variables


    // methods
    public AbilityProjectile(String name, int cost, int range, Entity owner) {
        super(name, cost, range, owner);
    }

    @Override
    public void computeTargets(List<AbilityTarget> list, Battle battle, int sourceX, int sourceY) {
        // loop all entities
        for (Entity entity : battle.getEntities()){
            // check alive and other team
            if (entity.getIsAlive() && entity.getTeamId() != this.m_owner.getTeamId()){
                // check distance
                if (Utils.manhattanDistance(entity, this.m_owner) <= this.m_range) {
                    // fire ze missiles!!
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

        // calc position offset from the owner to the entity
        Vector2 dif = Utils.direction(
                this.m_owner.getX(), this.m_owner.getY(),
                entity.getX(), entity.getY(),
                false
        );

        // action time
        return Actions.sequence(
                // bump towards
                Actions.moveBy(dif.x / 2, dif.y / 2, 0.25f),

                // damage
                new Action() {
                    @Override
                    public boolean act(float delta) {
                        int amount = Utils.randomInt(5, 10);
                        entity.damage(amount);
                        return true;
                    }
                },

                // bump away
                Actions.moveTo(this.m_owner.getTileX() * Config.TILE_SIZE, this.m_owner.getTileY() * Config.TILE_SIZE, 0.25f)
        );
        return null;
    }
}
