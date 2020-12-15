#ifndef trpg_Tilemap_hpp
#define trpg_Tilemap_hpp

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tileset.hpp"
#include "AssetManager.hpp"

namespace trpg {
	class TilemapTile {
	public:
		TilemapTile(int graphics_id);
		~TilemapTile();
		int get_graphics_id() const;

	protected:

	private:
		int m_graphics_id;
	};

	class Tilemap {
	public:
		Tilemap(AssetManager* am, int width, int height, int tilesize);
		~Tilemap();
		void update(int ms) const;
		void draw(sf::RenderWindow* rw);
		bool is_valid_tile_position(int tile_x, int tile_y) const;

	protected:

	private:
		void update_vertex_array();

		int m_width;
		int m_height;
		int m_tilesize;
		sf::VertexArray m_vertex_array;
		std::unique_ptr<Tileset> m_tileset;
		bool m_dirty;
		std::vector<std::vector<TilemapTile>> m_tiles;
	};
}
#endif