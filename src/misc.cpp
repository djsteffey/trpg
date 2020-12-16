#include "misc.hpp"
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

namespace trpg {
	namespace misc {
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

		void log(std::string tag, std::string format, ...) {
			// just forward on to printf
			printf("%s: ", tag.c_str());

			va_list args;
			va_start(args, format);
			vprintf(format.c_str(), args);
			printf("\n");
			va_end(args);
		}
	}
}