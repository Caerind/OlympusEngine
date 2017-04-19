#include "Quaternion.hpp"

namespace oe
{

Quaternion::Quaternion()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
{
}

Quaternion::Quaternion(const Quaternion& q)
{
	set(q);
}

Quaternion::Quaternion(F32 x, F32 y, F32 z, F32 w)
{
	set(x, y, z, w);
}

Quaternion::Quaternion(const Vector3& v, F32 w)
{
	set(v, w);
}

Quaternion::Quaternion(F32 pitch, F32 yaw, F32 roll)
{
	set(pitch, yaw, roll);
}

Quaternion::Quaternion(const Vector3& eulerAngles)
{
	set(eulerAngles);
}

Quaternion::Quaternion(F32 angle, const Vector3& axis)
{
	set(angle, axis);
}

Quaternion::Quaternion(const F32 q[4])
{
	set(q);
}

Quaternion& Quaternion::set(const Quaternion& q)
{
	std::memcpy(this, &q, sizeof(Quaternion));
	return *this;
}

Quaternion& Quaternion::set(F32 x, F32 y, F32 z, F32 w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

Quaternion& Quaternion::set(const Vector3& v, F32 w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
	return *this;
}

Quaternion& Quaternion::set(F32 pitch, F32 yaw, F32 roll)
{
	// TODO : Chech that everything is correct
	yaw *= 0.5f;
	roll *= 0.5f;
	pitch *= 0.5f;
	const F32 c1 = Math::cos(yaw);
	const F32 c2 = Math::cos(roll);
	const F32 c3 = Math::cos(pitch);
	const F32 s1 = Math::sin(yaw);
	const F32 s2 = Math::sin(roll);
	const F32 s3 = Math::sin(pitch);
	return set(s1 * s2 * c3 + c1 * c2 * s3, s1 * c2 * c3 + c1 * s2 * s3, c1 * s2 * c3 - s1 * c2 * s3, c1 * c2 * c3 - s1 * s2 * s3);
}

Quaternion& Quaternion::set(const Vector3& eulerAngles)
{
	return set(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Quaternion& Quaternion::set(F32 angle, const Vector3& axis)
{
	// TODO : Chech that everything is correct
	angle *= 0.5f;
	Vector3 normalizedAxis = axis.getNormal();
	const F32 sinAngle = Math::sin(angle);
	x = normalizedAxis.x * sinAngle;
	y = normalizedAxis.y * sinAngle;
	z = normalizedAxis.z * sinAngle;
	w = Math::cos(angle);
	return normalize();
}

Quaternion& Quaternion::set(const F32 q[4])
{
	std::memcpy(&x, q, 4 * sizeof(F32));
	return *this;
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	return set(q);
}

bool Quaternion::operator==(const Quaternion& q) const
{
	return Math::equals(x, q.x) && Math::equals(y, q.y) && Math::equals(z, q.z) && Math::equals(w, q.w);
}

bool Quaternion::operator!=(const Quaternion& q) const
{
	return !operator==(q);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	// TODO : Chech that everything is correct
	Quaternion result;
	result.x = w * q.x + x * q.w + y * q.z - z * q.y;
	result.y = w * q.y + y * q.w + z * q.x - x * q.z;
	result.z = w * q.z + z * q.w + x * q.y - y * q.x;
	result.w = w * q.w - x * q.x - y * q.y - z * q.z;
	return result;
}

Quaternion Quaternion::operator*(F32 scale) const
{
	return Quaternion(x * scale, y * scale, z * scale, w * scale);
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	return set(operator*(q));
}

Quaternion& Quaternion::operator*=(F32 scale)
{
	return set(operator*(scale));
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
	// TODO : Chech that everything is correct
	Vector3 qv = getVector();
	Vector3 uv = qv.crossProduct(v);
	Vector3 uuv = qv.crossProduct(uv);
	uv *= 2.0f * w;
	uuv *= 2.0f;
	return v + uv + uuv;
}

Quaternion::operator F32*()
{
	return &x;
}

Quaternion::operator const F32*() const
{
	return &x;
}

Quaternion& Quaternion::computeW()
{
	// TODO : Chech that everything is correct
	F32 t = 1.0f - getSquaredMagnitude();
	w = (t < 0.0f) ? 0.0f : -Math::sqrt(t);
	return *this;
}

Quaternion& Quaternion::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

Quaternion& Quaternion::inverse()
{
	// TODO : Chech that everything is correct
	F32 norm = getSquaredMagnitude();
	if (norm > 0.0f)
	{
		F32 invNorm = 1.0f / norm;
		x *= -invNorm;
		y *= -invNorm;
		z *= -invNorm;
		w *= invNorm;
	}
	return *this;
}

Quaternion& Quaternion::normalize(F32* oldLength)
{
	F32 norm = getMagnitude();
	if (norm > 0.0f)
	{
		F32 invNorm = 1.0f / norm;
		x *= invNorm;
		y *= invNorm;
		z *= invNorm;
		w *= invNorm;
	}
	if (oldLength)
	{
		*oldLength = norm;
	}
	return *this;
}

F32 Quaternion::dotProduct(const Quaternion& q) const
{
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

F32 Quaternion::getSquaredMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

F32 Quaternion::getMagnitude() const
{
	return Math::sqrt(getSquaredMagnitude());
}

Quaternion Quaternion::getConjugate() const
{
	return Quaternion(*this).conjugate();
}

Quaternion Quaternion::getInverse() const
{
	return Quaternion(*this).inverse();
}

Quaternion Quaternion::getNormal(F32* oldLength) const
{
	return Quaternion(*this).normalize(oldLength);
}

Vector3 Quaternion::getVector() const
{
	return Vector3(x, y, z);
}

Vector3 Quaternion::getEulerAngles() const
{
	// TODO : Chech that everything is correct
	F32 test = x * y + z * w;
	if (test > 0.499f)
	{
		// singularity at north pole
		return Vector3(90.0f, 2.0f * Math::atan2(x, w), 0.0f);
	}
	if (test < -0.499f)
	{
		// singularity at south pole
		return Vector3(-90.0f, -2.0f * Math::atan2(x, w), 0.0f);
	}
	return Vector3(Math::atan2(2.0f * x * w - 2.0f * y * z, 1.0f - 2.0f * x * x - 2.0f * z * z),
		           Math::atan2(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f * y * y - 2.0f * z * z),
		           Math::asin(2.0f * test));
}

void Quaternion::getAngleAxis(F32* angle, Vector3* axis)
{
	// TODO : Chech that everything is correct
	*axis = getVector() * ((w > 0.0f) ? 1.0f : -1.0f);
	F32 length;
	axis->normalize(&length);
	*angle = 2.0f * Math::atan2(length, w * ((w > 0.0f) ? 1.0f : -1.0f));
}

Quaternion& Quaternion::makeRotation(const Vector3& from, const Vector3& to)
{
	// TODO : Chech that everything is correct
	F32 dot = from.dotProduct(to);
	if (Math::equals(dot, -1.0f))
	{
		Vector3 cross(Vector3::axisX().crossProduct(from));
		if (Math::equals(cross.getLength(), 0.0f))
			cross = Vector3::axisY().crossProduct(from);
		return set(180.0f, cross);
	}
	else if (Math::equals(dot, 1.0f))
	{
		return makeIdentity();
	}
	else
	{
		Vector3 c(from.crossProduct(to));
		x = c.x;
		y = c.y;
		z = c.z;
		w = 1.0f + dot;
		return normalize();
	}
}

Quaternion& Quaternion::makeZero()
{
	return set(0.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion& Quaternion::makeIdentity()
{
	return set(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::normalize(const Quaternion& quat, F32* length)
{
	return Quaternion(quat).normalize(length);
}

Quaternion Quaternion::rotation(const Vector3& from, const Vector3& to)
{
	return Quaternion().makeRotation(from, to);
}

Quaternion Quaternion::lerp(const Quaternion& start, const Quaternion& end, F32 percent)
{
	const F32 omp = 1.f - percent;
	return Quaternion(omp * start.x + percent * end.x, omp * start.y + percent * end.y, omp * start.z + percent * end.z, omp * start.w + percent * end.w);
}

Quaternion Quaternion::slerp(const Quaternion& start, const Quaternion& end, F32 percent)
{
	Quaternion q;
	F32 cosOmega = start.dotProduct(end);
	if (cosOmega < 0.0f)
	{
		q.set(-end.w, -end.x, -end.y, -end.z);
		cosOmega = -cosOmega;
	}
	else
	{
		q.set(end);
	}
	F32 a, b;
	if (cosOmega > 0.9999f)
	{
		// Lerp to avoid div by zero
		return lerp(start, end, percent);
	}
	else
	{
		F32 sinOmega = Math::sqrt(1.0f - cosOmega * cosOmega);
		F32 omega = Math::atan2(sinOmega, cosOmega);
		sinOmega = 1.0f / sinOmega;
		a = Math::sin((1.0f - percent) * omega) * sinOmega;
		b = Math::sin(percent * omega) * sinOmega;
	}
	return Quaternion(a * start.x + b * q.x, a * start.y + b * q.y, a * start.z + b * q.z, a * start.w + b * q.w);
}

Quaternion Quaternion::zero()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion Quaternion::identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

const U8 Quaternion::dim()
{
	return 4;
}

Quaternion operator*(F32 scale, const Quaternion& q)
{
	return q * scale;
}

} // namespace oe
