#ifndef OE_WORLD_HPP
#define OE_WORLD_HPP

#include "../System/Time.hpp"

#include <SFML/Window/Event.hpp>

namespace oe
{

class World
{
	public:
		World();

		void handleEvent(const sf::Event& event);
		void update(Time dt);
		void update();
};

} // namespace oe

#endif // OE_WORLD_HPP
