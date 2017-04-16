#include "RenderSystem.hpp"
#include "../../System/Log.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace oe
{

RenderSystem::RenderSystem()
	: mTexture()
	, mRenderables()
	, mNeedUpdateOrderZ(true)
	, mNeedUpdateOrderY(true)
{
}

void RenderSystem::registerRenderable(RenderableComponent* renderable)
{
	ASSERT(renderable != nullptr);
	mRenderables.insert(renderable);

	// Reorder the sprite
	mNeedUpdateOrderZ = true;
	mNeedUpdateOrderY = true;
} 

void RenderSystem::unregisterRenderable(RenderableComponent* renderable)
{
	ASSERT(renderable != nullptr);
	mRenderables.remove(renderable);

	// Don't need to reorder here
}

void RenderSystem::registerParticle(ParticleComponent* particle)
{
	registerRenderable(particle);
	mParticles.insert(particle);
}

void RenderSystem::unregisterParticle(ParticleComponent* particle)
{
	mParticles.remove(particle);
	unregisterRenderable(particle);
}

void RenderSystem::registerAnimator(AnimatorComponent* animator)
{
	registerRenderable(animator);
	mAnimators.insert(animator);
}

void RenderSystem::unregisterAnimator(AnimatorComponent* animator)
{
	mAnimators.remove(animator);
	unregisterRenderable(animator);
}

void RenderSystem::update(Time dt)
{
	mDebugDraw.clear();
	for (auto& particle : mParticles)
	{
		particle->update(dt);
	}
	for (auto& animator : mAnimators)
	{
		animator->update(dt);
	}
}

void RenderSystem::render(sf::RenderTarget& target)
{
	preRender();
	render();
	postRender(target);
}

void RenderSystem::needUpdateOrderZ()
{
	mNeedUpdateOrderZ = true;
}

void RenderSystem::needUpdateOrderY()
{
	mNeedUpdateOrderY = true;
}

View& RenderSystem::getView()
{
	return mView;
}

void RenderSystem::preRender()
{
	// Reorder only on Z axis
	if (mNeedUpdateOrderZ)
	{
		std::sort(mRenderables.begin(), mRenderables.end(), RenderSystem::orderZ);
		mNeedUpdateOrderZ = false;

		// As we reordered Z we need to reorder Y
		mNeedUpdateOrderY = true;
	}

	// Reorder only on Y axis
	if (mNeedUpdateOrderY)
	{
		auto begin = mRenderables.begin();
		float currentZ = -99999.f;
		for (auto itr = mRenderables.begin(); itr != mRenderables.end(); ++itr)
		{
			RenderableComponent* r = (*itr);
			ASSERT(r != nullptr);
			F32 z = r->getGlobalZ();
			ASSERT(currentZ <= z);
			if (currentZ < z)
			{
				std::sort(begin, itr, RenderSystem::orderY);
				currentZ = z;
				begin = itr + 1;
			}
		}
		mNeedUpdateOrderY = false;
	}
}

void RenderSystem::render()
{
	mTexture.clear();
	mTexture.setView(mView.getHandle());
	for (RenderableComponent* renderable : mRenderables)
	{
		ASSERT(renderable != nullptr);
		if (renderable->isVisible())
		{
			renderable->render(mTexture);
		}
	}
	mDebugDraw.render(mTexture);
	mTexture.display();
}

void RenderSystem::postRender(sf::RenderTarget& target)
{
	// TODO : Add advanced graphics (Lights/Shaders)

	if (mTexture.getSize() == target.getSize())
	{
		target.draw(sf::Sprite(mTexture.getTexture()));
	}
	else
	{
		sf::Transform transform;
		transform.scale(target.getSize().x / ((F32)mTexture.getSize().x), target.getSize().y / ((F32)mTexture.getSize().y));
		target.draw(sf::Sprite(mTexture.getTexture()));
		if (!mTexture.create(target.getSize().x, target.getSize().y))
		{
			error("RenderSystem::postRender : Can't create sf::RenderTexture with size(" + toString(target.getSize().x) + ", " + toString(target.getSize().y) + ")");
		}
	}
}

bool RenderSystem::orderZ(RenderableComponent* a, RenderableComponent* b)
{
	ASSERT(a != nullptr);
	ASSERT(b != nullptr);
	return a->getGlobalZ() < b->getGlobalZ();
}

bool RenderSystem::orderY(RenderableComponent* a, RenderableComponent* b)
{
	ASSERT(a != nullptr);
	ASSERT(b != nullptr);
	return a->getGlobalPosition().y < b->getGlobalPosition().y;
}

} // namespace oe