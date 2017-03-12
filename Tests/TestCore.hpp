#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/UnitTest.hpp"
#include "../Sources/System/Profiler.hpp"

#include "../Sources/Core/Application.hpp"
#include "../Sources/Core/State.hpp"

BEGIN_TEST(Core)
{
	TEST("Application")
	{
		class MyState : public oe::State
		{
			public:
				MyState() { }
				std::string getName() { return "MyState"; }
				bool handleEvent(const sf::Event& event) { return false; }
				bool update(oe::Time dt) { oe::log("ez"); return false; }
				void render(sf::RenderTarget& target) { }
		};

		oe::Application app;
		app.pushState<MyState>();
		app.run();
	}
}
END_TEST;