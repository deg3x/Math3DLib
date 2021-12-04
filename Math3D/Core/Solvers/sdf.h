#pragma once
#include "vector.h"

namespace math3d
{
	float LineSegmentSDF(math3d::Vector<float, 2> segmentStart, math3d::Vector<float, 2> segmentEnd, math3d::Vector<float, 2> point);
	float CircleSDF(math3d::Vector<float, 2> center, float radius, math3d::Vector<float, 2> point);
	float SphereSDF(math3d::Vector<float, 3> center, float radius, math3d::Vector<float, 3> point);
}
