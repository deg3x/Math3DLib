# Math3DLib
 A flexible and easy to use 3D mathematics library for C++.\
 I created this while practicing my 3D math knowledge and I'm using it for game dev tests and practice.
 
 ## Supported Features
 * NxM dimension `Matrix` types and complete functionality
 * N size `Vector` types and complete functionality
 * `Quaternion` type and functionality
 * Rotations and `Slerp` functionality based on quaternions
 * Helper types `Vector2`, `Vector3`, `Vector4`, `Matrix2x2`, `Matrix3x3`, `Matrix4x4`
 * Hardware based fast `sqrt` implementation
 * Custom exceptions
 * Basic math operations (`Abs`, `RadToDeg`, `DegToRad`, float comparison)
 * `cmath` based trigonometric functions sin/cos/asin/acos (for now)

## To Do
* Provide our own implementation of sin/cos/asin/acos
* Create interpolation functionality (Linear/Easy in/Easy out/etc)
* Create solvers for 3D primitives equations passing through points
* Create intersection solvers for 3D primitives (Plane/Sphere/Line)
* Create solvers for parametric equations and curves
* Add functionality documentation and example usage

## Feedback
While creating this library I did my best to make the code bug free and ensure memory safety.\
However, no code is bug free :)\
If you find any bugs or you have a feature to suggest please contact me at mpenos.ks@gmail.com\
and I will work on it as soon as possible.

## License
The MIT License (MIT)