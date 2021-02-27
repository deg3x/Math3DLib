#pragma once
#include "Vector.h"
#include "Matrix.h"

namespace math3d
{
	typedef Vector<float, 2> Vector2;
	typedef Vector<float, 3> Vector3;
	typedef Matrix<float, 2, 2> Matrix2x2;
	typedef Matrix<float, 3, 3> Matrix3x3;
	typedef Matrix<float, 4, 4> Matrix4x4;

	/*class Vector2 : public Vector<double>
	{
	public:
		Vector2() : Vector<double>(2) {}
		Vector2(double x, double y);
		inline void SetX(double val) { *this->values = val; }
		inline void SetY(double val) { *(this->values + 1) = val; }
		inline double GetX() { return *values; }
		inline double GetY() { return *(values + 1); }
	};

	class Vector3 : public Vector<double>
	{
	public:
		Vector3() : Vector<double>(3) {}
		Vector3(double x, double y, double z);
		inline void SetX(double val) { *this->values = val; }
		inline void SetY(double val) { *(this->values + 1) = val; }
		inline void SetZ(double val) { *(this->values + 2) = val; }
		inline double GetX() { return *values; }
		inline double GetY() { return *(values + 1); }
		inline double GetZ() { return *(values + 2); }
	};

	class Vector4 : public Vector<double>
	{
	public:
		Vector4() : Vector<double>(4) {}
		Vector4(double x, double y, double z, double w);
		inline void SetX(double val) { *this->values = val; }
		inline void SetY(double val) { *(this->values + 1) = val; }
		inline void SetZ(double val) { *(this->values + 2) = val; }
		inline void SetW(double val) { *(this->values + 3) = val; }
		inline double GetX() { return *values; }
		inline double GetY() { return *(values + 1); }
		inline double GetZ() { return *(values + 2); }
		inline double GetW() { return *(values + 3); }
	};

	class Matrix2x2 : public Matrix<double>
	{
	public:
		Matrix2x2() : Matrix<double>(2, 2) {}
		Matrix2x2(const double* values) : Matrix<double>(2, 2, values) {}
	};

	class Matrix3x3 : public Matrix<double>
	{
	public:
		Matrix3x3() : Matrix<double>(3, 3) {}
		Matrix3x3(const double* values) : Matrix<double>(3, 3, values) {}
	};

	class Matrix4x4 : public Matrix<double>
	{
	public:
		Matrix4x4() : Matrix<double>(4, 4) {}
		Matrix4x4(const double* values) : Matrix<double>(4, 4, values) {}
	};*/
}