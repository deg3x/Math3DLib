#pragma once
#include "math3dexceptions.h"
#include <iostream>

namespace math3d
{
	typedef unsigned int uint_t;

	template <typename T, uint_t S>
	class Vector
	{
	protected:
		T values[S];

	public:
		Vector();
		Vector(const T* const values);
		Vector(const Vector<T, S>& vec);
		~Vector() {}

		T Magnitude() const;
		void Normalize();
		bool IsNormalized() const;
		T DotProduct(const Vector<T, S>& vector) const;

		static Vector<T, S> Normalize(const Vector<T, S>& vec);
		static T DotProduct(const Vector<T, S>& vectorA, const Vector<T, S>& vectorB);
		static Vector<T, S> CrossProduct(const Vector<T, S>& vectorA, const Vector<T, S>& vectorB);

		Vector<T, S>& operator=(Vector<T, S> v);
		Vector<T, S>& operator+=(const Vector<T, S>& v);
		Vector<T, S>& operator-=(const Vector<T, S>& v);
		T operator[](const int index) const;

		inline T GetValueAt(const uint_t index) const
		{
			if (index >= S)
			{
				throw VectorInvalidIndex();
			}

			return *(values + index);
		}

		inline void SetValueAt(const uint_t index, const T value)
		{
			if (index >= S)
			{
				throw VectorInvalidIndex();
			}

			*(values + index) = value;
		}

		friend void Swap(Vector<T, S>& vectorA, Vector<T, S>& vectorB)
		{
			std::swap(vectorA.values, vectorB.values);
		}

		friend std::ostream& operator<<(std::ostream& out, const Vector& v)
		{
			out << std::endl;

			out << "V(";
			for (int i = 0; i < S; i++)
			{
				out << v.GetValueAt(i);
				if (i != (S - 1))
				{
					out << ", ";
				}
			}

			out << ")" << std::endl;

			return out;
		}
	};

	template <typename T, uint_t S>
	Vector<T, S> operator+(Vector<T, S> vectorA, const Vector<T, S>& vectorB)
	{
		return vectorA += vectorB;
	}

	template <typename T, uint_t S>
	Vector<T, S> operator-(Vector<T, S> vectorA, const Vector<T, S>& vectorB)
	{
		return vectorA -= vectorB;
	}
}