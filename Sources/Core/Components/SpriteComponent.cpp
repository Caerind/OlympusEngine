#include "SpriteComponent.hpp"
#include "../World.hpp"

namespace oe
{

SpriteComponent::SpriteComponent()
	: mSprite()
	, mVisible(true)
{
}

void SpriteComponent::setTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

const sf::Texture* SpriteComponent::getTexture() const
{
	return mSprite.getTexture();
}

void SpriteComponent::setTextureRect(const sf::IntRect& textureRect)
{
	mSprite.setTextureRect(textureRect);
}

const sf::IntRect& SpriteComponent::getTextureRect() const
{
	return mSprite.getTextureRect();
}

void SpriteComponent::setColor(const Color& color)
{
	mSprite.setColor(oe::SFML::toSF(color));
}

const Color& SpriteComponent::getColor() const
{
	return oe::SFML::toOE(mSprite.getColor());
}

void SpriteComponent::setVisible(bool visible)
{
	mVisible = visible;
}

bool SpriteComponent::isVisible() const
{
	return mVisible;
}

void SpriteComponent::render(sf::RenderTarget& target) const
{
	if (mVisible)
	{
		target.draw(mSprite, getGlobalTransform()); // TODO : Do not recalculate global transform if not needed
	}
}

void SpriteComponent::onAttach()
{
	ASSERT(hasParent());
	mParent->getWorld().getRenderSystem().registerSprite(this);
}

void SpriteComponent::onDetach()
{
	ASSERT(hasParent());
	mParent->getWorld().getRenderSystem().unregisterSprite(this);
}

} // namespace oe