#ifndef OE_TRANSFORMABLE_HPP
#define OE_TRANSFORMABLE_HPP

#include "../Math/Vector2.hpp"
#include "../Math/Matrix4.hpp"

#include "../System/SFML.hpp"

#include <SFML/Graphics/Transformable.hpp>


namespace oe
{

class Transformable
{
	public:
		Transformable();
		
		Vector2 getPosition() const;
		void setPosition(const Vector2& position);
		void setPosition(F32 x, F32 y);
		void move(const Vector2& offset);
		void move(F32 offsetX, F32 offsetY);
		
		Vector2 getScale() const;
		void setScale(const Vector2& scale);
		void setScale(F32 x, F32 y);
		void scale(const Vector2& factor);
		void scale(F32 factorX, F32 factorY);
		void scale(F32 factor);
		
		F32 getRotation() const;
		void setRotation(F32 rotation);
		void rotate(F32 rotation);

		const sf::Transform& getTransform() const;
		const sf::Transform& getInverseTransform() const;

		Matrix4 getMatrix() const;
		Matrix4 getInverseMatrix() const;
		
	private:
		sf::Transformable mTransformable;
};

} // namespace oe

#endif // OE_TRANSFORMABLE_HPP
