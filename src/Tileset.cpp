#include "Tileset.hpp"
#include "AssetManager.hpp"
#include "misc.hpp"

namespace trpg {
	Tileset::Tileset() {
		this->m_tilesize = -1;
		this->m_texture = nullptr;
	}

	Tileset::~Tileset() {

	}

	bool Tileset::init(AssetManager* am, std::string filename, int tilesize) {
		// size
		this->m_tilesize = tilesize;

		// load the texture
		this->m_texture = am->get_texture(filename);
		if (this->m_texture == nullptr) {
			misc::log("Tileset::init()", "error getting texture %s", filename.c_str());
			return false;
		}

		// create the rects
		for (unsigned int y = 0; y < this->m_texture->getSize().y; y += this->m_tilesize) {
			for (unsigned int x = 0; x < this->m_texture->getSize().x; x += this->m_tilesize) {
				this->m_rects.push_back(sf::IntRect(x, y, this->m_tilesize, this->m_tilesize));
			}
		}

		// done
		return true;
	}

	const sf::Texture* Tileset::get_texture() const {
		return this->m_texture;
	}

	const sf::IntRect* Tileset::get_rect(int index) const {
		return &(this->m_rects[index]);
	}

	int Tileset::get_tilesize() const {
		return this->m_tilesize;
	}
}
