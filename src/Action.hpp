#ifndef trpg_Action_hpp
#define trpg_Action_hpp

#include <SFML/System.hpp>

namespace trpg {
	class Actor;

	class Action {
	public:
		Action();
		virtual ~Action();
		virtual bool update(int ms);

	protected:

	private:
	};

	class ActionMoveTo : public Action {
	public:
		ActionMoveTo(Actor* actor, int duration, sf::Vector2f start, sf::Vector2f end);
		~ActionMoveTo();
		bool update(int ms);

	protected:

	private:
		int m_duration;
		int m_current_duration;
		Actor* m_actor;
		sf::Vector2f m_start_position;
		sf::Vector2f m_end_position;
	};
}
#endif