#pragma once
#include <cfloat>
#include <intrin.h>

namespace math3d
{
#define PI			3.14159265358979323846
#define SQRT_TWO	1.4142135623730950488016887242097
#define SQRT_THREE	1.7320508075688772935274463415059

	/*// Fast x86 square root calculation, utilizing hardware fsqrt
	// Carmack's algorithm is history :)
	inline double __declspec (naked) __fastcall sqrt(double val)
	{
		__asm
		{
			fld qword ptr [esp+4]
			fsqrt
			ret 8
		}
	}

	inline float __declspec (naked) __fastcall sqrt(float val)
	{
		__asm
		{
			fld dword ptr[esp + 4]
			fsqrt
			ret 4
		}
	}*/

	//
	// Add actual sqrt implementations / Dont rely on inlined assembly (Intel intrinsics?)
	//

	float sin(float angle);
	float cos(float angle);
	double sin(double angle);
	double cos(double angle);
	float asin(float value);
	float acos(float value);
	double asin(double value);
	double acos(double value);

	inline float DegToRad(float angle)
	{
		return (angle / 180.0f) * (float)PI;
	}

	inline double DegToRad(double angle)
	{
		return (angle / 180.0) * PI;
	}

	inline float RadToDeg(float angle)
	{
		return (angle / (float)PI) * 180.0f;
	}

	inline double RadToDeg(double angle)
	{
		return (angle / PI) * 180.0;
	}

	inline float Abs(float val)
	{
		return val > 0.0f ? val : -val;
	}

	inline double Abs(double val)
	{
		return val > 0.0 ? val : -val;
	}

	inline bool IsNearlyEqual(float valA, float valB)
	{
		return Abs(valA - valB) < FLT_EPSILON;
	}

	inline bool IsNearlyEqual(double valA, double valB)
	{
		return Abs(valA - valB) < DBL_EPSILON;
	}

	inline bool IsNearlyZero(float val)
	{
		return IsNearlyEqual(val, 0.0f);
	}

	inline bool IsNearlyZero(double val)
	{
		return IsNearlyEqual(val, 0.0);
	}
}