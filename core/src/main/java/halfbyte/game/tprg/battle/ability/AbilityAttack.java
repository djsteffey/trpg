package halfbyte.game.tprg.battle.ability;

import com.badlogic.gdx.math.GridPoint2;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;

import java.util.List;

import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.Utils;
import halfbyte.game.tprg.battle.Battle;
import halfbyte.game.tprg.battle.Entity;

public class AbilityAttack extends Ability{
    // variables


    // methods
    public AbilityAttack(Entity owner) {
        super("Attack", 0, owner);
    }

    @Override
    public void computeTargets(List<AbilityTarget> list, Battle battle, int sourceX, int sourceY) {
        // iterate the 4 cardinal directions
        for (GridPoint2 dir : Utils.CARDINAL_DIRECTIONS){
            // get target point
            int targetX = sourceX + dir.x;
            int targetY = sourceY + dir.y;

            // get the entity there
            Entity entity = battle.getEntityAtTilePosition(targetX, targetY);

            // check if we have an entity
            if (entity != null){
                // valid target
                list.add(new AbilityTarget(this, targetX, targetY, 100));
            }
        }
    }

    @Override
    public Action generateAction(Battle battle, AbilityTarget abilityTarget) {
        // get the entity at the target
        Entity entity = battle.getEntityAtTilePosition(abilityTarget.destTileX, abilityTarget.destTileY);

        // validate entity
        if (entity == null){
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
                        return true;
                    }
                },

                // bump away
                Actions.moveTo(this.m_owner.getTileX() * Config.TILE_SIZE, this.m_owner.getTileY() * Config.TILE_SIZE, 0.25f)
        );
    }
}
