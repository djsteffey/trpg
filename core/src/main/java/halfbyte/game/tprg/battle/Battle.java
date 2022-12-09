package halfbyte.game.tprg.battle;

import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.Group;
import com.badlogic.gdx.scenes.scene2d.actions.Actions;
import java.util.ArrayList;
import java.util.List;
import halfbyte.game.tprg.Utils;

public class Battle extends Group {
    // variables
    private Tilemap m_tilemap;
    private List<Entity> m_entities;
    private int m_turnIndex;

    // methods
    public Battle(){
        // tilemap
        this.m_tilemap = new Tilemap(15, 15);
        this.addActor(this.m_tilemap);

        // entities
        this.m_entities = new ArrayList<>();
        for (int i = 0; i < 10; ++i){
            Entity entity = new Entity(
                    Utils.randomInt(1, this.m_tilemap.getTilesWide() - 1),
                    Utils.randomInt(1, this.m_tilemap.getTilesHigh() - 1),
                    i % 2
            );
            this.m_entities.add(entity);
            this.addActor(entity);
        }

        // turn
        this.m_turnIndex = 0;
        this.doNextTurn();
    }

    @Override
    public void act(float delta) {
        super.act(delta);
    }

    public Tilemap getTilemap(){
        return this.m_tilemap;
    }

    public List<Entity> getEntities(){
        return this.m_entities;
    }

    public boolean getIsTileWalkable(Entity entity, int tileX, int tileY){
        // first ask the tilemap
        if (this.m_tilemap.getIsTileWalkable(tileX, tileY) == false){
            return false;
        }

        // check if there is another entity there
        for (Entity other : this.m_entities){
            if (other != entity){
                if (other.getTileX() == tileX && other.getTileY() == tileY){
                    // there is another entity already there
                    return false;
                }
            }
        }

        // passed
        return true;
    }

    public Entity getEntityAtTilePosition(int tileX, int tileY){
        for (Entity entity : this.m_entities){
            if (entity.getTileX() == tileX && entity.getTileY() == tileY){
                return entity;
            }
        }
        return null;
    }

    private void doEndOfTurn(){
        // remove dead entities from stage
        for (Entity entity : this.m_entities){
            if (entity.getIsAlive() == false){
                entity.remove();
            }
        }

        // remove dead entities from list
        this.m_entities.removeIf(entity-> entity.getIsAlive() == false);

        // todo check end of battle

        // next turn
        this.doNextTurn();
    }

    private void doNextTurn(){
        // increment turn index
        this.m_turnIndex = (this.m_turnIndex + 1) % this.m_entities.size();

        // get the entity
        Entity entity = this.m_entities.get(this.m_turnIndex);

        // get its turn action
        Action action = entity.getTurnAction(this);

        // make sure we have an action
        if (action != null){
            // setup a sequence and put on the entity
            entity.addAction(Actions.sequence(
                    action,
                    new Action() {
                        @Override
                        public boolean act(float delta) {
                            Battle.this.doEndOfTurn();
                            return true;
                        }
                    }
            ));
        }
        else{
            // no action it can do; setup next turn
            entity.addAction(Actions.sequence(
                    new Action() {
                        @Override
                        public boolean act(float delta) {
                            Battle.this.doNextTurn();
                            return true;
                        }
                    }
            ));
        }
    }
}
