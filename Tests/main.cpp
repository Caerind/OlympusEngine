#include "../Sources/Application/Application.hpp"
#include "../Sources/Core/World.hpp"
#include "../Sources/Core/Components/SpriteComponent.hpp"
#include "../Sources/Core/Components/LayerComponent.hpp"

class MyEntity : public oe::Entity
{
	public: 
		TYPE(MyEntity);

		MyEntity(oe::EntityManager& manager)
			: oe::Entity(manager)
			, mComponent(*this)
			, mLayerComponent(*this, true)
		{
			mComponent.setPosition(100, 0);
			mComponent.setPositionZ(100);

			mLayerComponent.setPosition(0, 0);
			mLayerComponent.setPositionZ(-100);
		}

		void setTexture(sf::Texture& texture)
		{
			mComponent.setTexture(texture);
		}

		void setTileset(oe::Tileset& tileset)
		{
			mLayerComponent.create(&tileset, { 30,30 }, { 16,16 });
			mLayerComponent.loadFromCode("eJyNlkFuhTAMRHOpJivKimT/73+Ygoql0ftjQyWrkO947MnYobfWxmn7aT/t/2/I2ue0ldhx2sTaFaPL/nX/j5ixZ8C33X6x53P/7qxLPMaJ/WFRV+B2g6vvF+4mRrxdYhJzgpMMN+PZ1UPT3+IM1IKjwGUs5TnqdfXQXC7Ma0O9jKVn8nRu6luZ1roknsbW31mrrjFWZfQdJjZ9nJ5Ua9RO7M80tZrnscNHdaGcuNiaI3N1PFY+7CPHjVundngm3EMf5Y34GR41sQym83P1Hgk+ZwBzmQkuayXPTrtHgkUN7i9xnfayGRnv1Lbj+OlsHa6byZm2s1odLmcRa3PPTltvanXzWf2c3ljj1uoeczPI4Tpes+fszmHPcp4Rt8KqeiObPU4Xrkc0T+XMcenuD5fX0yxyc8/NCjcPNX6lR+orm3GcS1XN8X60eoY63Eq3lX6oAebq8JfBdPc8e6v61iIfjiOHm82b7E5131nZOQzBdbVWxv7kt4zzZZ7UuuubDetVTtXs0jxn++7VTEeVvp/uZ/I8W96r2beVy4t7lsH/lZon8PS+1bU3HGfmcrqe/wC1L9MJ");
		}

	private:
		oe::SpriteComponent mComponent;
		oe::LayerComponent mLayerComponent;
};

class MyState : public oe::State
{
	public:
		MyState(oe::StateManager& manager)
			: oe::State(manager)
			, mWorld(getApplication())
		{
			// ImGui Windows;
			mLogger.show();
			mConsole.show();
			mProfiler.show();
			mData.show();

			// Logger test
			oe::error("test1");
			oe::log("test3");
			oe::warning("test4");
			oe::info("test5");

			// Loading
			mTileset.setTileSize({ 16,16 });
			mTileset.setTileCount(104);
			mTileset.setColumns(8);
			mTileset.setImageSource("Assets/orthogonal.png");
			mTexture.loadFromFile("Assets/hero.png");

			// Entity
			mHandle = mWorld.getEntityManager().createEntity<MyEntity>();
			MyEntity* entity = mHandle.getAs<MyEntity>();
			if (entity != nullptr)
			{
				entity->setTexture(mTexture);
				entity->setTileset(mTileset);
				entity->setPosition(0, 0);
				entity->setName("test");
			}

			// Inputs
			mKeyZ.setKey(sf::Keyboard::Z);
			mKeyZ.setType(oe::ActionType::Hold);
			mKeyQ.setKey(sf::Keyboard::Q);
			mKeyQ.setType(oe::ActionType::Hold);
			mKeyS.setKey(sf::Keyboard::S);
			mKeyS.setType(oe::ActionType::Hold);
			mKeyD.setKey(sf::Keyboard::D);
			mKeyD.setType(oe::ActionType::Hold);
			mKeyE.setKey(sf::Keyboard::E);
			mKeyE.setType(oe::ActionType::Pressed);

			// Actions def
			oe::ActionSystem& as = mWorld.getActionSystem();
			oe::ActionId up = as.addAction("up");
			oe::ActionId down = as.addAction("down");
			oe::ActionId left = as.addAction("left");
			oe::ActionId right = as.addAction("right");
			oe::ActionId action = as.addAction("action");

			// Actions connections
			as.setInput(up, &mKeyZ);
			as.setInput(down, &mKeyS);
			as.setInput(left, &mKeyQ);
			as.setInput(right, &mKeyD);
			as.setInput(action, &mKeyE);

			// Actions outputs
			as.addOutput(up, [this]() { mHandle->move(0.0f, -1.0f); });
			as.addOutput(down, [this]() { mHandle->move(0.0f, 1.0f); });
			as.addOutput(left, [this]() { mHandle->move(-1.0f, 0.0f); });
			as.addOutput(right, [this]() { mHandle->move(1.0f, 0.0f); });
			as.addOutput(action, [this]() { oe::info("Action!"); });

			// World
			mWorld.getRenderSystem().setView(oe::View(0, 0, 800, 600));
			mWorld.play();
		}

		bool handleEvent(const sf::Event& event)
		{
			OE_PROFILE_FUNCTION("MyState::handleEvent");

			mWorld.handleEvent(event);

			return false;
		}

		bool update(oe::Time dt) 
		{
			OE_PROFILE_FUNCTION("MyState::update");

			mWorld.update(dt);

			#ifdef OE_IMGUI
			mLogger.draw();
			mConsole.draw();
			mProfiler.draw();
			mData.draw();
			#endif

			return true; 
		}

		void render(sf::RenderTarget& target)
		{
			OE_PROFILE_FUNCTION("MyState::render");

			mWorld.render(target);
		}

	private:
		oe::World mWorld;
		oe::EntityHandle mHandle;
		oe::ImGuiLogger mLogger;
		oe::ImGuiConsole mConsole;
		oe::ImGuiProfiler mProfiler;
		oe::ImGuiDataViewer mData;
		sf::Texture mTexture;
		oe::Tileset mTileset;

		oe::ActionInputKey mKeyZ;
		oe::ActionInputKey mKeyQ;
		oe::ActionInputKey mKeyS;
		oe::ActionInputKey mKeyD;
		oe::ActionInputKey mKeyE;

		bool mVariable;
};

int main()
{
	oe::Application app;

	app.start<MyState>();

	getchar();
	return 0;
}
