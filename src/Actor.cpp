#include "Actor.hpp"
#include "misc.hpp"
#include "Tilemap.hpp"

namespace trpg {
	Actor::Actor(unsigned long id, int graphics_id, int size, const Tileset& tileset) {
		// actor id and graphics and size
		this->m_id = id;
		this->m_graphics_id = graphics_id;
		this->m_size = size;

		// initial tile position is not on map
		this->m_tile_x = -1;
		this->m_tile_y = -1;

		// setup the sprite
		this->m_sprite.setPosition((float)(this->m_tile_x * this->m_size), (float)(this->m_tile_x * this->m_size));
		this->m_sprite.setTexture(*(tileset.get_texture()));
		this->m_sprite.setTextureRect(*(tileset.get_rect(this->m_graphics_id)));
		this->m_sprite.setScale(
			(float)size / tileset.get_tilesize(),
			(float)size / tileset.get_tilesize()
		);

		// setup the stats
		std::memset(&this->m_stats, sizeof(this->m_stats), 0);
		this->m_stats.m_speed = rand() % 500 + 1000;
		this->m_stats.m_speed_counter = 0;
	}

	Actor::~Actor() {

	}

	void Actor::update(int ms, Tilemap& tilemap, ActorManager& am) {
		// see if time to do a turn
		this->m_stats.m_speed_counter += ms;
		if (this->m_stats.m_speed_counter >= this->m_stats.m_speed){
			this->ai(tilemap, am);
			this->m_stats.m_speed_counter -= this->m_stats.m_speed;
		}

		// update actions
		for (auto iter = this->m_actions.begin(); iter != this->m_actions.end(); ){
			if ((*iter)->update(ms)) {
				// action done
				iter = this->m_actions.erase(iter);
			}
			else {
				++iter;
			}
		}
	}

	void Actor::draw(sf::RenderWindow* rw) {
		rw->draw(this->m_sprite);
	}

	unsigned long Actor::get_id() const {
		return this->m_id;
	}

	void Actor::set_tile_position(int tile_x, int tile_y) {
		this->m_tile_x = tile_x;
		this->m_tile_y = tile_y;
//		this->m_sprite.setPosition((float)(this->m_tile_x * this->m_size), (float)(this->m_tile_y * this->m_size));
	}

	void Actor::set_sprite_position(float x, float y) {
		this->m_sprite.setPosition(x, y);
	}

	void Actor::ai(Tilemap& tilemap, ActorManager& am) {
		// just move
		EDirection dir = random_direction();
		sf::Vector2i vec = direction_to_vector(dir);
		int new_x = this->m_tile_x + vec.x;
		int new_y = this->m_tile_y + vec.y;
		if (tilemap.is_valid_tile_position(new_x, new_y)) {
			this->set_tile_position(new_x, new_y);
			this->m_actions.push_back(
				std::make_unique<ActionMoveTo>(
					this,
					250,
					this->m_sprite.getPosition(),
					sf::Vector2f((float)(this->m_tile_x * this->m_size), (float)(this->m_tile_y * this->m_size))
					)
			);
		}
	}
}
