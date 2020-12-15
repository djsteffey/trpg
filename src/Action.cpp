#include "Action.hpp"
#include "Actor.hpp"

namespace trpg {
	Action::Action() {

	}

	Action::~Action() {

	}

	bool Action::update(int ms) {
		return true;
	}

	ActionMoveTo::ActionMoveTo(Actor* actor, int duration, sf::Vector2f start, sf::Vector2f end) {
		this->m_duration = duration;
		this->m_current_duration = 0;
		this->m_actor = actor;
		this->m_start_position = start;
		this->m_end_position = end;
	}

	ActionMoveTo::~ActionMoveTo() {

	}

	bool ActionMoveTo::update(int ms) {
		this->m_current_duration += ms;
		if (this->m_current_duration > this->m_duration) {
			this->m_current_duration = this->m_duration;
		}
		float percent = (float)this->m_current_duration / this->m_duration;
		float x = this->m_start_position.x + (this->m_end_position.x - this->m_start_position.x) * percent;
		float y = this->m_start_position.y + (this->m_end_position.y - this->m_start_position.y) * percent;
		this->m_actor->set_sprite_position(x, y);
		if (this->m_current_duration == this->m_duration) {
			return true;
		}
		return false;
	}
}
