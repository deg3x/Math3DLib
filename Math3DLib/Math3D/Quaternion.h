#pragma once
#include "Math3dHelpers.h"
#include <iostream>

namespace math3d
{
	class Quaternion
	{
	private:
		double w;
		double x;
		double y;
		double z;

		void ClearNearlyZeroComponents();

	public:
		static const Quaternion zero;

		Quaternion();
		Quaternion(double w, double x, double y, double z);
		Quaternion(const Quaternion& quat);
		~Quaternion() = default;

		void Conjugate();
		void Inverse();
		void Normalize();
		bool IsUnit() const;
		double Magnitude() const;
		double DotProduct(const Quaternion& quat) const;
		Vector3 RotateVector(Vector3 vec);
		Quaternion Slerp(const Quaternion& quat, const double alpha) const;

		static Quaternion Normalize(const Quaternion& quat);
		static Quaternion Conjugate(const Quaternion& quat);
		static Quaternion Inverse(const Quaternion& quat);
		static double DotProduct(const Quaternion& quatA, const Quaternion& quatB);
		static Quaternion CreateRotationAboutAxis(double angle, Vector3 axis);
		static Vector3 RotateVectorBy(Vector3 vec, Quaternion quat);
		static Quaternion Slerp(const Quaternion& quatA, const Quaternion& quatB, const double A);

		Quaternion& operator=(const Quaternion& quat);
		Quaternion& operator+=(const Quaternion& quat);
		Quaternion& operator-=(const Quaternion& quat);
		Quaternion& operator*=(const Quaternion& quat);
		Quaternion& operator*=(const double& scalar);

		inline void SetW(double val)
		{
			this->w = val;
		}

		inline void SetX(double val)
		{
			this->x = val;
		}

		inline void SetY(double val)
		{
			this->y = val;
		}

		inline void SetZ(double val)
		{
			this->z = val;
		}

		inline double GetW()
		{
			return this->w;
		}

		inline double GetX()
		{
			return this->x;
		}

		inline double GetY()
		{
			return this->y;
		}

		inline double GetZ()
		{
			return this->z;
		}

		friend std::ostream& operator<<(std::ostream& out, const Quaternion& quat)
		{
			out << "Q(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;

			return out;
		}
	};

	inline Quaternion operator+(Quaternion quatA, const Quaternion& quatB)
	{
		return quatA += quatB;
	}

	inline Quaternion operator-(Quaternion quatA, const Quaternion& quatB)
	{
		return quatA -= quatB;
	}

	inline Quaternion operator*(Quaternion quatA, const Quaternion& quatB)
	{
		return quatA *= quatB;
	}

	inline Quaternion operator*(Quaternion quatA, const double& scalar)
	{
		return quatA *= scalar;
	}
}