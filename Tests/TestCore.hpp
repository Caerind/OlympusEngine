#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/UnitTest.hpp"
#include "../Sources/System/Profiler.hpp"

#include "../Sources/Core/Application.hpp"
#include "../Sources/Core/State.hpp"
#include "../Sources/Core/World.hpp"
#include "../Sources/Core/Entity.hpp"
#include "../Sources/Core/Map.hpp"
#include "../Sources/Core/Components/SpriteComponent.hpp"
#include "../Sources/Core/Components/TextComponent.hpp"
#include "../Sources/Core/Components/LayerComponent.hpp"
#include "../Sources/Core/Components/ViewComponent.hpp"
#include "../Sources/Core/Components/ParticleComponent.hpp"
#include "../Sources/Core/Components/AnimatorComponent.hpp"

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
				MyState(oe::Application& application) 
					: oe::State(application)
					, mWorld(application)
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
					mApplication.getWindow().setTitle("TestCore : " + oe::toString(mApplication.getFPSCount()));
					return false;
				}

				void render(sf::RenderTarget& target)
				{
					mWorld.render(target);
				}

			private:
				oe::World mWorld;
				oe::ResourceId mSelectSound;
		};

		oe::Application app;
		app.pushState<MyState>();
		app.run();
	}

	TEST("Map")
	{
		class MyEntity : public oe::Entity
		{
			public:
				MyEntity(oe::World& world)
					: oe::Entity(world)
					, mSprite(this)
					, mView(this)
				{
				}

				oe::SpriteComponent& getSprite()
				{
					return mSprite;
				}

				oe::ViewComponent& getView()
				{
					return mView;
				}

			private:
				oe::SpriteComponent mSprite;
				oe::ViewComponent mView;
		};

		class MyState : public oe::State
		{
			public:
				MyState(oe::Application& application)
					: oe::State(application)
					, mWorld(application)
					, mMap()
					, mMapState(0)
					, mTileset()
				{
					mApplication.getWindow().setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f)));
					mApplication.getWindow().applyMainView();

					oe::EntityHandle vch = mWorld.createEntity<MyEntity>();
					MyEntity* vc = vch.getAs<MyEntity>();
					vc->setPosition(100.f, 100.f);

					mTileset.setImageSource("Assets/orthogonal.png");
					mTileset.setTileSize(oe::Vector2i(16, 16));
					mTileset.setTileCount(104);
					mTileset.setColumns(8);
					mMap = mWorld.createEntity<oe::Map>();
					oe::Map* map = mMap.getAs<oe::Map>();
					map->setTileset(&mTileset);
					map->setOrientation(oe::MapUtility::Orthogonal);
					map->setSize(oe::Vector2i(5, 5));
					map->setTileSize(oe::Vector2i(16, 16));
					map->setStaggerAxis(oe::MapUtility::Y);
					map->setStaggerIndex(oe::MapUtility::Odd);
					map->setHexSideLength(0);
					oe::LayerComponent& layer = map->addLayer();
					layer.setTileId(oe::Vector2i(0, 0), 53);
					layer.setTileId(oe::Vector2i(1, 0), 54);
					layer.setTileId(oe::Vector2i(2, 0), 55);
					layer.setTileId(oe::Vector2i(3, 0), 48);
					layer.setTileId(oe::Vector2i(4, 0), 48);
					layer.setTileId(oe::Vector2i(0, 1), 61);
					layer.setTileId(oe::Vector2i(1, 1), 62);
					layer.setTileId(oe::Vector2i(2, 1), 63);
					layer.setTileId(oe::Vector2i(3, 1), 48);
					layer.setTileId(oe::Vector2i(4, 1), 48);
					layer.setTileId(oe::Vector2i(0, 2), 69);
					layer.setTileId(oe::Vector2i(1, 2), 70);
					layer.setTileId(oe::Vector2i(2, 2), 71);
					layer.setTileId(oe::Vector2i(3, 2), 48);
					layer.setTileId(oe::Vector2i(4, 2), 48);
					layer.setTileId(oe::Vector2i(0, 3), 48);
					layer.setTileId(oe::Vector2i(1, 3), 48);
					layer.setTileId(oe::Vector2i(2, 3), 48);
					layer.setTileId(oe::Vector2i(3, 3), 48);
					layer.setTileId(oe::Vector2i(4, 3), 48);
					layer.setTileId(oe::Vector2i(0, 4), 48);
					layer.setTileId(oe::Vector2i(1, 4), 48);
					layer.setTileId(oe::Vector2i(2, 4), 48);
					layer.setTileId(oe::Vector2i(3, 4), 48);
					layer.setTileId(oe::Vector2i(4, 4), 48);
				}

				std::string getName()
				{
					return "MyState";
				}

				bool handleEvent(const sf::Event& event)
				{
					if (event.type == sf::Event::KeyPressed)
					{
						mMapState++;
						if (mMapState > 5)
						{
							mMapState = 0;
						}

						switch (mMapState)
						{
							case 0: // Ortho
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/orthogonal.png");
								mTileset.setTileSize(oe::Vector2i(16, 16));
								mTileset.setTileCount(104);
								mTileset.setColumns(8);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Orthogonal);
								map->setSize(oe::Vector2i(5, 5));
								map->setTileSize(oe::Vector2i(16, 16));
								map->setStaggerAxis(oe::MapUtility::Y);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(0);
								oe::LayerComponent& layer = map->addLayer();
								layer.setTileId(oe::Vector2i(0, 0), 53);
								layer.setTileId(oe::Vector2i(1, 0), 54);
								layer.setTileId(oe::Vector2i(2, 0), 55);
								layer.setTileId(oe::Vector2i(3, 0), 48);
								layer.setTileId(oe::Vector2i(4, 0), 48);
								layer.setTileId(oe::Vector2i(0, 1), 61);
								layer.setTileId(oe::Vector2i(1, 1), 62);
								layer.setTileId(oe::Vector2i(2, 1), 63);
								layer.setTileId(oe::Vector2i(3, 1), 48);
								layer.setTileId(oe::Vector2i(4, 1), 48);
								layer.setTileId(oe::Vector2i(0, 2), 69);
								layer.setTileId(oe::Vector2i(1, 2), 70);
								layer.setTileId(oe::Vector2i(2, 2), 71);
								layer.setTileId(oe::Vector2i(3, 2), 48);
								layer.setTileId(oe::Vector2i(4, 2), 48);
								layer.setTileId(oe::Vector2i(0, 3), 48);
								layer.setTileId(oe::Vector2i(1, 3), 48);
								layer.setTileId(oe::Vector2i(2, 3), 48);
								layer.setTileId(oe::Vector2i(3, 3), 48);
								layer.setTileId(oe::Vector2i(4, 3), 48);
								layer.setTileId(oe::Vector2i(0, 4), 48);
								layer.setTileId(oe::Vector2i(1, 4), 48);
								layer.setTileId(oe::Vector2i(2, 4), 48);
								layer.setTileId(oe::Vector2i(3, 4), 48);
								layer.setTileId(oe::Vector2i(4, 4), 48);
								mColor = 48;
							} break;

							case 1: // Iso
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/isometric.png");
								mTileset.setTileSize(oe::Vector2i(64, 32));
								mTileset.setTileCount(6);
								mTileset.setColumns(2);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Isometric);
								map->setSize(oe::Vector2i(5, 5));
								map->setTileSize(oe::Vector2i(64, 32));
								map->setStaggerAxis(oe::MapUtility::Y);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(0);
								oe::LayerComponent& layer = map->addLayer();
								layer.setTileId(oe::Vector2i(0, 0), 2);
								layer.setTileId(oe::Vector2i(1, 0), 2);
								layer.setTileId(oe::Vector2i(2, 0), 2);
								layer.setTileId(oe::Vector2i(3, 0), 2);
								layer.setTileId(oe::Vector2i(4, 0), 2);
								layer.setTileId(oe::Vector2i(0, 1), 6);
								layer.setTileId(oe::Vector2i(1, 1), 6);
								layer.setTileId(oe::Vector2i(2, 1), 6);
								layer.setTileId(oe::Vector2i(3, 1), 6);
								layer.setTileId(oe::Vector2i(4, 1), 6);
								layer.setTileId(oe::Vector2i(0, 2), 3);
								layer.setTileId(oe::Vector2i(1, 2), 3);
								layer.setTileId(oe::Vector2i(2, 2), 3);
								layer.setTileId(oe::Vector2i(3, 2), 3);
								layer.setTileId(oe::Vector2i(4, 2), 3);
								layer.setTileId(oe::Vector2i(0, 3), 4);
								layer.setTileId(oe::Vector2i(1, 3), 4);
								layer.setTileId(oe::Vector2i(2, 3), 4);
								layer.setTileId(oe::Vector2i(3, 3), 4);
								layer.setTileId(oe::Vector2i(4, 3), 4);
								layer.setTileId(oe::Vector2i(0, 4), 5);
								layer.setTileId(oe::Vector2i(1, 4), 5);
								layer.setTileId(oe::Vector2i(2, 4), 5);
								layer.setTileId(oe::Vector2i(3, 4), 5);
								layer.setTileId(oe::Vector2i(4, 4), 5);
								mColor = 6;
							} break;

							case 2: // Staggered
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/isometric.png");
								mTileset.setTileSize(oe::Vector2i(64, 32));
								mTileset.setTileCount(6);
								mTileset.setColumns(2);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Staggered);
								map->setSize(oe::Vector2i(5, 5));
								map->setTileSize(oe::Vector2i(64, 32));
								map->setStaggerAxis(oe::MapUtility::Y);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(0);
								oe::LayerComponent& layer = map->addLayer();
								layer.setTileId(oe::Vector2i(0, 0), 2);
								layer.setTileId(oe::Vector2i(1, 0), 2);
								layer.setTileId(oe::Vector2i(2, 0), 2);
								layer.setTileId(oe::Vector2i(3, 0), 2);
								layer.setTileId(oe::Vector2i(4, 0), 2);
								layer.setTileId(oe::Vector2i(0, 1), 2);
								layer.setTileId(oe::Vector2i(1, 1), 2);
								layer.setTileId(oe::Vector2i(2, 1), 2);
								layer.setTileId(oe::Vector2i(3, 1), 2);
								layer.setTileId(oe::Vector2i(4, 1), 2);
								layer.setTileId(oe::Vector2i(0, 2), 2);
								layer.setTileId(oe::Vector2i(1, 2), 3);
								layer.setTileId(oe::Vector2i(2, 2), 5);
								layer.setTileId(oe::Vector2i(3, 2), 4);
								layer.setTileId(oe::Vector2i(4, 2), 6);
								layer.setTileId(oe::Vector2i(0, 3), 2);
								layer.setTileId(oe::Vector2i(1, 3), 2);
								layer.setTileId(oe::Vector2i(2, 3), 2);
								layer.setTileId(oe::Vector2i(3, 3), 2);
								layer.setTileId(oe::Vector2i(4, 3), 2);
								layer.setTileId(oe::Vector2i(0, 4), 2);
								layer.setTileId(oe::Vector2i(1, 4), 2);
								layer.setTileId(oe::Vector2i(2, 4), 2);
								layer.setTileId(oe::Vector2i(3, 4), 2);
								layer.setTileId(oe::Vector2i(4, 4), 2);
								mColor = 6;
							} break;

							case 3: // Hexa Pointy
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/hexapointy.png");
								mTileset.setTileSize(oe::Vector2i(60, 80));
								mTileset.setTileCount(12);
								mTileset.setColumns(4);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Hexagonal);
								map->setSize(oe::Vector2i(5, 5));
								map->setTileSize(oe::Vector2i(60, 52));
								map->setStaggerAxis(oe::MapUtility::Y);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(28);
								oe::LayerComponent& layer = map->addLayer();
								layer.setTileId(oe::Vector2i(0, 0), 5);
								layer.setTileId(oe::Vector2i(1, 0), 5);
								layer.setTileId(oe::Vector2i(2, 0), 5);
								layer.setTileId(oe::Vector2i(3, 0), 5);
								layer.setTileId(oe::Vector2i(4, 0), 5);
								layer.setTileId(oe::Vector2i(0, 1), 8);
								layer.setTileId(oe::Vector2i(1, 1), 8);
								layer.setTileId(oe::Vector2i(2, 1), 8);
								layer.setTileId(oe::Vector2i(3, 1), 8);
								layer.setTileId(oe::Vector2i(4, 1), 8);
								layer.setTileId(oe::Vector2i(0, 2), 7);
								layer.setTileId(oe::Vector2i(1, 2), 7);
								layer.setTileId(oe::Vector2i(2, 2), 7);
								layer.setTileId(oe::Vector2i(3, 2), 7);
								layer.setTileId(oe::Vector2i(4, 2), 7);
								layer.setTileId(oe::Vector2i(0, 3), 5);
								layer.setTileId(oe::Vector2i(1, 3), 5);
								layer.setTileId(oe::Vector2i(2, 3), 5);
								layer.setTileId(oe::Vector2i(3, 3), 5);
								layer.setTileId(oe::Vector2i(4, 3), 5);
								layer.setTileId(oe::Vector2i(0, 4), 6);
								layer.setTileId(oe::Vector2i(1, 4), 6);
								layer.setTileId(oe::Vector2i(2, 4), 6);
								layer.setTileId(oe::Vector2i(3, 4), 6);
								layer.setTileId(oe::Vector2i(4, 4), 6);
								mColor = 6;
							} break;

							case 4: // Hexa Flat
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/hexaflat.png");
								mTileset.setTileSize(oe::Vector2i(60, 60));
								mTileset.setTileCount(12);
								mTileset.setColumns(4);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Hexagonal);
								map->setSize(oe::Vector2i(5, 5));
								map->setTileSize(oe::Vector2i(60, 39));
								map->setStaggerAxis(oe::MapUtility::X);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(30);
								oe::LayerComponent& layer = map->addLayer();
								layer.setTileId(oe::Vector2i(0, 0), 5);
								layer.setTileId(oe::Vector2i(1, 0), 5);
								layer.setTileId(oe::Vector2i(2, 0), 5);
								layer.setTileId(oe::Vector2i(3, 0), 5);
								layer.setTileId(oe::Vector2i(4, 0), 5);
								layer.setTileId(oe::Vector2i(0, 1), 8);
								layer.setTileId(oe::Vector2i(1, 1), 8);
								layer.setTileId(oe::Vector2i(2, 1), 8);
								layer.setTileId(oe::Vector2i(3, 1), 8);
								layer.setTileId(oe::Vector2i(4, 1), 8);
								layer.setTileId(oe::Vector2i(0, 2), 7);
								layer.setTileId(oe::Vector2i(1, 2), 7);
								layer.setTileId(oe::Vector2i(2, 2), 7);
								layer.setTileId(oe::Vector2i(3, 2), 7);
								layer.setTileId(oe::Vector2i(4, 2), 7);
								layer.setTileId(oe::Vector2i(0, 3), 5);
								layer.setTileId(oe::Vector2i(1, 3), 5);
								layer.setTileId(oe::Vector2i(2, 3), 5);
								layer.setTileId(oe::Vector2i(3, 3), 5);
								layer.setTileId(oe::Vector2i(4, 3), 5);
								layer.setTileId(oe::Vector2i(0, 4), 6);
								layer.setTileId(oe::Vector2i(1, 4), 6);
								layer.setTileId(oe::Vector2i(2, 4), 6);
								layer.setTileId(oe::Vector2i(3, 4), 6);
								layer.setTileId(oe::Vector2i(4, 4), 6);
								mColor = 6;
							} break;

							case 5: // Hexa Pointy 2 
							{
								mWorld.killEntity(mMap);
								mTileset.setImageSource("Assets/hexapointy2.png");
								mTileset.setTileSize(oe::Vector2i(60, 80));
								mTileset.setTileCount(3);
								mTileset.setColumns(3);
								mMap = mWorld.createEntity<oe::Map>();
								oe::Map* map = mMap.getAs<oe::Map>();
								map->setTileset(&mTileset);
								map->setOrientation(oe::MapUtility::Hexagonal);
								map->setSize(oe::Vector2i(30, 30));
								map->setTileSize(oe::Vector2i(60, 52));
								map->setStaggerAxis(oe::MapUtility::Y);
								map->setStaggerIndex(oe::MapUtility::Odd);
								map->setHexSideLength(28);
								oe::LayerComponent& layer = map->addLayer();
								oe::Vector2i c;
								for (c.x = 0; c.x < 30; c.x++)
								{
									for (c.y = 0; c.y < 30; c.y++)
									{
										layer.setTileId(oe::Vector2i(c.x, c.y), 1);
									}
								}
								mColor = 2;
								mColor2 = 3;
							} break;
						}
					}
					return false;
				}

				bool update(oe::Time dt)
				{
					mWorld.update();
					mWorld.update(dt);
					mApplication.getWindow().setTitle("TestCore : " + oe::toString(mApplication.getFPSCount()));

					oe::Vector2i coords = mMap.getAs<oe::Map>()->worldToCoords(mApplication.getWindow().getCursorPosition());
					if (coords != mLastCoords)
					{
						mLastCoords = coords;
						//printf("%d, %d\n", coords.x, coords.y);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						mMap.getAs<oe::Map>()->getLayer().setTileId(coords, mColor);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						mMap.getAs<oe::Map>()->getLayer().setTileId(coords, mColor2);
					}
					return false;
				}

				void render(sf::RenderTarget& target)
				{
					mWorld.render(target);
				}

			private:
				oe::World mWorld;
				U32 mMapState;
				oe::Tileset mTileset;
				oe::EntityHandle mMap;
				oe::Vector2i mLastCoords;
				oe::TileId mColor;
				oe::TileId mColor2;
		};

		oe::Application app;
		app.pushState<MyState>();
		app.run();
	}

	TEST("Advanced")
	{
		// TODO : Test View
		class MyEntity : public oe::Entity
		{
		public:
			MyEntity(oe::World& world)
				: oe::Entity(world)
				, mParticle(this)
				, mView(this)
				, mAnimator(this)
			{
			}

			oe::ParticleComponent& getParticle()
			{
				return mParticle;
			}

			oe::ViewComponent& getView()
			{
				return mView;
			}

			oe::AnimatorComponent& getAnimator()
			{
				return mAnimator;
			}

		private:
			oe::ParticleComponent mParticle;
			oe::ViewComponent mView;
			oe::AnimatorComponent mAnimator;
		};

		class MyState : public oe::State
		{
		public:
			MyState(oe::Application& application)
				: oe::State(application)
				, mWorld(application)
			{
				mApplication.getWindow().setMainView(sf::View(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f)));
				mApplication.getWindow().applyMainView();

				mWorld.getRenderSystem().getView() = mApplication.getWindow().getMainView();

				oe::ResourceId pt = mWorld.getTextures().create("particle", "Assets/fx.png");

				oe::ResourceId an = mWorld.getTextures().create("soldier", "Assets/soldier.png");

				mIdleAnimation.addFrame(an, sf::IntRect(0, 0, 64, 64), oe::seconds(5.f));
				mAnimation.addFrame(an, sf::IntRect(0, 0, 64, 64), oe::seconds(0.2f));
				mAnimation.addFrame(an, sf::IntRect(64, 0, 64, 64), oe::seconds(0.2f));
				mAnimation.addFrame(an, sf::IntRect(128, 0, 64, 64), oe::seconds(0.2f));
				mAnimation.addFrame(an, sf::IntRect(192, 0, 64, 64), oe::seconds(0.2f));

				mEntity = mWorld.createEntity<MyEntity>();
				MyEntity* ent = mEntity.getAs<MyEntity>();
				ent->setPosition(400.f, 300.f, 0.f);
				oe::ParticleComponent& p = ent->getParticle();
				p.setTexture(pt);
				p.addTextureRect(0, 0, 6, 6);
				p.setParticleLifetime(oe::seconds(0.3f));
				p.setParticleColor(oe::Distributions::colorGrade(oe::Color::Cyan, 0.3f, 1.0f));
				p.setParticleVelocity(oe::Distributions::circle(oe::Vector2(), 300.0f));
				p.setParticleRotationSpeed(oe::Distributions::uniform(0.0f, 90.f));
				p.enableEmission();
				p.setEmissionRate(100.f);
				oe::AnimatorComponent& a = ent->getAnimator();
				a.play(&mIdleAnimation);
				a.setPosition(-32, -60);

				mTileset.setImageSource("Assets/hexapointy2.png");
				mTileset.setTileSize(oe::Vector2i(60, 80));
				mTileset.setTileCount(3);
				mTileset.setColumns(3);
				mMap = mWorld.createEntity<oe::Map>();
				oe::Map* map = mMap.getAs<oe::Map>();
				map->setPositionZ(-100.f);
				map->setTileset(&mTileset);
				map->setOrientation(oe::MapUtility::Hexagonal);
				map->setSize(oe::Vector2i(30, 30));
				map->setTileSize(oe::Vector2i(60, 52));
				map->setStaggerAxis(oe::MapUtility::Y);
				map->setStaggerIndex(oe::MapUtility::Odd);
				map->setHexSideLength(28);
				oe::LayerComponent& layer = map->addLayer();
				oe::Vector2i c;
				for (c.x = 0; c.x < 30; c.x++)
				{
					for (c.y = 0; c.y < 30; c.y++)
					{
						layer.setTileId(oe::Vector2i(c.x, c.y), 1);
					}
				}
			}

			std::string getName()
			{
				return "MyState";
			}

			bool handleEvent(const sf::Event& event)
			{
				return false;
			}

			bool update(oe::Time dt)
			{
				mWorld.update();
				mWorld.update(dt);
				mApplication.getWindow().setTitle("TestCore : " + oe::toString(mApplication.getFPSCount()));

				oe::Vector2 mvt;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					mvt.y--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					mvt.y++;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					mvt.x--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					mvt.x++;
				}
				mEntity.get()->move(mvt * dt.asSeconds() * 200.f);

				oe::AnimatorComponent& a = mEntity.getAs<MyEntity>()->getAnimator();
				if (mvt != oe::Vector2() && !a.isPlaying(&mAnimation))
				{
					a.play(&mAnimation);
				}
				else if (mvt == oe::Vector2() && !a.isPlaying(&mIdleAnimation))
				{
					a.play(&mIdleAnimation);
				}

				return false;
			}

			void render(sf::RenderTarget& target)
			{
				mWorld.render(target);
			}

		private:
			oe::World mWorld;
			oe::EntityHandle mMap;
			oe::EntityHandle mEntity;
			oe::Tileset mTileset;
			oe::Animation mAnimation;
			oe::Animation mIdleAnimation;
		};

		oe::Application app;
		app.pushState<MyState>();
		app.run();
	}
}
END_TEST;