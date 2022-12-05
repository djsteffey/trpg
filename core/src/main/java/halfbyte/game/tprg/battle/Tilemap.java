package halfbyte.game.tprg.battle;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.Group;
import halfbyte.game.tprg.Config;
import halfbyte.game.tprg.GameAssetManager;
import halfbyte.game.tprg.Tileset;

public class Tilemap extends Group {
    // variables
    private int m_width;
    private int m_height;
    private int[][] m_tiles;
    private Tileset m_tileset;

    // methods
    public Tilemap(int width, int height){
        // parameters
        this.m_width = width;
        this.m_height = height;

        // create all the tiles
        this.m_tiles = new int[this.m_width][this.m_height];
        for (int y = 0; y < this.m_height; ++y){
            for (int x = 0; x < this.m_width; ++x){
                this.m_tiles[x][y] = 0;
            }
        }

        // load the tileset
        this.m_tileset = GameAssetManager.getInstance().getTileset("tiles_24x24.png", 24);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        // super me
        super.draw(batch, parentAlpha);

        // setup the color
        batch.setColor(this.getColor());

        // iterate all the tiles
        for (int y = 0; y < this.m_height; ++y){
            for (int x = 0; x < this.m_width; ++x){
                TextureRegion tr = this.m_tileset.getRegion(this.m_tiles[x][y]);
                batch.draw(
                        tr,
                        this.getX() + x * Config.TILE_SIZE,
                        this.getY() + y * Config.TILE_SIZE,
                        Config.TILE_SIZE,
                        Config.TILE_SIZE
                );
            }
        }
    }

    public int getTilesWide(){
        return this.m_width;
    }

    public int getTilesHigh(){
        return this.m_height;
    }

    public boolean getIsTileWalkable(int tileX, int tileY){
        if (this.getIsValidTile(tileX, tileY) == false){
            return false;
        }
        return true;
    }

    private boolean getIsValidTile(int x, int y){
        if (x < 0 || x > this.m_width - 1 || y < 0 || y > this.m_height - 1){
            return false;
        }
        return true;
    }


}
