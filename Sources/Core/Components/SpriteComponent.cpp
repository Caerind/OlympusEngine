#include "SpriteComponent.hpp"
#include "../World.hpp"

namespace oe
{

SpriteComponent::SpriteComponent(Entity& entity)
	: RenderableComponent(entity)
	, mSprite()
{
}

void SpriteComponent::setTexture(ResourceId texture)
{
	mSprite.setTexture(getWorld().getTextures().get(texture));
	mLocalAABB = mSprite.getLocalBounds();
}

void SpriteComponent::setTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
	mLocalAABB = mSprite.getLocalBounds();
}

const sf::Texture* SpriteComponent::getTexture() const
{
	return mSprite.getTexture();
}

void SpriteComponent::setTextureRect(const sf::IntRect& textureRect)
{
	mSprite.setTextureRect(textureRect);
	mLocalAABB = mSprite.getLocalBounds();
}

const sf::IntRect& SpriteComponent::getTextureRect() const
{
	return mSprite.getTextureRect();
}

void SpriteComponent::setColor(const Color& color)
{
	mSprite.setColor(toSF(color));
}

Color SpriteComponent::getColor() const
{
	return toOE(mSprite.getColor());
}

void SpriteComponent::render(sf::RenderTarget& target)
{
	target.draw(mSprite, getGlobalTransform());
}

} // namespace oe