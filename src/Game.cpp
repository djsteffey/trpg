#include "Game.hpp"
#include "ScreenBattle.hpp"
#include "misc.hpp"

namespace trpg {
	Game::Game() {

	}

	Game::~Game() {

	}

	void Game::run() {
		// create the render window
		this->m_render_window.create(
			sf::VideoMode(1280, 720),
			"TRPG",
			sf::Style::Close | sf::Style::Titlebar
		);

		// init
		this->m_screen = std::make_unique<ScreenBattle>();
		if (this->m_screen->init() == false) {
			misc::log("Game::init()", "error init screen");
			return;
		}

		// loop while the window is open
		while (this->m_render_window.isOpen()){
			// game loop
			this->process_events();
			this->update();
			this->draw();
		}
	}

	void Game::process_events() {
		sf::Event event;
		while (this->m_render_window.pollEvent(event)) {
			// handle the event
			switch (event.type) {
				case sf::Event::Closed:{
					this->m_render_window.close();
				} break;
				case sf::Event::KeyPressed: {
					if (event.key.code == sf::Keyboard::Escape) {
						this->m_render_window.close();
					}
				} break;
			}
		}
	}

	void Game::update() {
		static sf::Clock clock;
		int ms = clock.restart().asMilliseconds();
		this->m_screen->update(ms);
	}

	void Game::draw() {
		// clear
		this->m_render_window.clear();

		// draw stuff
		this->m_screen->draw(&(this->m_render_window));

		// present
		this->m_render_window.display();
	}
}