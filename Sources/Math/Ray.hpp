#ifndef OE_RAY_HPP
#define OE_RAY_HPP

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "AABB.hpp"

namespace oe 
{

class Ray
{
	public:
		Ray();
		Ray(const Vector3& origin, const Vector3& direction);

		void setOrigin(const Vector3& origin);
		void setOrigin(F32 x, F32 y, F32 z);
		const Vector3& getOrigin() const;

		void setDirection(const Vector3& direction);
		void setDirection(F32 x, F32 y, F32 z);
		const Vector3& getDirection() const;

		Vector3 getPoint(F32 t) const;
		Vector3 operator*(F32 t) const;

		std::pair<bool, F32> intersects(const Sphere& sphere) const;
		std::pair<bool, F32> intersects(const Plane& plane) const;
		std::pair<bool, F32> intersects(const AABB& box) const;

		bool operator==(const Ray& ray) const;
		bool operator!=(const Ray& ray) const;

	private:
		Vector3 mOrigin;
		Vector3 mDirection;
};

} // namespace oe

#endif // OE_RAY_HPP
