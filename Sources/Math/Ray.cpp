#include "Ray.hpp"

namespace oe
{

Ray::Ray()
	: mOrigin(Vector3::zero())
	, mDirection(Vector3::zero())
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction)
	: mOrigin(origin)
	, mDirection(direction)
{
}

void Ray::setOrigin(const Vector3& origin)
{
	mOrigin = origin;
}

void Ray::setOrigin(F32 x, F32 y, F32 z)
{
	setOrigin(Vector3(x, y, z));
}

const Vector3& Ray::getOrigin() const
{
	return mOrigin;
}

void Ray::setDirection(const Vector3& direction)
{
	mDirection = direction;
}

void Ray::setDirection(F32 x, F32 y, F32 z)
{
	setDirection(Vector3(x, y, z));
}

const Vector3& Ray::getDirection() const
{
	return mDirection;
}

Vector3 Ray::getPoint(F32 t) const
{
	return mOrigin + mDirection * t;
}

Vector3 Ray::operator*(F32 t) const
{
	return mOrigin + mDirection * t;
}

std::pair<bool, F32> Ray::intersects(const Sphere& sphere) const
{
	// Adjust ray origin relative to sphere center
	const Vector3& diff = mOrigin - sphere.getCenter();
	F32 radius = sphere.getRadius();

	// Check origin inside first
	if (diff.getSquaredLength() <= radius * radius)
	{
		return std::pair<bool, F32>(true, 0.f);
	}

	// Build coeffs which can be used with std quadratic solver
	// ie t = (-b +/- sqrt(b*b + 4ac)) / 2a
	const F32 a = Vector3::dotProduct(mDirection, mDirection);
	const F32 b = 2 * Vector3::dotProduct(diff, mDirection);
	const F32 c = Vector3::dotProduct(diff, diff) - (radius * radius);
	const F32 d = (b * b) - (4.f * a * c); // Calc determinant
	if (d < 0.f)
	{
		return std::pair<bool, F32>(false, 0.f); // No intersection
	}
	else
	{
		F32 t = (-b - Math::sqrt(d)) / (2.f * a);
		if (t < 0.f)
		{
			t = (-b + Math::sqrt(d)) / (2.f * a);
		}
		return std::pair<bool, F32>(true, t);
	}
}

std::pair<bool, F32> Ray::intersects(const Plane& plane) const
{
	F32 denom = Vector3::dotProduct(plane.getNormal(), mDirection);
	if (fabs(denom) < 1e-7f)
	{
		return std::pair<bool, F32>(false, 0.f); // Parallel
	}
	else
	{
		F32 nom = Vector3::dotProduct(plane.getNormal(), mOrigin) + plane.getConstant();
		F32 t = -(nom / denom);
		return std::pair<bool, F32>(t >= 0.f, t);
	}
}

std::pair<bool, F32> Ray::intersects(const AABB& box) const
{
	F32 lowt = 0.f;
	F32 t;
	bool hit = false;
	Vector3 hitpoint;
	const Vector3& min = box.getMinimum();
	const Vector3& max = box.getMaximum();

	// Check origin inside first
	if (box.intersects(mOrigin))
	{
		return std::pair<bool, F32>(true, 0.0f);
	}

	// Check each face in turn, only check closest 3
	// Min x
	if (mOrigin.x <= min.x && mDirection.x > 0.0f)
	{
		t = (min.x - mOrigin.x) / mDirection.x;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
			hitpoint.z >= min.z && hitpoint.z <= max.z &&
			(!hit || t < lowt)) //-V560
		{
			hit = true;
			lowt = t;
		}
	}
	// Max x
	if (mOrigin.x >= max.x && mDirection.x < 0.0f)
	{
		t = (max.x - mOrigin.x) / mDirection.x;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
			hitpoint.z >= min.z && hitpoint.z <= max.z &&
			(!hit || t < lowt))
		{
			hit = true;
			lowt = t;
		}
	}
	// Min y
	if (mOrigin.y <= min.y && mDirection.y > 0.0f)
	{
		t = (min.y - mOrigin.y) / mDirection.y;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
			hitpoint.z >= min.z && hitpoint.z <= max.z &&
			(!hit || t < lowt))
		{
			hit = true;
			lowt = t;
		}
	}
	// Max y
	if (mOrigin.y >= max.y && mDirection.y < 0.0f)
	{
		t = (max.y - mOrigin.y) / mDirection.y;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
			hitpoint.z >= min.z && hitpoint.z <= max.z &&
			(!hit || t < lowt))
		{
			hit = true;
			lowt = t;
		}
	}
	// Min z
	if (mOrigin.z <= min.z && mDirection.z > 0.0f)
	{
		t = (min.z - mOrigin.z) / mDirection.z;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
			hitpoint.y >= min.y && hitpoint.y <= max.y &&
			(!hit || t < lowt))
		{
			hit = true;
			lowt = t;
		}
	}
	// Max z
	if (mOrigin.z >= max.z && mDirection.z < 0.0f)
	{
		t = (max.z - mOrigin.z) / mDirection.z;
		hitpoint = mOrigin + mDirection * t;
		if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
			hitpoint.y >= min.y && hitpoint.y <= max.y &&
			(!hit || t < lowt))
		{
			hit = true;
			lowt = t;
		}
	}

	return std::pair<bool, F32>(hit, lowt);
}

bool Ray::operator==(const Ray& ray) const
{
	return mOrigin == ray.mOrigin && mDirection == ray.mDirection;
}

bool Ray::operator!=(const Ray& ray) const
{
	return !operator==(ray);
}

} // namespace oe
