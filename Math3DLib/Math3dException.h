#pragma once
#include <iostream>

namespace math3d
{
	class MathException : public std::exception
	{
	public:
		MathException() {}
		virtual const char* what() const noexcept override
		{
			return "Math library generic exception";
		}
	};

	class MatrixInvalidDimension : public MathException
	{
	public:
		MatrixInvalidDimension() {}
		virtual const char* what() const noexcept override
		{
			return "Invalid matrix dimension";
		}
	};

	class MatrixInvalidIndex : public MathException
	{
	public:
		MatrixInvalidIndex() {}
		virtual const char* what() const noexcept override
		{
			return "Invalid matrix indexing";
		}
	};

	class MatrixNoSquare : public MathException
	{
	public:
		MatrixNoSquare() {}
		virtual const char* what() const noexcept override
		{
			return "Matrix is not square";
		}
	};

	class VectorInvalidSize : public MathException
	{
	public:
		VectorInvalidSize() {}
		virtual const char* what() const noexcept override
		{
			return "Invalid vector size";
		}
	};

	class VectorInvalidIndex : public MathException
	{
	public:
		VectorInvalidIndex() {}
		virtual const char* what() const noexcept override
		{
			return "Invalid vector indexing";
		}
	};
}
