#ifndef OE_SPHERE_HPP
#define OE_SPHERE_HPP

#include "Vector3.hpp"

namespace oe 
{

class Plane;
class AABB;

class Sphere
{
	public:
		Sphere();
		Sphere(const Vector3& center, F32 radius = 1.f);
		Sphere(F32 radius, const Vector3& center = Vector3::zero());
		
		const Vector3& getCenter() const;
		void setCenter(const Vector3& center);

		F32 getRadius() const;
		void setRadius(F32 radius);

		AABB getAABB() const;

		bool intersects(const Vector3& point) const;
		bool intersects(const Sphere& sphere) const;
		bool intersects(const Plane& plane) const;
		bool intersects(const AABB& box) const;

		bool operator==(const Sphere& p) const;
		bool operator!=(const Sphere& p) const;
		
	private:
		Vector3 mCenter;
		F32 mRadius;
};

} // namespace oe

#endif // OE_SPHERE_HPP
