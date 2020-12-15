#ifndef trpg_Tileset_hpp
#define trpg_Tileset_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace trpg {
	class Tileset {
	public:
		Tileset(std::string filename, int tilesize);
		~Tileset();
		const sf::Texture& get_texture() const;
		const sf::IntRect& get_rect(int index) const;
		int get_tilesize() const;
	protected:

	private:
		sf::Texture m_texture;
		std::vector<sf::IntRect> m_rects;
		int m_tilesize;
	};
}
#endif