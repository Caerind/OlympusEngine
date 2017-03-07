#ifndef OE_PLANE_HPP
#define OE_PLANE_HPP

#include "Vector3.hpp"

namespace oe 
{

class Sphere;
class AABB;

class Plane
{
	public:
		Plane();
		Plane(const Vector3& normal, F32 constant);
		Plane(const Vector3& normal, const Vector3& point);
		Plane(F32 a, F32 b, F32 c, F32 d);
		Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3);

		void redefine(const Vector3& normal, const Vector3& point);
		void redefine(const Vector3& point1, const Vector3& point2, const Vector3& point3);

		const Vector3& getNormal() const;
		void setNormal(const Vector3& normal);

		F32 getConstant() const;
		void setConstant(F32 constant);

		F32 normalize();

		F32 getDistance(const Vector3& point) const;

		Vector3 projectVector(const Vector3& vector) const;

		enum Side : U8
		{
			None,
			Positive,
			Negative,
			Both
		};
		Side getSide(const Vector3& point) const;
		Side getSide(const Sphere& sphere) const;
		Side getSide(const AABB& box) const;

		bool intersects(const Vector3& point) const;
		bool intersects(const Plane& plane) const;
		bool intersects(const Sphere& sphere) const;
		bool intersects(const AABB& box) const;

		Plane operator-() const;
		bool operator==(const Plane& p) const;
		bool operator!=(const Plane& p) const;

	private:
		Vector3 mNormal;
		F32 mConstant;
};

} // namespace oe

#endif // OE_PLANE_HPP
