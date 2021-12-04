#include "sdf.h"
#include "vector.h"
#include "math3dutil.h"

float math3d::LineSegmentSDF(math3d::Vector<float, 2> segmentStart, math3d::Vector<float, 2> segmentEnd, math3d::Vector<float, 2> point)
{
	math3d::Vector<float, 2> segment = segmentEnd - segmentStart;
	math3d::Vector<float, 2> startToPoint = point - segmentStart;

	float alpha = math3d::clamp(0.0f, 1.0f, math3d::Vector<float, 2>::DotProduct(segment, startToPoint) / math3d::Vector<float, 2>::DotProduct(segment, segment));

	return (startToPoint - segment * alpha).Magnitude();
}

float math3d::CircleSDF(math3d::Vector<float, 2> center, float radius, math3d::Vector<float, 2> point)
{
	return (center - point).Magnitude() - radius;
}

float math3d::SphereSDF(math3d::Vector<float, 3> center, float radius, math3d::Vector<float, 3> point)
{
	return (center - point).Magnitude() - radius;
}