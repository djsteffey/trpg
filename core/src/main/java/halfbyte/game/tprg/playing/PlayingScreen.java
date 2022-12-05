package halfbyte.game.tprg.playing;

import halfbyte.game.tprg.AbstractScreen;
import halfbyte.game.tprg.IGameServices;
import halfbyte.game.tprg.battle.Battle;

public class PlayingScreen extends AbstractScreen {
    // variables

    // methods
    public PlayingScreen(IGameServices gs) {
        // super
        super(gs);

        // create a battle
        Battle battle = new Battle();
        this.m_stage.addActor(battle);
    }

    @Override
    public void render(float delta) {
        delta *= 4;

        // super render
        super.render(delta);
    }
}
