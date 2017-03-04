#include "Quaternion.hpp"

namespace oe
{

Quaternion::Quaternion()
	: mScalar()
	, mVector()
{
}

Quaternion::Quaternion(const Quaternion& q)
	: mScalar(q.mScalar)
	, mVector(q.mVector)
{
}

Quaternion::Quaternion(F32 s1, F32 s2, F32 s3, F32 s4)
	: mScalar(s1)
	, mVector(s2, s3, s4)
{
}

Quaternion::Quaternion(F32 s, const Vector3& v)
	: mScalar(s)
	, mVector(v)
{
}

F32& Quaternion::scalar()
{
	return mScalar;
}

const F32& Quaternion::scalar() const
{
	return mScalar;
}

Vector3& Quaternion::vector()
{
	return mVector;
}

const Vector3& Quaternion::vector() const
{
	return mVector;
}

Quaternion Quaternion::inversed() const
{
	return Quaternion(mScalar, -mVector);
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	mScalar = q.mScalar;
	mVector = q.mVector;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return Quaternion(mScalar * q.mScalar - Vector3::dotProduct(mVector, q.mVector), mScalar * q.mVector + q.mScalar * mVector + Vector3::crossProduct(mVector, q.mVector));
}

Quaternion Quaternion::operator*(F32 s) const
{
	F32 angle;
	Vector3 axis;
	toAngleAxis(&angle, &axis);
	angle *= s;
	return Quaternion(Math::cos(0.5f * angle), axis.normalized() * Math::sin(0.5f * angle));
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
	F32 ss = mScalar + mScalar;
	return ss * Vector3::crossProduct(mVector, v) + (ss * mScalar - 1) * v + 2 * Vector3::dotProduct(mVector, v) * mVector;
}

F32 Quaternion::normalize()
{
	const F32 length = Math::sqrt(mScalar * mScalar + Vector3::dotProduct(mVector, mVector));
	const F32 scale = (1.f / length);
	mScalar *= scale;
	mVector *= scale;
	return length;
}

Quaternion Quaternion::normalized() const
{
	Quaternion q(*this);
	q.normalize();
	return q;
}

void Quaternion::toAngleAxis(F32* angle, Vector3* axis) const
{
	*axis = mScalar > 0.f ? mVector : -mVector;
	*angle = 2.f * Math::atan2(axis->normalize(), mScalar > 0.f ? mScalar : -mScalar);
}

Vector3 Quaternion::toEulerAngles() const
{
	Matrix3 m(toMatrix());
	F32 cos2 = m[0] * m[0] + m[1] * m[1];
	if (cos2 < 1e-6f)
	{
		return Vector3(0.f, m[2] < 0.f ? Math::halfPi() : -Math::halfPi(), -Math::atan2(m[3], m[4]));
	}
	else
	{
		return Vector3(Math::atan2(m[5], m[8]), Math::atan2(-m[2], Math::sqrt(cos2)), Math::atan2(m[1], m[0]));
	}
}

Matrix3 Quaternion::toMatrix() const
{
	const F32 x2 = mVector[0] * mVector[0];
	const F32 y2 = mVector[1] * mVector[1];
	const F32 z2 = mVector[2] * mVector[2];
	const F32 sx = mScalar * mVector[0];
	const F32 sy = mScalar * mVector[1];
	const F32 sz = mScalar * mVector[2];
	const F32 xz = mVector[0] * mVector[2];
	const F32 yz = mVector[1] * mVector[2];
	const F32 xy = mVector[0] * mVector[1];
	return Matrix3(1.f - 2.f * (y2 + z2), 2.f * (xy + sz), 2.f * (xz - sy), 2.f * (xy - sz), 1.f - 2.f * (x2 + z2), 2.f * (sx + yz), 2.f * (sy + xz), 2.f * (yz - sx), 1.f - 2.f * (x2 + y2));
}

Matrix4 Quaternion::toMatrix4() const
{
	const F32 x2 = mVector[0] * mVector[0];
	const F32 y2 = mVector[1] * mVector[1];
	const F32 z2 = mVector[2] * mVector[2];
	const F32 sx = mScalar * mVector[0];
	const F32 sy = mScalar * mVector[1];
	const F32 sz = mScalar * mVector[2];
	const F32 xz = mVector[0] * mVector[2];
	const F32 yz = mVector[1] * mVector[2];
	const F32 xy = mVector[0] * mVector[1];
	return Matrix4(1.f - 2.f * (y2 + z2), 2.f * (xy + sz), 2.f * (xz - sy), 0.f, 2.f * (xy - sz), 1.f - 2.f * (x2 + z2), 2.f * (sx + yz), 0.f, 2.f * (sy + xz), 2.f * (yz - sx), 1.f - 2.f * (x2 + y2), 0.f, 0.f, 0.f, 0.f, 1.f);
}

Quaternion Quaternion::fromAngleAxis(F32 angle, const Vector3& axis)
{
	const F32 halfAngle = 0.5f * angle;
	Vector3 localAxis(axis);
	return Quaternion(Math::cos(halfAngle), localAxis.normalized() * Math::sin(halfAngle));
}

Quaternion Quaternion::fromEulerAngles(const Vector3& angles)
{
	const Vector3 halfAngles(0.5f * angles[0], 0.5f * angles[1], 0.5f * angles[2]);
	const F32 sinx = Math::sin(halfAngles[0]);
	const F32 cosx = Math::cos(halfAngles[0]);
	const F32 siny = Math::sin(halfAngles[1]);
	const F32 cosy = Math::cos(halfAngles[1]);
	const F32 sinz = Math::sin(halfAngles[2]);
	const F32 cosz = Math::cos(halfAngles[2]);
	return Quaternion(cosx * cosy * cosz + sinx * siny * sinz, sinx * cosy * cosz - cosx * siny * sinz, cosx * siny * cosz + sinx * cosy * sinz, cosx * cosy * sinz - sinx * siny * cosz);
}

Quaternion Quaternion::fromMatrix(const Matrix3& m)
{
	const F32 trace = m(0, 0) + m(1, 1) + m(2, 2);
	if (trace > 0)
	{
		const F32 s = Math::sqrt(trace + 1) * 2.f;
		const F32 oneOverS = 1.f / s;
		return Quaternion(0.25f * s, (m[5] - m[7]) * oneOverS, (m[6] - m[2]) * oneOverS, (m[1] - m[3]) * oneOverS);
	}
	else if (m[0] > m[4] && m[0] > m[8])
	{
		const F32 s = Math::sqrt(m[0] - m[4] - m[8] + 1) * 2.f;
		const F32 oneOverS = 1.f / s;
		return Quaternion((m[5] - m[7]) * oneOverS, 0.25f * s, (m[3] + m[1]) * oneOverS, (m[6] + m[2]) * oneOverS);
	}
	else if (m[4] > m[8])
	{
		const F32 s = Math::sqrt(m[4] - m[0] - m[8] + 1) * 2.f;
		const F32 oneOverS = 1.f / s;
		return Quaternion((m[6] - m[2]) * oneOverS, (m[3] + m[1]) * oneOverS, 0.25f * s, (m[5] + m[7]) * oneOverS);
	}
	else
	{
		const F32 s = Math::sqrt(m[8] - m[0] - m[4] + 1) * 2.f;
		const F32 oneOverS = 1.f / s;
		return Quaternion((m[1] - m[3]) * oneOverS, (m[6] + m[2]) * oneOverS, (m[5] + m[7]) * oneOverS, 0.25f * s);
	}
}

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, F32 percent)
{
	if (q1.mScalar * q2.mScalar + Vector3::dotProduct(q1.mVector, q2.mVector) > 0.999999f)
	{
		return Quaternion(q1.mScalar * (1 - percent) + q2.mScalar * percent, q1.mVector * (1 - percent) + q2.mVector * percent);
	}
	return q1 * ((q1.inversed() * q2) * percent);
}

F32& Quaternion::operator[](const U8 i)
{
	if (i == 0)
	{
		return mScalar;
	}
	return mVector[i - 1];
}

const F32& Quaternion::operator[](const U8 i) const
{
	return const_cast<Quaternion*>(this)->operator[](i);
}

Vector3 Quaternion::perpendicularVector(const Vector3& v)
{
	// We start out by taking the cross product of the vector and the x-axis to
	// find something parallel to the input vectors.  If that cross product
	// turns out to be length 0 (i. e. the vectors already lie along the x axis)
	// then we use the y-axis instead.
	Vector3 axis = Vector3::crossProduct(Vector3(1.f, 0.f, 0.f), v);
	// We use a fairly high epsilon here because we know that if this number
	// is too small, the axis we'll get from a cross product with the y axis
	// will be much better and more numerically stable.
	if (axis.getLengthSquared() < 0.05f)
	{
		axis = Vector3::crossProduct(Vector3(0.f, 1.f, 0.f), v);
	}
	return axis;
}

Quaternion Quaternion::rotateFromToWithAxis(const Vector3& v1, const Vector3& v2, const Vector3& preferred_axis)
{
	Vector3 start = v1.normalized();
	Vector3 end = v2.normalized();
	F32 dot_product = Vector3::dotProduct(start, end);
	// Any rotation < 0.1 degrees is treated as no rotation in order to avoid division by zero errors.
	// So we early-out in cases where it's less then 0.1 degrees.
	// cos( 0.1 degrees) = 0.99999847691
	if (dot_product >= 0.99999847691f)
	{
		return Quaternion::identity();
	}
	// If the vectors point in opposite directions, return a 180 degree rotation, on the axis that they asked for.
	if (dot_product <= -0.99999847691f)
	{
		return Quaternion(0.f, preferred_axis);
	}
	// Degenerate cases have been handled, so if we're here, we have to actually compute the angle we want:
	Vector3 crosmScalarproduct = Vector3::crossProduct(start, end);
	return Quaternion(1.f + dot_product, crosmScalarproduct).normalized();
}

Quaternion Quaternion::rotateFromTo(const Vector3& v1, const Vector3& v2)
{
	Vector3 start = v1.normalized();
	Vector3 end = v2.normalized();
	F32 dot_product = Vector3::dotProduct(start, end);
	// Any rotation < 0.1 degrees is treated as no rotation in order to avoid division by zero errors.
	// So we early-out in cases where it's less then 0.1 degrees.
	// cos( 0.1 degrees) = 0.99999847691
	if (dot_product >= 0.99999847691f)
	{
		return Quaternion::identity();
	}
	// If the vectors point in opposite directions, return a 180 degree rotation, on an arbitrary axis.
	if (dot_product <= -0.99999847691f)
	{
		return Quaternion(0.f, perpendicularVector(start));
	}
	// Degenerate cases have been handled, so if we're here, we have to actually compute the angle we want:
	Vector3 crosmScalarproduct = Vector3::crossProduct(start, end);
	return Quaternion(1.f + dot_product, crosmScalarproduct).normalized();
}

Quaternion Quaternion::identity()
{
	return Quaternion(1.f, 0.f, 0.f, 0.f);
}

Quaternion operator*(F32 s, const Quaternion& q)
{
	return q * s;
}

} // namespace oe