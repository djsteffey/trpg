package halfbyte.game.tprg;

public interface IGameServices {
    IPlatformServices getPlatformServices();
    void setNextScreen(AbstractScreen screen);
}
