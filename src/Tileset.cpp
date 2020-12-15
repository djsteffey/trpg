#include "Tileset.hpp"

namespace trpg {
	Tileset::Tileset(std::string filename, int tilesize) {
		// size
		this->m_tilesize = tilesize;

		// load the texture
		this->m_texture.loadFromFile(filename);

		// create the rects
		for (int y = 0; y < this->m_texture.getSize().y; y += this->m_tilesize) {
			for (int x = 0; x < this->m_texture.getSize().x; x += this->m_tilesize) {
				this->m_rects.push_back(sf::IntRect(x, y, this->m_tilesize, this->m_tilesize));
			}
		}
	}

	Tileset::~Tileset() {

	}

	const sf::Texture& Tileset::get_texture() const {
		return this->m_texture;
	}

	const sf::IntRect& Tileset::get_rect(int index) const {
		return this->m_rects[index];
	}

	int Tileset::get_tilesize() const {
		return this->m_tilesize;
	}
}
