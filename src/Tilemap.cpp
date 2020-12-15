#include "Tilemap.hpp"

namespace trpg {
	TilemapTile::TilemapTile(int graphics_id) {
		this->m_graphics_id = graphics_id;
	}

	TilemapTile::~TilemapTile() {

	}

	int TilemapTile::get_graphics_id() const {
		return this->m_graphics_id;
	}

	Tilemap::Tilemap(int width, int height, int tilesize) {
		// save size
		this->m_width = width;
		this->m_height = height;
		this->m_tilesize = tilesize;

		// create the tileset
		this->m_tileset = std::make_unique<Tileset>("assets/tiles_24x24.png", 24);

		// create the tiles
		this->m_tiles.resize(this->m_width);
		for (int x = 0; x < this->m_width; ++x) {
			for (int y = 0; y < this->m_height; ++y) {
				if (x == 0 || y == 0 || x == this->m_width - 1 || y == this->m_height - 1) {
					this->m_tiles[x].push_back(TilemapTile(0));
				}
				else {
					this->m_tiles[x].push_back(TilemapTile(3));
				}
			}
		}

		// mark as dirty and update the vertex array
		this->m_dirty = true;
		this->update_vertex_array();
	}

	Tilemap::~Tilemap() {

	}

	void Tilemap::update(int ms) {

	}

	void Tilemap::draw(sf::RenderWindow& rw) {
		if (this->m_dirty) {
			this->update_vertex_array();
		}
		rw.draw(this->m_vertex_array, &(this->m_tileset->get_texture()));
	}

	void Tilemap::update_vertex_array() {
		// check to make sure dirty
		if (this->m_dirty == false) {
			// no need
			return;
		}

		// clear dirty
		this->m_dirty = false;

		// set vertex array properties
		this->m_vertex_array.setPrimitiveType(sf::PrimitiveType::Quads);

		// make sure the vertex array is sized appropriately
		size_t size = 4;
		size *= this->m_width * this->m_height;;
		this->m_vertex_array.resize(size);
		
		// fill it up
		for (int y = 0; y < this->m_height; ++y) {
			for (int x = 0; x < this->m_width; ++x) {
				// rect of the texture in the tileset
				sf::IntRect rect = this->m_tileset->get_rect(this->m_tiles[x][y].get_graphics_id());

				// first vert index
				size_t vert_index = (x + y * this->m_width) * 4;

				// top left
				sf::Vertex* v = &(this->m_vertex_array[vert_index + 0]);
				v->position.x = (float)(x * this->m_tilesize);
				v->position.y = (float)(y * this->m_tilesize);
				v->color = sf::Color::White;
				v->texCoords.x = (float)rect.left;
				v->texCoords.y = (float)rect.top;

				// top right
				v = &(this->m_vertex_array[vert_index + 1]);
				v->position.x = (float)((x + 1) * this->m_tilesize);
				v->position.y = (float)(y * this->m_tilesize);
				v->color = sf::Color::White;
				v->texCoords.x = (float)(rect.left + rect.width);
				v->texCoords.y = (float)rect.top;

				// bottom right
				v = &(this->m_vertex_array[vert_index + 2]);
				v->position.x = (float)((x + 1) * this->m_tilesize);
				v->position.y = (float)((y + 1) * this->m_tilesize);
				v->color = sf::Color::White;
				v->texCoords.x = (float)(rect.left + rect.width);
				v->texCoords.y = (float)(rect.top + rect.height);

				// bottom left
				v = &(this->m_vertex_array[vert_index + 3]);
				v->position.x = (float)(x * this->m_tilesize);
				v->position.y = (float)((y + 1) * this->m_tilesize);
				v->color = sf::Color::White;
				v->texCoords.x = (float)rect.left;
				v->texCoords.y = (float)(rect.top + rect.height);
			}
		}
	}

	bool Tilemap::is_valid_tile_position(int tile_x, int tile_y) {
		if (tile_x < 0 || tile_y < 0 || tile_x > this->m_width - 1 || tile_y > this->m_height - 1) {
			return false;
		}
		return true;
	}
}
