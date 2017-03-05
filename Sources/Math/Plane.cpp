#include "Plane.hpp"
#include "Sphere.hpp"

#include "Matrix3.hpp"

namespace oe
{

Plane::Plane()
	: mNormal(0.f)
	, mConstant(0.f)
{
}

Plane::Plane(const Vector3& normal, F32 constant)
	: mNormal(normal)
	, mConstant(-constant)
{
}

Plane::Plane(const Vector3& normal, const Vector3& point)
{
	redefine(normal, point);
}

Plane::Plane(F32 a, F32 b, F32 c, F32 d)
	: mNormal(a, b, c)
	, mConstant(d)
{
}

Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
	redefine(point1, point2, point3);
}

void Plane::redefine(const Vector3& normal, const Vector3& point)
{
	mNormal = normal;
	mConstant = -Vector3::dotProduct(normal, point);
}

void Plane::redefine(const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
	Vector3 edge1 = point2 - point1;
	Vector3 edge2 = point3 - point1;
	mNormal = Vector3::crossProduct(edge1, edge2).normalized();
	mConstant = -Vector3::dotProduct(mNormal, point1);
}

const Vector3& Plane::getNormal() const
{
	return mNormal;
}

void Plane::setNormal(const Vector3& normal)
{
	mNormal = normal;
}

F32 Plane::getConstant() const
{
	return mConstant;
}

void Plane::setConstant(F32 constant)
{
	mConstant = constant;
}

F32 Plane::normalize()
{
	F32 length = mNormal.getLength();
	ASSERT(length > 0.f);
	F32 inv = 1.0f / length;
	mNormal *= inv;
	mConstant *= inv;
	return length;
}

F32 Plane::getDistance(const Vector3& point) const
{
	return Vector3::dotProduct(mNormal, point) + mConstant;
}

Vector3 Plane::projectVector(const Vector3& vector) const
{
	Matrix3 xform;
	xform(0, 0) = 1.f - mNormal.x() * mNormal.x();
	xform(0, 1) = -mNormal.x() * mNormal.y();
	xform(0, 2) = -mNormal.x() * mNormal.z();
	xform(1, 0) = -mNormal.y() * mNormal.x();
	xform(1, 1) = 1.f - mNormal.y() * mNormal.y();
	xform(1, 2) = -mNormal.y() * mNormal.z();
	xform(2, 0) = -mNormal.z() * mNormal.x();
	xform(2, 1) = -mNormal.z() * mNormal.y();
	xform(2, 2) = 1.f - mNormal.z() * mNormal.z();
	return xform * vector;
}

Plane::Side Plane::getSide(const Vector3& point) const
{
	F32 distance = getDistance(point);
	if (distance > 0.f)
	{
		return Plane::Positive;
	}
	if (distance < 0.f)
	{
		return Plane::Negative;
	}
	return Plane::None;
}

Plane::Side Plane::getSide(const Sphere& sphere) const
{
	F32 distance = getDistance(sphere.getCenter());
	if (sphere.getRadius() > fabs(distance))
	{
		return Plane::Both;
	}
	if (distance > 0.f)
	{
		return Plane::Positive;
	}
	if (distance < 0.f)
	{
		return Plane::Negative;
	}
	return Plane::None;
}

bool Plane::intersects(const Vector3& point) const
{
	return Math::equals(getDistance(point), 0.f);
}

bool Plane::intersects(const Plane& plane) const
{
	return operator==(plane);
}

bool Plane::intersects(const Sphere& sphere) const
{
	return Math::equals(getDistance(sphere.getCenter()), sphere.getRadius());
}

Plane Plane::operator-() const
{
	return Plane(-(mNormal.x()), -(mNormal.y()), -(mNormal.z()), -mConstant); // not equal to Plane(-normal, -d)
}

bool Plane::operator==(const Plane& p) const
{
	return mNormal == p.mNormal && Math::equals(mConstant, p.mConstant);
}

bool Plane::operator!=(const Plane& p) const
{
	return !operator==(p);
}

} // namespace oe
