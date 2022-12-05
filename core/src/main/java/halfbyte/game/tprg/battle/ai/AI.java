package halfbyte.game.tprg.battle.ai;

import com.badlogic.gdx.math.GridPoint2;
import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import java.util.ArrayList;
import java.util.List;
import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.Utils;
import halfbyte.game.tprg.battle.Battle;
import halfbyte.game.tprg.battle.Entity;
import halfbyte.game.tprg.battle.ability.Ability;

public class AI {
    // variables
    private Entity m_owner;

    // methods
    public AI(Entity owner){
        this.m_owner = owner;
    }

    public Action createTurnAction(Battle battle){
        // list of all ability/target combinations
        List<Ability.AbilityTarget> list = new ArrayList<>();

        // iterate over all abilities
        for (Ability ability : this.m_owner.getAbilities()){
            // for each ability, have it compute the list of where that ability can be used along with the score
            ability.computeTargets(list, battle, this.m_owner.getTileX(), this.m_owner.getTileY());
        }

        // check if we got an ability we can execute
        if (list.size() > 0){
            // pick ability with highest score
            Ability.AbilityTarget best = null;
            for (Ability.AbilityTarget abilityTarget : list){
                if (best == null || abilityTarget.score > best.score){
                    best = abilityTarget;
                }
            }

            // return the ability action
            return best.ability.generateAction(battle, best);
        }

        // no actions; try to move
        // get available destinations in the 4 cardinal directions
        List<GridPoint2> destinations = new ArrayList<>();
        for (GridPoint2 dir : Utils.CARDINAL_DIRECTIONS){
            if (battle.getIsTileWalkable(this.m_owner, this.m_owner.getTileX() + dir.x, this.m_owner.getTileY() + dir.y)){
                destinations.add(new GridPoint2(this.m_owner.getTileX() + dir.x, this.m_owner.getTileY() + dir.y));
            }
        }

        // check if we have one
        if (destinations.isEmpty() == false){
            // pick one at random
            GridPoint2 destination = destinations.get(Utils.randomInt(0, destinations.size()));

            // move to it
            return this.createWalkToTileAction(destination.x, destination.y);
        }

        // getting here means there is no ability and no move we can do
        return null;
    }

    private Action createWalkToTileAction(int destinationTileX, int destinationTileY){
        return Actions.sequence(
                Actions.moveTo(destinationTileX * Config.TILE_SIZE, destinationTileY * Config.TILE_SIZE, 0.25f),
                new Action() {
                    @Override
                    public boolean act(float delta) {
                        Entity entity = (Entity) this.getActor();
                        entity.setTilePosition(destinationTileX, destinationTileY, false);
                        return true;
                    }
                }
        );
    }
}
