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

	//////////////////////////////////////////////////////////////////////////////

	ActionSequence::ActionSequence() {
		
	}

	ActionSequence::~ActionSequence() {

	}

	bool ActionSequence::update(int ms) {
		// update the front
		if (this->m_actions.front()->update(ms)) {
			// front action is done
			this->m_actions.pop_front();

			// see if out of actions
			if (this->m_actions.empty()) {
				// all done
				return true;
			}
		}

		// not done yet
		return false;
	}

	void ActionSequence::add_action(std::unique_ptr<Action> action) {
		this->m_actions.push_back(std::move(action));
	}

	//////////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////////

	ActionMeleeAttack::ActionMeleeAttack(Actor* actor, Actor* target, int duration, int tilesize) {
		// save the actors
		this->m_actor = actor;
		this->m_target = target;

		// compute start and end
		sf::Vector2f start = sf::Vector2f(actor->get_tile_position_x() * tilesi)

		// setup sequence
		auto ptr = std::make_unique<ActionMoveTo>(
			actor,
			duration / 2,
			std::
			)
	}

	ActionMeleeAttack::~ActionMeleeAttack() {

	}

	bool ActionMeleeAttack::update(int ms) {

	}

}

	protected:

	private:
		int m_duration;
		int m_current_duration;
		Actor* m_actor;
		Actor* m_target;
		ActionSequence m_sequence;