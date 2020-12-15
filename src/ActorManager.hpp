#ifndef trpg_ActorManager_hpp
#define trpg_ActorManager_hpp

#include <SFML/Graphics.hpp>
#include "Tileset.hpp"
#include <map>
#include <memory>
#include "Actor.hpp"

namespace trpg {
	class ActorManager {
	public:
		ActorManager();
		~ActorManager();
		void update(int ms, Tilemap& tilemap);
		void draw(sf::RenderWindow& rw);
		unsigned long add_actor(int graphics_id, int size);
		Actor* get_actor(unsigned long id);

	protected:

	private:
		unsigned long m_next_id;
		std::unique_ptr<Tileset> m_tileset;
		std::map<unsigned long, std::unique_ptr<Actor>> m_actors;
	};
}
#endif