#pragma once

float CircleSDF(math3d::Vector<float, 2> center, float radius, math3d::Vector<float, 2> point);
float SphereSDF(math3d::Vector<float, 3> center, float radius, math3d::Vector<float, 3> point);