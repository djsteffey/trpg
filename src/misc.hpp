#ifndef trpg_misc_hpp
#define trpg_misc_hpp

#include <SFML/System.hpp>

namespace trpg {
	namespace misc {
		enum class EDirection {
			UP, DOWN, LEFT, RIGHT
		};
		EDirection random_direction();
		sf::Vector2i direction_to_vector(EDirection dir);

		void log(std::string tag, std::string format, ...);
	}
}
#endif