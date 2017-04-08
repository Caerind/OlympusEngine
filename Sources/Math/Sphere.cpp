#include "Sphere.hpp"
#include "Plane.hpp"
#include "AABB.hpp"

namespace oe
{

Sphere::Sphere()
	: mCenter()
	, mRadius(1.0f)
{
}

Sphere::Sphere(const Vector3& center, F32 radius)
	: mCenter(center)
	, mRadius(radius)
{
}

Sphere::Sphere(F32 radius, const Vector3& center)
	: mCenter(center)
	, mRadius(radius)
{
}

const Vector3& Sphere::getCenter() const
{
	return mCenter;
}

void Sphere::setCenter(const Vector3& center)
{
	mCenter.set(center);
}

F32 Sphere::getRadius() const
{
	return mRadius;
}

void Sphere::setRadius(F32 radius)
{
	mRadius = radius;
}

AABB Sphere::getAABB() const
{
	const Vector3 radius(mRadius);
	return AABB(mCenter - radius, mCenter + radius);
}

bool Sphere::intersects(const Vector3& point) const
{
	return (point - mCenter).getSquaredLength() <= mRadius * mRadius;
}

bool Sphere::intersects(const Sphere& sphere) const
{
	return (sphere.mCenter - mCenter).getSquaredLength() <= (sphere.mRadius + mRadius) * (sphere.mRadius + mRadius);
}

bool Sphere::intersects(const Plane& plane) const
{
	return plane.intersects(*this);
}

bool Sphere::intersects(const AABB& box) const
{
	// Use splitting planes
	const Vector3& min(box.getMinimum());
	const Vector3& max(box.getMaximum());
	// Arvo's algorithm
	F32 s;
	F32 d = 0.f;
	for (U8 i = 0; i < 3; ++i)
	{
		if (mCenter[i] < min[i])
		{
			s = mCenter[i] - min[i];
			d += s * s;
		}
		else if (mCenter[i] > max[i])
		{
			s = mCenter[i] - max[i];
			d += s * s;
		}
	}
	return d <= mRadius * mRadius;
}

bool Sphere::operator==(const Sphere& p) const
{
	return mCenter == p.mCenter && Math::equals(mRadius, p.mRadius);
}

bool Sphere::operator!=(const Sphere& p) const
{
	return !operator==(p);
}

} // namespace oe
