#include "math3dutil.h"
#include <cmath>
#include <iostream>

using namespace math3d;

//
// I feel ashamed for creating this dependency, but we'll roll our own
// trigonometric functions when we find a satisfying implementation
//
float math3d::sin(float angle)
{
	return std::sin(DegToRad(angle));
}

float math3d::cos(float angle)
{
	return std::cos(DegToRad(angle));
}

double math3d::sin(double angle)
{
	return std::sin(DegToRad(angle));
}

double math3d::cos(double angle)
{
	return std::cos(DegToRad(angle));
}

float math3d::asin(float value)
{
	return std::asin(value);
}

float math3d::acos(float value)
{
	return std::acos(value);
}

double math3d::asin(double value)
{
	return std::sin(value);
}

double math3d::acos(double value)
{
	return std::cos(value);
}