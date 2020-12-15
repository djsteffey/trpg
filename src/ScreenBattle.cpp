#include "ScreenBattle.hpp"

namespace trpg {
	ScreenBattle::ScreenBattle() {
		this->m_tilemap = std::make_unique<Tilemap>(20, 15, 48);
		this->m_actor_manager = std::make_unique<ActorManager>();
		for (int i = 0; i < 5; ++i) {
			unsigned long id = this->m_actor_manager->add_actor(44, 48);
			Actor* actor = this->m_actor_manager->get_actor(id);
			actor->set_tile_position(i, i);
		}
	}

	ScreenBattle::~ScreenBattle() {

	}

	void ScreenBattle::update(int ms){
		this->m_tilemap->update(ms);
		this->m_actor_manager->update(ms, *this->m_tilemap);
	}

	void ScreenBattle::draw(sf::RenderWindow& rw) {
		this->m_tilemap->draw(rw);
		this->m_actor_manager->draw(rw);
	}
}
