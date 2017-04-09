#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/UnitTest.hpp"
#include "../Sources/System/Profiler.hpp"

#include "../Sources/Core/Application.hpp"
#include "../Sources/Core/State.hpp"
#include "../Sources/Core/World.hpp"
#include "../Sources/Core/Entity.hpp"
#include "../Sources/Core/Components/SpriteComponent.hpp"
#include "../Sources/Core/Components/TextComponent.hpp"

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "../Sources/System/SFML.hpp"

BEGIN_TEST(Core)
{
	TEST("Overall")
	{
		class MyEntity : public oe::Entity
		{
			public:
				MyEntity(oe::World& world)
					: oe::Entity(world)
					, mSprite(this)
					, mText(this)
				{
				}

				oe::SpriteComponent& getSprite()
				{
					return mSprite;
				}

				oe::TextComponent& getText()
				{
					return mText;
				}

			private:
				oe::SpriteComponent mSprite;
				oe::TextComponent mText;
		};
		
		class MyState : public oe::State
		{
			public:
				MyState()
				{
					oe::ResourceId hero = mWorld.getTextures().create("hero", "Assets/hero.png");
					oe::ResourceId font = mWorld.getFonts().create("font", "Assets/font.ttf");
					oe::ResourceId theme = mWorld.getAudioSystem().createMusic("theme", "Assets/theme.ogg");
					mSelectSound = mWorld.getAudioSystem().createSound("select", "Assets/select.wav");

					for (U32 i = 0; i < 100; i++)
					{
						oe::EntityHandle h = mWorld.createEntity<MyEntity>();
						MyEntity* e = h.getAs<MyEntity>();
						e->setPosition(oe::Vector2(i * i * 10.0f, 0.0f));
						oe::SpriteComponent& sprite = e->getSprite();
						sprite.setTexture(hero);
						sprite.setPosition(oe::Vector2(i * 80.0f, i * 60.0f));
						sprite.setPositionZ(i * 10.0f);
						sprite.setVisible(true);
						oe::TextComponent& text = e->getText();
						text.setFont(font);
						text.setString("HelloWorld");
						text.setFillColor(oe::Color::Black);
						text.setOutlineColor(oe::Color::Red);
						text.setOutlineThickness(1.0f);
						text.setPosition(0.0f, 30.0f, 1000.0f);
						if (i > 0)
						{
							text.setVisible(false);
						}
					}

					mWorld.getAudioSystem().playMusic(theme, true);
				}

				std::string getName()
				{
					return "MyState";
				}

				bool handleEvent(const sf::Event& event)
				{
					if (event.type == sf::Event::KeyPressed)
					{
						mWorld.getAudioSystem().playSound(mSelectSound);
					}
					return false;
				}

				bool update(oe::Time dt)
				{
					mWorld.update();
					mWorld.update(dt);
					oe::Application::getSingleton().getWindow().setTitle("TestCore : " + oe::toString(oe::Application::getSingleton().getFPSCount()));
					return false;
				}

				void render(sf::RenderTarget& target)
				{
					mWorld.render(target);
				}

			private:
				oe::Clock mClock;
				oe::World mWorld;
				oe::ResourceId mSelectSound;
		};

		oe::Application app;
		app.pushState<MyState>();
		app.run();
	}
}
END_TEST;