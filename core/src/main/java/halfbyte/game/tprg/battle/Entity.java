package halfbyte.game.tprg.battle;

import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.Group;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import java.util.ArrayList;
import java.util.List;
import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.GameAssetManager;
import halfbyte.game.tprg.battle.ability.Ability;
import halfbyte.game.tprg.battle.ability.AbilityAttack;
import halfbyte.game.tprg.battle.ai.AI;

public class Entity extends Group {
    // variables
    private int m_tileX;
    private int m_tileY;
    private List<Ability> m_abilities;
    private AI m_ai;

    // methods
    public Entity(int tileX, int tileY){
        // parameters
        this.m_tileX = tileX;
        this.m_tileY = tileY;

        // size and position
        this.setSize(Config.TILE_SIZE, Config.TILE_SIZE);
        this.setPosition(
                this.m_tileX * this.getWidth(),
                this.m_tileY * this.getHeight()
        );

        // graphic
        Image image = new Image(GameAssetManager.getInstance().getTileset("actors_24x24.png", 24).getRegion(26));
        image.setSize(this.getWidth(), this.getHeight());
        this.addActor(image);

        // abilities
        this.m_abilities = new ArrayList<>();
        this.m_abilities.add(new AbilityAttack(this));

        // ai
        this.m_ai = new AI(this);
    }

    public List<Ability> getAbilities(){
        return this.m_abilities;
    }

    public int getTileX(){
        return this.m_tileX;
    }

    public int getTileY(){
        return this.m_tileY;
    }

    public void setTilePosition(int tileX, int tileY, boolean snapPosition){
        this.m_tileX = tileX;
        this.m_tileY = tileY;
        if (snapPosition){
            this.setPosition(this.m_tileX * Config.TILE_SIZE, this.m_tileY * Config.TILE_SIZE);
        }
    }

    public Action getTurnAction(Battle battle){
        return this.m_ai.createTurnAction(battle);
    }
}
