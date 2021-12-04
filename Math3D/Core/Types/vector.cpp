#include "vector.h"
#include "math3dutil.h"
#include "math3dexceptions.h"
#include <iostream>

using namespace math3d;

template <typename T, uint_t S>
Vector<T, S>::Vector()
{
	if (S == 0)
	{
		throw VectorInvalidSize();
	}

	for (int i = 0; i < S; i++)
	{
		*(this->values + i) = (T)0;
	}
}

template <typename T, uint_t S>
Vector<T, S>::Vector(const T* const values)
{	
	if (S == 0)
	{
		throw VectorInvalidSize();
	}

	for (int i = 0; i < S; i++)
	{
		*(this->values + i) = *(values + i);
	}
}

template <typename T, uint_t S>
Vector<T, S>::Vector(const Vector<T, S>& v)
{
	for (int i = 0; i < S; i++)
	{
		*(this->values + i) = *(v.values + i);
	}
}

template <typename T, uint_t S>
T Vector<T, S>::Magnitude() const
{
	T len = (T)0;

	for (int i = 0; i < S; i++)
	{
		len += this->GetValueAt(i) * this->GetValueAt(i);
	}

	return sqrt(len);
}

template <typename T, uint_t S>
void Vector<T, S>::Normalize()
{
	T len = this->Magnitude();

	for (int i = 0; i < S; i++)
	{
		*(this->values + i) /= len;
	}
}

template <typename T, uint_t S>
bool Vector<T, S>::IsNormalized() const
{
	return IsNearlyEqual(this->Magnitude(), (T)1) ? true : false;
}

template <typename T, uint_t S>
Vector<T, S> Vector<T, S>::Normalize(const Vector<T, S>& vec)
{
	T len = vec.Magnitude();
	Vector<T, S> ret;

	for (int i = 0; i < S; i++)
	{
		ret.SetValueAt(i, vec.GetValueAt(i) / len);
	}

	return ret;
}

template <typename T, uint_t S>
T Vector<T, S>::DotProduct(const Vector<T, S>& vector) const
{
	T dot = 0;

	for (uint_t i = 0; i < S; i++)
	{
		dot += this->GetValueAt(i) * vector.GetValueAt(i);
	}

	return dot;
}

template <typename T, uint_t S>
T Vector<T, S>::DotProduct(const Vector<T, S>& vectorA, const Vector<T, S>& vectorB)
{
	T dot = 0;

	for (uint_t i = 0; i < S; i++)
	{
		dot += vectorA.GetValueAt(i) * vectorB.GetValueAt(i);
	}

	return dot;
}

template <typename T, uint_t S>
Vector<T, S> Vector<T, S>::CrossProduct(const Vector<T, S>& vectorA, const Vector<T, S>& vectorB)
{
	if (S > 3 || S <= 1)
	{
		throw VectorInvalidSize();
	}

	if (S == 2)
	{
		Vector<T, S> ret;

		T vals[] = { -vectorA.GetValueAt(1), vectorA.GetValueAt(0) };
		Vector<T, S> perp(vals);

		ret.SetValueAt(0, DotProduct(perp, vectorB));

		return ret;
	}
	else
	{
		Vector<T, S> ret;

		ret.SetValueAt(0,  (vectorA.GetValueAt(1) * vectorB.GetValueAt(2)) - (vectorA.GetValueAt(2) * vectorB.GetValueAt(1)));
		ret.SetValueAt(1, -((vectorA.GetValueAt(0) * vectorB.GetValueAt(2)) - (vectorA.GetValueAt(2) * vectorB.GetValueAt(0))));
		ret.SetValueAt(2,  (vectorA.GetValueAt(0) * vectorB.GetValueAt(1)) - (vectorA.GetValueAt(1) * vectorB.GetValueAt(0)));

		return ret;
	}
}

template <typename T, uint_t S>
Vector<T, S>& Vector<T, S>::operator=(Vector<T, S> v)
{
	Swap(*this, v);

	return *this;
}

template <typename T, uint_t S>
Vector<T, S>& Vector<T, S>::operator+=(const Vector<T, S>& v)
{
	for (int i = 0; i < S; i++)
	{
		this->SetValueAt(i, this->GetValueAt(i) + v.GetValueAt(i));
	}

	return *this;
}

template <typename T, uint_t S>
Vector<T, S>& Vector<T, S>::operator-=(const Vector<T, S>& v)
{
	for (int i = 0; i < S; i++)
	{
		this->SetValueAt(i, this->GetValueAt(i) - v.GetValueAt(i));
	}

	return *this;
}

template <typename T, uint_t S>
Vector<T, S>& Vector<T, S>::operator*=(const float& scalar)
{
	for (int i = 0; i < S; i++)
	{
		this->SetValueAt(i, this->GetValueAt(i) * scalar);
	}

	return *this;
}

template <typename T, uint_t S>
T Vector<T, S>::operator[](const int index) const
{
	if (S <= index)
	{
		throw VectorInvalidIndex();
	}

	return this->GetValueAt(index);
}

/* Enforce numeric types */
template class Vector<float, 1>;
template class Vector<float, 2>;
template class Vector<float, 3>;
template class Vector<float, 4>;
template class Vector<double, 1>;
template class Vector<double, 2>;
template class Vector<double, 3>;
template class Vector<double, 4>;