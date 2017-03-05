#include "Sphere.hpp"
#include "Plane.hpp"

namespace oe
{

Sphere::Sphere()
	: mCenter()
	, mRadius(1.f)
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
	mCenter = center;
}

F32 Sphere::getRadius() const
{
	return mRadius;
}

void Sphere::setRadius(F32 radius)
{
	mRadius = radius;
}

bool Sphere::intersects(const Vector3& point) const
{
	return (point - mCenter).getLengthSquared() <= mRadius * mRadius;
}

bool Sphere::intersects(const Sphere& sphere) const
{
	return (sphere.mCenter - mCenter).getLengthSquared() <= (sphere.mRadius + mRadius) * (sphere.mRadius + mRadius);
}

bool Sphere::intersects(const Plane& plane) const
{
	return plane.intersects(*this);
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
