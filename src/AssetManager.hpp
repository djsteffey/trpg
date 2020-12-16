#ifndef trpg_AssetManager_hpp
#define trpg_AssetManager_hpp

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tileset.hpp"

namespace trpg {
	class AssetManager {
	public:
		AssetManager();
		~AssetManager();
		bool init();
		bool load_texture(std::string filename);
		const sf::Texture* get_texture(std::string filename);
		bool load_tileset(std::string filename, int tilesize);
		const Tileset* get_tileset(std::string filename);

	protected:

	private:
		std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
		std::map<std::string, std::unique_ptr<Tileset>> m_tilesets;
	};
}
#endif