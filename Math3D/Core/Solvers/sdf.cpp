#include "sdf.h"
#include "vector.h"

float CircleSDF(math3d::Vector<float, 2> center, float radius, math3d::Vector<float, 2> point)
{
	return (center - point).Magnitude() - radius;
}

float SphereSDF(math3d::Vector<float, 3> center, float radius, math3d::Vector<float, 3> point)
{
	return (center - point).Magnitude() - radius;
}