#include "ScreenBattle.hpp"
#include "Actor.hpp"
#include "misc.hpp"

namespace trpg {
	ScreenBattle::ScreenBattle() {
		this->m_asset_manager = nullptr;
		this->m_tilemap = nullptr;
		this->m_actor_manager = nullptr;
	}

	ScreenBattle::~ScreenBattle() {

	}

	bool ScreenBattle::init() {
		// assets
		this->m_asset_manager = std::make_unique<AssetManager>();
		if (this->m_asset_manager->init() == false) {
			misc::log("ScreenBattle::init()", "error init asset manager");
			return false;
		}
		if (this->m_asset_manager->load_texture("assets/actors_24x24.png") == false) {
			misc::log("ScreenBattle::init()", "error loading texture %s", "assets/actors_24x24.png");
			return false;
		}
		if (this->m_asset_manager->load_texture("assets/tiles_24x24.png") == false) {
			misc::log("ScreenBattle::init()", "error loading texture %s", "assets/tiles_24x24.png");
			return false;
		}
		if (this->m_asset_manager->load_tileset("assets/tiles_24x24.png", 24) == false) {
			misc::log("ScreenBattle::init()", "error loading tileset %s", "assets/tiles_24x24.png");
			return false;
		}
		if (this->m_asset_manager->load_tileset("assets/actors_24x24.png", 24) == false) {
			misc::log("ScreenBattle::init()", "error loading tileset %s", "assets/actors_24x24.png");
			return false;
		}

		// tilemap
		this->m_tilemap = std::make_unique<Tilemap>();
		if (this->m_tilemap->init(this->m_asset_manager.get(), 20, 15, 48) == false) {
			misc::log("ScreenBattle::init()", "error init tilemap");
			return false;
		}

		// actors
		this->m_actor_manager = std::make_unique<ActorManager>();
		if (this->m_actor_manager->init(this->m_asset_manager.get()) == false) {
			misc::log("ScreenBattle::init()", "error init actor manager");
			return false;
		}
		for (int i = 0; i < 5; ++i) {
			unsigned long id = this->m_actor_manager->add_actor(44, 48);
			if (id == 0) {
				misc::log("ScreenBattle::init()", "error adding actor");
				return false;
			}
			Actor* actor = this->m_actor_manager->get_actor(id);
			actor->set_tile_position(rand() % 20, rand() % 15, true);
		}

		// done
		return true;
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
