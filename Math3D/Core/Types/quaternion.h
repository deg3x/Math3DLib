#pragma once
#include "math3dhelpers.h"
#include <iostream>

namespace math3d
{
	class Quaternion
	{
	private:
		float w;
		float x;
		float y;
		float z;

		void ClearNearlyZeroComponents();

	public:
		static const Quaternion zero;

		Quaternion();
		Quaternion(float w, float x, float y, float z);
		Quaternion(const Quaternion& quat);
		~Quaternion() = default;

		void Conjugate();
		void Inverse();
		void Normalize();
		bool IsUnit() const;
		float Magnitude() const;
		float DotProduct(const Quaternion& quat) const;
		Vector3 RotateVector(Vector3 vec);
		Quaternion Slerp(const Quaternion& quat, const float alpha) const;

		static Quaternion Normalize(const Quaternion& quat);
		static Quaternion Conjugate(const Quaternion& quat);
		static Quaternion Inverse(const Quaternion& quat);
		static double DotProduct(const Quaternion& quatA, const Quaternion& quatB);
		static Quaternion CreateRotationAboutAxis(float angle, Vector3 axis);
		static Vector3 RotateVectorBy(Vector3 vec, Quaternion quat);
		static Quaternion Slerp(const Quaternion& quatA, const Quaternion& quatB, const float A);

		Quaternion& operator=(const Quaternion& quat);
		Quaternion& operator+=(const Quaternion& quat);
		Quaternion& operator-=(const Quaternion& quat);
		Quaternion& operator*=(const Quaternion& quat);
		Quaternion& operator*=(const float& scalar);

		inline void SetW(float val)
		{
			this->w = val;
		}

		inline void SetX(float val)
		{
			this->x = val;
		}

		inline void SetY(float val)
		{
			this->y = val;
		}

		inline void SetZ(float val)
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

	inline Quaternion operator*(Quaternion quatA, const float& scalar)
	{
		return quatA *= scalar;
	}
}