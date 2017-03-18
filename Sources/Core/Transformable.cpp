#include "Transformable.hpp"

namespace oe
{

Transformable::Transformable()
{
}

Vector2 Transformable::getPosition() const
{
	return oe::SFML::toOE(mTransformable.getPosition());
}

void Transformable::setPosition(const Vector2& position)
{
	mTransformable.setPosition(position.x(), position.y());
}

void Transformable::setPosition(F32 x, F32 y)
{
	mTransformable.setPosition(x, y);
}

void Transformable::move(const Vector2& offset)
{
	mTransformable.move(offset.x(), offset.y());
}

void Transformable::move(F32 offsetX, F32 offsetY)
{
	mTransformable.move(offsetX, offsetY);
}

Vector2 Transformable::getScale() const
{
	return oe::SFML::toOE(mTransformable.getScale());
}

void Transformable::setScale(const Vector2& scale)
{
	mTransformable.setScale(scale.x(), scale.y());
}

void Transformable::setScale(F32 x, F32 y)
{
	mTransformable.setScale(x, y);
}

void Transformable::scale(const Vector2& factor)
{
	mTransformable.scale(factor.x(), factor.y());
}

void Transformable::scale(F32 factorX, F32 factorY)
{
	mTransformable.scale(factorX, factorY);
}

void Transformable::scale(F32 factor)
{
	mTransformable.scale(factor, factor);
}

F32 Transformable::getRotation() const
{
	return mTransformable.getRotation();
}

void Transformable::setRotation(F32 rotation)
{
	mTransformable.setRotation(rotation);
}

void Transformable::rotate(F32 rotation)
{
	mTransformable.rotate(rotation);
}

const sf::Transform& Transformable::getTransform() const
{
	return mTransformable.getTransform();
}

const sf::Transform& Transformable::getInverseTransform() const
{
	return mTransformable.getInverseTransform();
}

Matrix4 Transformable::getMatrix() const
{
	// TODO : Update Matrix and Transform at the same time, and use const&
	return oe::SFML::toOE(getTransform());
}

Matrix4 Transformable::getInverseMatrix() const
{
	// TODO : Update Matrix and Transform at the same time, and use const&
	return oe::SFML::toOE(getInverseTransform());
}

} // namespace oe