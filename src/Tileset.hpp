#ifndef trpg_Tileset_hpp
#define trpg_Tileset_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace trpg {
	class AssetManager;

	class Tileset {
	public:
		Tileset();
		~Tileset();

		bool init(AssetManager* am, std::string filename, int tilesize);
		const sf::Texture* get_texture() const;
		const sf::IntRect* get_rect(int index) const;

		int get_tilesize() const;

	protected:

	private:
		const sf::Texture* m_texture;
		std::vector<sf::IntRect> m_rects;
		int m_tilesize;
	};
}
#endif