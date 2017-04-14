#ifndef OE_RENDERSYSTEM_HPP
#define OE_RENDERSYSTEM_HPP

#include "../RenderableComponent.hpp"
#include "../Components/ParticleComponent.hpp"
#include "../Components/AnimatorComponent.hpp"
#include "../ComponentList.hpp"

#include "../../System/DebugDraw.hpp"
#include "../../System/View.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace oe
{

class RenderSystem
{
	public:
		RenderSystem();

		void registerRenderable(RenderableComponent* renderable);
		void unregisterRenderable(RenderableComponent* renderable);

		void registerParticle(ParticleComponent* particle);
		void unregisterParticle(ParticleComponent* particle);

		void registerAnimator(AnimatorComponent* animator);
		void unregisterAnimator(AnimatorComponent* animator);

		void update(Time dt);
		void render(sf::RenderTarget& target);

		void needUpdateOrderZ();
		void needUpdateOrderY();

		View& getView();

	private:
		void preRender();
		void render();
		void postRender(sf::RenderTarget& target);

		static bool orderZ(RenderableComponent* a, RenderableComponent* b);
		static bool orderY(RenderableComponent* a, RenderableComponent* b);

	private:
		sf::RenderTexture mTexture;

		RenderableComponentList mRenderables;
		ParticleComponentList mParticles;
		AnimatorComponentList mAnimators;

		DebugDraw mDebugDraw;

		View mView;

		bool mNeedUpdateOrderZ;
		bool mNeedUpdateOrderY;
};

} // namespace oe

#endif // OE_RENDERSYSTEM_HPP
