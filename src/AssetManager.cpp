#include "AssetManager.hpp"

namespace trpg {
	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {

	}

	bool AssetManager::load_texture(std::string filename) {
		// see if already loaded
		auto find = this->m_textures.find(filename);
		if (find == this->m_textures.end()) {
			// not loaded; load it
			auto ptr = std::make_unique<sf::Texture>();
			if (ptr->loadFromFile(filename)) {
				// success
				this->m_textures[filename] = std::move(ptr);
			}
			else {
				// failed
				return false;
			}
		}

		// success
		return true;
	}

	const sf::Texture* AssetManager::get_texture(std::string filename) {
		// find it
		auto find = this->m_textures.find(filename);

		// check it
		if (find != this->m_textures.end()) {
			// found it
			return find->second.get();
		}

		// didnt find so try and load
		if (this->load_texture(filename)) {
			// loaded so now return it
			return this->m_textures[filename].get();
		}

		// failed to find and/or load
		return nullptr;
	}

	bool AssetManager::load_tileset(std::string filename, int tilesize) {

	}

	const Tileset* AssetManager::get_tileset(std::string filename) {

	}
}
