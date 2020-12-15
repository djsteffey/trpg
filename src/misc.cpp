#include "misc.hpp"
#include <cstdlib>

namespace trpg {
	EDirection random_direction() {
		return (EDirection)(std::rand() % 4);
	}

	sf::Vector2i direction_to_vector(EDirection dir) {
		switch (dir) {
			case EDirection::UP: { return sf::Vector2i(0, -1); } break;
			case EDirection::DOWN: { return sf::Vector2i(0, 1); } break;
			case EDirection::LEFT: { return sf::Vector2i(-1, 0); } break;
			case EDirection::RIGHT: { return sf::Vector2i(1, 0); } break;
		}
		return sf::Vector2i(0, 0);
	}
}