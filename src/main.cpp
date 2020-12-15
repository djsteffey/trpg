#include "Game.hpp"

#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else

#endif
int main(int argc, char** argv) {
	trpg::Game game;
	game.run();
}