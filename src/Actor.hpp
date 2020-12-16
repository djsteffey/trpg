#ifndef trpg_Actor_hpp
#define trpg_Actor_hpp

#include <SFML/Graphics.hpp>
#include "Tileset.hpp"
#include "Action.hpp"
#include <memory>

namespace trpg {
	class Tilemap;
	class ActorManager;

	struct ActorStats{
		int m_speed;
		int m_speed_counter;
	};

	class Actor {
	public:
		Actor();
		~Actor();
		bool init(unsigned long id, int graphics_id, int size, const Tileset* tileset);
		void update(int ms, Tilemap& tilemap, ActorManager& am);
		void draw(sf::RenderWindow* rw);
		unsigned long get_id() const;
		void set_tile_position(int tile_x, int tile_y, bool set_sprite_position);
		void set_sprite_position(float x, float y);
		void ai(Tilemap& tilemap, ActorManager& am);
		int get_tile_position_x() const;
		int get_tile_position_y() const;

	protected:

	private:
		unsigned long m_id;
		int m_graphics_id;
		int m_size;
		int m_tile_x;
		int m_tile_y;
		sf::Sprite m_sprite;
		ActorStats m_stats;
		std::vector<std::unique_ptr<Action>> m_actions;
	};
}
#endif