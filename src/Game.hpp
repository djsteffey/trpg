#ifndef trpg_Game_hpp
#define trpg_Game_hpp

#include <SFML/Graphics.hpp>
#include "ScreenAbstract.hpp"

namespace trpg {
	class Game {
	public:
		Game();
		~Game();
		void run();

	protected:

	private:
		void process_events();
		void update();
		void draw();

		sf::RenderWindow m_render_window;
		std::unique_ptr<ScreenAbstract> m_screen;
	};
}
#endif