package halfbyte.game.tprg.lwjgl3;

import com.badlogic.gdx.backends.lwjgl3.Lwjgl3Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3ApplicationConfiguration;
import halfbyte.game.tprg.IPlatformServices;
import halfbyte.game.tprg.TRPGGame;

public class Lwjgl3Launcher implements IPlatformServices {
	public static void main(String[] args) {
		// config
		Lwjgl3ApplicationConfiguration configuration = new Lwjgl3ApplicationConfiguration();
		configuration.setTitle("TRPG");
		configuration.setWindowedMode(1280, 720);
		configuration.setResizable(false);
		configuration.setWindowPosition(200, 200);
		configuration.useVsync(true);
		configuration.setWindowIcon("libgdx128.png", "libgdx64.png", "libgdx32.png", "libgdx16.png");

		// create game
		TRPGGame game = new TRPGGame(new Lwjgl3Launcher());

		// start
		new Lwjgl3Application(game, configuration);
	}
}