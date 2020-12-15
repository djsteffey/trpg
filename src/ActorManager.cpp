#include "ActorManager.hpp"

namespace trpg {
	ActorManager::ActorManager() {
		this->m_next_id = 1;
		this->m_tileset = std::make_unique<Tileset>("assets/actors_24x24.png", 24);
	}

	ActorManager::~ActorManager() {

	}

	void ActorManager::update(int ms, Tilemap& tilemap) {
		for (auto& kvp : this->m_actors) {
			kvp.second->update(ms, tilemap, *this);
		}
	}

	void ActorManager::draw(sf::RenderWindow& rw) {
		for (auto& kvp : this->m_actors) {
			kvp.second->draw(rw);
		}
	}

	unsigned long ActorManager::add_actor(int graphics_id, int size){
		unsigned long id = this->m_next_id++;
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(id, 34, 48, *this->m_tileset);
		this->m_actors[id] = std::move(actor);
		return id;
	}

	Actor* ActorManager::get_actor(unsigned long id) {
		return this->m_actors[id].get();
	}
}
