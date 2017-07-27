#include "TextComponent.hpp"
#include "../World.hpp"

namespace oe
{

TextComponent::TextComponent(Entity& entity, bool attachedToEntity)
	: RenderableComponent(entity, attachedToEntity)
	, mText()
	, mString("")
{
}

void TextComponent::setFont(ResourceId font)
{
	setFont(getWorld().getFonts().get(font));
}

void TextComponent::setFont(sf::Font& font)
{
	mText.setFont(font);
	setLocalAABB(toOE(mText.getLocalBounds()));
}

const sf::Font* TextComponent::getFont() const
{
	return mText.getFont();
}

void TextComponent::setString(const std::string& string)
{
	mString = string;
	mText.setString(string);
	setLocalAABB(toOE(mText.getLocalBounds()));
}

const std::string& TextComponent::getString() const
{
	return mString;
}

void TextComponent::setFillColor(const oe::Color& color)
{
	mText.setFillColor(toSF(color));
}

void TextComponent::setFillColor(const sf::Color& color)
{
	mText.setFillColor(color);
}

const sf::Color& TextComponent::getFillColor() const
{
	return mText.getFillColor();
}

void TextComponent::setOutlineColor(const oe::Color& color)
{
	mText.setOutlineColor(toSF(color));
}

void TextComponent::setOutlineColor(const sf::Color& color)
{
	mText.setOutlineColor(color);
}

const sf::Color& TextComponent::getOutlineColor() const
{
	return mText.getOutlineColor();
}

void TextComponent::setOutlineThickness(F32 thickness)
{
	mText.setOutlineThickness(thickness);
	setLocalAABB(toOE(mText.getLocalBounds()));
}

F32 TextComponent::getOutlineThickness() const
{
	return mText.getOutlineThickness();
}

void TextComponent::setCharacterSize(U32 size)
{
	mText.setCharacterSize(size);
	setLocalAABB(toOE(mText.getLocalBounds()));
}

U32 TextComponent::getCharacterSize() const
{
	return mText.getCharacterSize();
}

void TextComponent::render(sf::RenderTarget& target)
{
	target.draw(mText, getGlobalTransform());
}

} // namespace oe