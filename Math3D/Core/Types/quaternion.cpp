#include "quaternion.h"
#include "math3dutil.h"
#include "math3dhelpers.h"
#include "vector.h"
#include <iostream>

using namespace math3d;

Quaternion::Quaternion() : w(0.0f), x(0.0f), y(0.0f), z(0.0f) {}
Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}
Quaternion::Quaternion(const Quaternion& quat) : w(quat.w), x(quat.x), y(quat.y), z(quat.z) {}

void Quaternion::ClearNearlyZeroComponents()
{
	this->w = IsNearlyZero(this->w) ? 0.0 : this->w;
	this->x = IsNearlyZero(this->x) ? 0.0 : this->x;
	this->y = IsNearlyZero(this->y) ? 0.0 : this->y;
	this->z = IsNearlyZero(this->z) ? 0.0 : this->z;
}

void Quaternion::Conjugate()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

void Quaternion::Inverse()
{
	Quaternion inverse;

	inverse = Quaternion::Conjugate(*this) * (1.0 / (this->Magnitude() * this->Magnitude()));

	this->w = inverse.w;
	this->x = inverse.x;
	this->y = inverse.y;
	this->z = inverse.z;

	this->ClearNearlyZeroComponents();
}

void Quaternion::Normalize()
{
	if (this->IsUnit())
	{
		return;
	}

	double invMagnitude = 1.0 / this->Magnitude();

	this->w *= invMagnitude;
	this->x *= invMagnitude;
	this->y *= invMagnitude;
	this->z *= invMagnitude;
}

bool Quaternion::IsUnit() const
{
	return IsNearlyEqual(this->Magnitude(), 1.0);
}

double Quaternion::Magnitude() const
{
	return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
}

double Quaternion::DotProduct(const Quaternion& quat) const
{
	return (this->w * quat.w + this->x * quat.x + this->y * quat.y + this->z * quat.z);
}

Vector3 Quaternion::RotateVector(Vector3 vec)
{
	Quaternion rotated = *this * Quaternion(0.0, vec[0], vec[1], vec[2]) * Quaternion::Inverse(*this);
	rotated.ClearNearlyZeroComponents();

	float ret[3] = { rotated.x, rotated.y, rotated.z };

	return Vector3(ret);
}

Quaternion Quaternion::Slerp(const Quaternion& quat, const double alpha) const
{
	Quaternion quatA = Quaternion::Normalize(*this);
	Quaternion quatB = Quaternion::Normalize(quat);

	double theta = acos(Quaternion::DotProduct(quatA, quatB));

	Quaternion ret = quatA * (sin(theta * (1 - alpha)) / sin(theta)) + quatB * (sin(theta * alpha) / sin(theta));

	return ret;
}

Quaternion Quaternion::Normalize(const Quaternion& quat)
{
	if (quat.IsUnit())
	{
		return quat;
	}

	double invMagnitude = 1.0 / quat.Magnitude();

	Quaternion ret;

	ret.w = quat.w * invMagnitude;
	ret.x = quat.x * invMagnitude;
	ret.y = quat.y * invMagnitude;
	ret.z = quat.z * invMagnitude;

	return ret;
}

Quaternion Quaternion::Conjugate(const Quaternion& quat)
{
	Quaternion ret(quat.w, -quat.x, -quat.y, -quat.z);

	return ret;
}

Quaternion Quaternion::Inverse(const Quaternion& quat)
{
	Quaternion inverse;

	inverse = Quaternion::Conjugate(quat) * (1.0 / (quat.Magnitude() * quat.Magnitude()));
	inverse.ClearNearlyZeroComponents();
	
	return inverse;
}

double Quaternion::DotProduct(const Quaternion& quatA, const Quaternion& quatB)
{
	return (quatA.w * quatB.w + quatA.x * quatB.x + quatA.y * quatB.y + quatA.z * quatB.z);
}

Quaternion Quaternion::CreateRotationAboutAxis(double angle, Vector3 axis)
{
	Quaternion rotation;

	axis.Normalize();

	angle /= 2.0f;

	rotation.w = cos(angle);
	rotation.x = sin(angle) * axis[0];
	rotation.y = sin(angle) * axis[1];
	rotation.z = sin(angle) * axis[2];

	rotation.ClearNearlyZeroComponents();

	return rotation;
}

Vector3 Quaternion::RotateVectorBy(Vector3 vec, Quaternion quat)
{
	Quaternion rotated = quat * Quaternion(0.0, vec[0], vec[1], vec[2]) * Quaternion::Inverse(quat);
	rotated.ClearNearlyZeroComponents();

	float ret[3] = { rotated.x, rotated.y, rotated.z };

	return Vector3(ret);
}

Quaternion Quaternion::Slerp(const Quaternion& quatA, const Quaternion& quatB, const double alpha)
{
	Quaternion quaternionA = Quaternion::Normalize(quatA);
	Quaternion quaternionB = Quaternion::Normalize(quatB);

	double theta = acos(Quaternion::DotProduct(quaternionA, quaternionB));

	Quaternion ret = quaternionA * (sin(theta * (1 - alpha)) / sin(theta)) + quaternionB * (sin(theta * alpha) / sin(theta));

	return ret;
}

Quaternion& Quaternion::operator=(const Quaternion& quat)
{
	this->w = quat.w;
	this->x = quat.x;
	this->y = quat.y;
	this->z = quat.z;

	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
	this->w += quat.w;
	this->x += quat.x;
	this->y += quat.y;
	this->z += quat.z;

	this->ClearNearlyZeroComponents();

	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
	this->w -= quat.w;
	this->x -= quat.x;
	this->y -= quat.y;
	this->z -= quat.z;

	this->ClearNearlyZeroComponents();

	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& quat)
{
	double w = (this->w * quat.w) - (this->x * quat.x) - (this->y * quat.y) - (this->z * quat.z);
	double x = (this->w * quat.x) + (this->x * quat.w) + (this->y * quat.z) - (this->z * quat.y);
	double y = (this->w * quat.y) + (this->y * quat.w) - (this->x * quat.z) + (this->z * quat.x);
	double z = (this->w * quat.z) + (this->z * quat.w) + (this->x * quat.y) - (this->y * quat.x);

	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;

	this->ClearNearlyZeroComponents();

	return *this;
}

Quaternion& Quaternion::operator*=(const double& scalar)
{
	this->w = w * scalar;
	this->x = x * scalar;
	this->y = y * scalar;
	this->z = z * scalar;

	this->ClearNearlyZeroComponents();

	return *this;
}

const Quaternion Quaternion::zero = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);