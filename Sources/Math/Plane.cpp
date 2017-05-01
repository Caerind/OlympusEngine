#include "Plane.hpp"
#include "Sphere.hpp"
#include "AABB.hpp"

namespace oe
{

Plane::Plane()
	: mNormal(0.0f)
	, mConstant(0.0f)
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
	mNormal.set(normal);
	mConstant = -mNormal.dotProduct(point);
}

void Plane::redefine(const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
	Vector3 edge1 = point2 - point1;
	Vector3 edge2 = point3 - point1;
	mNormal.set(edge1.crossProduct(edge2).getNormal());
	mConstant = -mNormal.dotProduct(point1);
}

const Vector3& Plane::getNormal() const
{
	return mNormal;
}

void Plane::setNormal(const Vector3& normal)
{
	mNormal.set(normal);
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
	return mNormal.dotProduct(point) + mConstant;
}

Vector3 Plane::projectVector(const Vector3& vector) const
{
	// TODO : Plane::projectVector : Use Quaternion
	//F32 x = mNormal.x;
	//F32 y = mNormal.y;
	//F32 z = mNormal.z;
	//Matrix3 m(1.f - x * x, -x * y, -x * z, -y * x, 1.f - y * y, -y * z, -z * x, -z * y, 1.f - z * z);
	//return m * vector;
	return Vector3();
}

Plane::Side Plane::getSide(const Vector3& point) const
{
	F32 distance = getDistance(point);
	if (distance > 0.0f)
	{
		return Plane::Positive;
	}
	if (distance < 0.0f)
	{
		return Plane::Negative;
	}
	return Plane::None;
}

Plane::Side Plane::getSide(const Sphere& sphere) const
{
	F32 distance = getDistance(sphere.getCenter());
	if (sphere.getRadius() > Math::abs(distance))
	{
		return Plane::Both;
	}
	if (distance > 0.0f)
	{
		return Plane::Positive;
	}
	if (distance < 0.0f)
	{
		return Plane::Negative;
	}
	return Plane::None;
}

Plane::Side Plane::getSide(const AABB& box) const
{
	F32 dist = getDistance(box.getCenter());
	F32 maxAbsDist = Math::abs(mNormal.dotProduct(box.getHalfSize()));
	if (dist < -maxAbsDist)
		return Plane::Negative;
	if (dist > +maxAbsDist)
		return Plane::Positive;
	return Plane::Both;
}

bool Plane::intersects(const Vector3& point) const
{
	return Math::equals(getDistance(point), 0.0f);
}

bool Plane::intersects(const Plane& plane) const
{
	return operator!=(plane);
}

bool Plane::intersects(const Sphere& sphere) const
{
	return fabs(getDistance(sphere.getCenter())) <= sphere.getRadius();
}

bool Plane::intersects(const AABB& box) const
{
	return getSide(box) == Plane::Both;
}

Plane Plane::operator-() const
{
	return Plane(-(mNormal.x), -(mNormal.y), -(mNormal.z), -mConstant); // not equal to Plane(-normal, -d)
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
