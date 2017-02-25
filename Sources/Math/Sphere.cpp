#include "Sphere.hpp"

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

} // namespace oe
