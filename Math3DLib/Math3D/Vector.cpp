#include "Vector.h"
#include "Math3dUtil.h"
#include "Math3dException.h"
#include <iostream>

using namespace math3d;

template <typename T>
Vector<T>::Vector(uint_t size) : size(size)
{
	if (size == 0)
	{
		throw VectorInvalidSize();
	}

	try
	{
		this->values = new T[size];
	}
	catch (std::bad_alloc& ex)
	{
		this->CleanupVectorData();
		std::cerr << ex.what();
	}
}

template <typename T>
Vector<T>::Vector(uint_t size, const T* const values) : Vector(size)
{
	if (this->values == nullptr)
	{
		return;
	}
	
	for (int i = 0; i < size; i++)
	{
		*(this->values + i) = *(values + i);
	}
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v) : size(v.size)
{
	if (this->values != nullptr)
	{
		this->CleanupVectorData();
	}

	try
	{
		values = new T[size];
	}
	catch (std::bad_alloc& ex)
	{
		this->CleanupVectorData();

		std::cerr << ex.what();

		return;
	}

	for (int i = 0; i < v.size; i++)
	{
		*(this->values + i) = *(v.values + i);
	}
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] this->values;
	this->values = nullptr;
}

template <typename T>
T Vector<T>::Magnitude() const
{
	T len = 0.0;

	for (int i = 0; i < this->size; i++)
	{
		len += this->GetValueAt(i) * this->GetValueAt(i);
	}

	return sqrt(len);
}

template <typename T>
void Vector<T>::Normalize()
{
	double len = this->Magnitude();

	for (int i = 0; i < this->size; i++)
	{
		*(this->values + i) /= len;
	}
}

template <typename T>
bool Vector<T>::IsNormalized() const
{
	return IsNearlyEqual(this->Magnitude(), (T)1) ? true : false;
}

template <typename T>
void Vector<T>::CleanupVectorData()
{
	if (this->values != nullptr)
	{
		delete[] this->values;
		this->values = nullptr;
	}

	size = 0;
}

template <typename T>
Vector<T> Vector<T>::Normalize(const Vector<T>& vec)
{
	double len = vec.Magnitude();
	Vector<T> ret(vec.size);

	for (int i = 0; i < ret.size; i++)
	{
		ret.SetValueAt(i, vec.GetValueAt(i) / len);
	}

	return ret;
}

template <typename T>
T Vector<T>::DotProduct(const Vector<T>& vector) const
{
	if (this->size != vector.size)
	{
		throw VectorInvalidSize();
	}

	T dot = 0;

	for (uint_t i = 0; i < this->size; i++)
	{
		dot += this->GetValueAt(i) * vector.GetValueAt(i);
	}

	return dot;
}

template <typename T>
T Vector<T>::DotProduct(const Vector<T>& vectorA, const Vector<T>& vectorB)
{
	if (vectorA.size != vectorB.size)
	{
		throw VectorInvalidSize();
	}

	T dot = 0;

	for (uint_t i = 0; i < vectorA.size; i++)
	{
		dot += vectorA.GetValueAt(i) * vectorB.GetValueAt(i);
	}

	return dot;
}

template <typename T>
Vector<T> Vector<T>::CrossProduct(const Vector<T>& vectorA, const Vector<T>& vectorB)
{
	if (vectorA.size != vectorB.size)
	{
		throw VectorInvalidSize();
	}

	if (vectorA.size > 3 || vectorA.size <= 1)
	{
		throw VectorInvalidSize();
	}

	Vector<T> ret;

	if (vectorA.size == 2)
	{
		ret = Vector<T>(1);

		T vals[] = { -vectorA.GetValueAt(1), vectorA.GetValueAt(0) };
		Vector<T> perp(2, vals);

		ret.SetValueAt(0, DotProduct(perp, vectorB));
	}
	else
	{
		ret = Vector<T>(vectorA.size);

		ret.SetValueAt(0, (vectorA.GetValueAt(0) * vectorB.GetValueAt(2)) - (vectorA.GetValueAt(2) * vectorB.GetValueAt(0)));
		ret.SetValueAt(1, -(vectorA.GetValueAt(1) * vectorB.GetValueAt(2)) - (vectorA.GetValueAt(2) * vectorB.GetValueAt(1)));
		ret.SetValueAt(2, (vectorA.GetValueAt(0) * vectorB.GetValueAt(1)) - (vectorA.GetValueAt(1) * vectorB.GetValueAt(0)));
	}

	return ret;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& v)
{
	if (v.size != this->size)
	{
		throw VectorInvalidSize();
	}

	for (int i = 0; i < size; i++)
	{
		this->SetValueAt(i, this->GetValueAt(i) + v.GetValueAt(i));
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& v)
{
	if (v.size != this->size)
	{
		throw VectorInvalidSize();
	}

	for (int i = 0; i < size; i++)
	{
		this->SetValueAt(i, this->GetValueAt(i) - v.GetValueAt(i));
	}

	return *this;
}

template <typename T>
T Vector<T>::operator[](const int index) const
{
	if (this->size <= index)
	{
		throw VectorInvalidIndex();
	}

	return this->GetValueAt(index);
}

/* Enforce numeric types */
//template class Vector<int>;
template class Vector<float>;
template class Vector<double>;