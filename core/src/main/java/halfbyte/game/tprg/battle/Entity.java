package halfbyte.game.tprg.battle;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Action;
import com.badlogic.gdx.scenes.scene2d.Group;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import java.util.ArrayList;
import java.util.List;
import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.GameAssetManager;
import halfbyte.game.tprg.UiProgressBar;
import halfbyte.game.tprg.Utils;
import halfbyte.game.tprg.battle.ability.Ability;
import halfbyte.game.tprg.battle.ability.AbilityAttack;
import halfbyte.game.tprg.battle.ability.AbilityHeal;
import halfbyte.game.tprg.battle.ai.AI;

public class Entity extends Group {
    // variables
    private int m_tileX;
    private int m_tileY;
    private List<Ability> m_abilities;
    private AI m_ai;
    private int m_hpMax;
    private int m_hpCurrent;
    private int m_teamId;
    private UiProgressBar m_hpBar;

    // methods
    public Entity(int tileX, int tileY, int teamId){
        // parameters
        this.m_tileX = tileX;
        this.m_tileY = tileY;
        this.m_teamId = teamId;

        // size and position
        this.setSize(Config.TILE_SIZE, Config.TILE_SIZE);
        this.setPosition(
                this.m_tileX * this.getWidth(),
                this.m_tileY * this.getHeight()
        );

        // abilities
        this.m_abilities = new ArrayList<>();
        this.m_abilities.add(new AbilityAttack(this));
        this.m_abilities.add(new AbilityHeal(this));

        // stats
        this.m_hpMax = Utils.randomInt(50, 100);
        this.m_hpCurrent = this.m_hpMax;

        // graphic
        Image image = new Image(GameAssetManager.getInstance().getTileset("actors_24x24.png", 24).getRegion(22 + this.m_teamId));
        image.setSize(this.getWidth() * 0.75f, this.getHeight() * 0.75f);
        image.setPosition(
                (this.getWidth() - image.getWidth()) / 2,
                0
        );
        this.addActor(image);

        // hp bar
        this.m_hpBar = new UiProgressBar(this.m_hpCurrent, this.m_hpMax);
        this.m_hpBar.setSize(this.getWidth() * 0.85f, 12);
        this.m_hpBar.setPosition(
                (this.getWidth() - this.m_hpBar.getWidth()) / 2,
                this.getHeight() - this.m_hpBar.getHeight() - 2
        );
        this.addActor(this.m_hpBar);

        // ai
        this.m_ai = new AI(this);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        this.m_hpBar.setValue(this.m_hpCurrent, this.m_hpMax);
        super.draw(batch, parentAlpha);
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

    public int getTeamId(){
        return this.m_teamId;
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

    public void damage(int amount){
        this.m_hpCurrent = Math.max(this.m_hpCurrent - amount, 0);
    }

    public void heal(int amount){
        this.m_hpCurrent = Math.min(this.m_hpCurrent + amount, this.m_hpMax);
    }

    public boolean getIsAlive(){
        return this.m_hpCurrent > 0;
    }

    public float getHpPercent(){
        return (float)this.m_hpCurrent / this.m_hpMax;
    }
}
