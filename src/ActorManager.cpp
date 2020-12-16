#include "ActorManager.hpp"
#include "Tileset.hpp"
#include "Actor.hpp"
#include "AssetManager.hpp"
#include "misc.hpp"

namespace trpg {
	ActorManager::ActorManager() {
		this->m_next_id = -11;
		this->m_tileset = nullptr;
	}

	ActorManager::~ActorManager() {

	}

	bool ActorManager::init(AssetManager* am) {
		// setup id
		this->m_next_id = 1;

		// get tileset
		this->m_tileset = am->get_tileset("assets/actors_24x24.png");
		if (this->m_tileset == nullptr) {
			misc::log("ActorManager::init()", "error getting tileset %s", "assets/actors_24x24.png");
			return false;
		}

		// done
		return true;
	}

	void ActorManager::update(int ms, Tilemap& tilemap) {
		for (auto& kvp : this->m_actors) {
			kvp.second->update(ms, tilemap, *this);
		}
	}

	void ActorManager::draw(sf::RenderWindow* rw) {
		for (auto& kvp : this->m_actors) {
			kvp.second->draw(rw);
		}
	}

	unsigned long ActorManager::add_actor(int graphics_id, int size){
		unsigned long id = this->m_next_id++;
		std::unique_ptr<Actor> actor = std::make_unique<Actor>();
		if (actor->init(id, 34, 48, this->m_tileset) == false) {
			misc::log("ActorManager::init()", "error init actor");
			return 0;
		}
		this->m_actors[id] = std::move(actor);
		return id;
	}

	Actor* ActorManager::get_actor(unsigned long id) {
		return this->m_actors[id].get();
	}
}
