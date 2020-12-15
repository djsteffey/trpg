#include "ScreenBattle.hpp"

namespace trpg {
	ScreenBattle::ScreenBattle() {
		// assets
		this->m_asset_manager = std::make_unique<AssetManager>();
		this->m_asset_manager->load_texture("assets/actors_24x24.png");
		this->m_asset_manager->load_texture("assets/tiles_24x24.png");

		// tilemap
		this->m_tilemap = std::make_unique<Tilemap>(20, 15, 48);
		this->m_actor_manager = std::make_unique<ActorManager>();
		for (int i = 0; i < 5; ++i) {
			unsigned long id = this->m_actor_manager->add_actor(44, 48);
			Actor* actor = this->m_actor_manager->get_actor(id);
			actor->set_tile_position(rand() % 20, rand()% 15);
		}
	}

	ScreenBattle::~ScreenBattle() {

	}

	void ScreenBattle::update(int ms){
		this->m_tilemap->update(ms);
		this->m_actor_manager->update(ms, *this->m_tilemap);
	}

	void ScreenBattle::draw(sf::RenderWindow* rw) {
		this->m_tilemap->draw(rw);
		this->m_actor_manager->draw(rw);
	}
}
