#pragma once
#include "Math3dException.h"
#include <iostream>

namespace math3d
{
	typedef unsigned int uint_t;

	template <typename T>
	class Vector
	{
	protected:
		T* values = nullptr;
		uint_t size;

	public:
		Vector() {}
		Vector(uint_t size);
		Vector(uint_t size, const T* const values);
		Vector(const Vector<T>& vec);
		virtual ~Vector();

		T Magnitude() const;
		void Normalize();
		bool IsNormalized() const;
		void CleanupVectorData();
		T DotProduct(const Vector<T>& vector) const;

		static Vector<T> Normalize(const Vector<T>& vec);
		static T DotProduct(const Vector<T>& vectorA, const Vector<T>& vectorB);
		static Vector<T> CrossProduct(const Vector<T>& vectorA, const Vector<T>& vectorB);

		Vector<T>& operator=(Vector<T> v);
		Vector<T>& operator+=(const Vector<T>& v);
		Vector<T>& operator-=(const Vector<T>& v);
		T operator[](const int index) const;

		inline T GetValueAt(const uint_t index) const
		{
			if (index >= size)
			{
				throw VectorInvalidIndex();
			}

			return *(values + index);
		}

		inline void SetValueAt(const uint_t index, const T value)
		{
			if (index >= size)
			{
				throw VectorInvalidIndex();
			}

			*(values + index) = value;
		}

		friend void Swap(Vector<T>& vectorA, Vector<T>& vectorB)
		{
			std::swap(vectorA.size, vectorB.size);
			std::swap(vectorA.values, vectorB.values);
		}

		friend std::ostream& operator<<(std::ostream& out, const Vector& v)
		{
			if (v.values == nullptr)
			{
				return out;
			}

			out << std::endl;

			out << "V(";
			for (int i = 0; i < v.size; i++)
			{
				out << v.GetValueAt(i);
				if (i != (v.size - 1))
				{
					out << ", ";
				}
			}

			out << ")" << std::endl;

			return out;
		}
	};

	template <typename T>
	Vector<T> operator+(Vector<T> vectorA, const Vector<T>& vectorB)
	{
		return vectorA += vectorB;
	}

	template <typename T>
	Vector<T> operator-(Vector<T> vectorA, const Vector<T>& vectorB)
	{
		return vectorA -= vectorB;
	}
}