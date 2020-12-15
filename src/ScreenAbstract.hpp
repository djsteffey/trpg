#ifndef trpg_ScreenAbstract_hpp
#define trpg_ScreenAbstract_hpp

#include <SFML/Graphics.hpp>

namespace trpg {
	class ScreenAbstract {
	public:
		ScreenAbstract();
		virtual ~ScreenAbstract();
		virtual void update(int ms) = 0;
		virtual void draw(sf::RenderWindow* rw) = 0;

	protected:

	private:
	};
}

#endif