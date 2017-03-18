#include "RenderSystem.hpp"

namespace oe
{

RenderSystem::RenderSystem()
	: mTexture()
	, mSprites()
{
}

void RenderSystem::registerSprite(SpriteComponent* sprite)
{
	ASSERT(sprite != nullptr);
	mSprites.emplace_back(sprite);
} 

void RenderSystem::unregisterSprite(SpriteComponent* sprite)
{
	ASSERT(sprite != nullptr);
	for (auto itr = mSprites.begin(); itr != mSprites.end(); ++itr)
	{
		if (*itr == sprite)
		{
			mSprites.erase(itr);
			return;
		}
	}
}

void RenderSystem::preRender()
{

	// TODO : Reorder sprites

	bool needReordering = false;
	for (SpriteComponent* component : mSprites)
	{
		ASSERT(component != nullptr);
		/*
		if (component->needUpdate())
		{
			if (component->hasTransformChanged())
			{
				needReordering = true;
			}
			ASSERT(component->getSpriteIndex() < mMaxSprites);
			ASSERT(mSprites[component->getSpriteIndex()] != nullptr);
			mSprites[component->getSpriteIndex()]->update(component);
		}
		*/
	}
	if (needReordering)
	{
	}
}

void RenderSystem::render()
{
	mTexture.clear();
	for (SpriteComponent* sprite : mSprites)
	{
		ASSERT(sprite != nullptr);
		sprite->render(mTexture);
	}
	mTexture.display();
}

void RenderSystem::postRender(sf::RenderTarget& target)
{
	// TODO : Particles

	// TODO : Lights

	// TODO : Shaders

	if (mTexture.getSize() == target.getSize())
	{
		target.draw(sf::Sprite(mTexture.getTexture()));
	}
	else
	{
		sf::Sprite sprite(mTexture.getTexture());
		sprite.setScale(target.getSize().x / ((F32)mTexture.getSize().x), target.getSize().y / ((F32)mTexture.getSize().y));
		target.draw(sprite);
		if (!mTexture.create(target.getSize().x, target.getSize().y))
		{
			// TODO : Error handling
			printf("RenderSystem::postRender : Can't create sf::RenderTexture with size(%d, %d)", target.getSize().x, target.getSize().y);
		}
	}
}

} // namespace oe