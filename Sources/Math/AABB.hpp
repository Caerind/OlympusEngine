#ifndef OE_AABB_HPP
#define OE_AABB_HPP

#include "Vector3.hpp"
#include "Matrix4.hpp"

namespace oe 
{

class Sphere;
class Plane;

class AABB
{
	public:
		AABB();
		AABB(const Vector3& min, const Vector3& max);
		AABB(F32 minX, F32 minY, F32 minZ, F32 maxX, F32 maxY, F32 maxZ);

		const Vector3& getMinimum() const;
		void setMinimum(const Vector3& minimum);
		void setMinimum(F32 x, F32 y, F32 z);

		const Vector3& getMaximum() const;
		void setMaximum(const Vector3& maximum);
		void setMaximum(F32 x, F32 y, F32 z);

		void setBox(const Vector3& minimum, const Vector3& maximum);
		void setBox(F32 minX, F32 minY, F32 minZ, F32 maxX, F32 maxY, F32 maxZ);
		void setCenteredBox(const Vector3& center, const Vector3& halfSize);
		void setCenteredBox(F32 cX, F32 cY, F32 cZ, F32 hsX, F32 hsY, F32 hsZ);

		void merge(const Vector3& point);
		void merge(const AABB& box);

		void transform(const Matrix4& m);

		Vector3 getCenter() const;
		Vector3 getSize() const;
		Vector3 getHalfSize() const;
		F32 getVolume() const;

		/*
		   1-------2
		  /|      /|
		 / |     / |
		5-------4  |
		|  0----|--3
		| /     | /
		|/      |/
		6-------7
		*/
		Vector3 getCorner(U8 index) const;

		F32 getDistanceSquared(const Vector3& point) const;
		F32 getDistance(const Vector3& point) const;

		bool intersects(const Vector3& point) const;
		bool intersects(const AABB& box) const;
		bool intersects(const Plane& plane) const;
		bool intersects(const Sphere& sphere) const;

		AABB intersection(const AABB&& box) const;

		bool contains(const AABB& box) const;

		bool operator==(const AABB& box) const;
		bool operator!=(const AABB& box) const;

	private:
		Vector3 mMin;
		Vector3 mMax;
};

} // namespace oe

#endif // OE_AABB_HPP
