#ifndef trpg_ScreenBattle_hpp
#define trpg_ScreenBattle_hpp

#include "ScreenAbstract.hpp"
#include "Tilemap.hpp"
#include "ActorManager.hpp"
#include <memory>
#include "AssetManager.hpp"

namespace trpg {
	class ScreenBattle: public ScreenAbstract{
	public:
		ScreenBattle();
		~ScreenBattle();
		void update(int ms) override;
		void draw(sf::RenderWindow* rw) override;

	protected:

	private:
		std::unique_ptr<Tilemap> m_tilemap;
		std::unique_ptr<ActorManager> m_actor_manager;
		std::unique_ptr<AssetManager> m_asset_manager;
	};
}

#endif