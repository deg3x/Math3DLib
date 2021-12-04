#include "matrix.h"
#include "math3dutil.h"
#include "math3dexceptions.h"
#include <iostream>

using namespace math3d;

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>::Matrix()
{
	for (uint_t i = 0; i < R * C; i++)
	{
		*(this->values + i) = (T)0;
	}
}

/* Caller is responsible for handling memory violation via out of bounds values pointer dereference */
template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>::Matrix(const T* values)
{
	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			*(this->values + i*C + j) = *(values + i*C + j);
		}
	}
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& m)
{
	for (uint_t i = 0; i < R * C; i++)
	{
		*(this->values + i) = *(m.values + i);
	}
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, 1, C> Matrix<T, R, C>::GetRow(const uint_t row) const
{
	if (row >= R)
	{
		throw MatrixInvalidIndex();
	}

	Matrix<T, 1, C> ret;

	for (uint_t i = 0; i < C; i++)
	{
		ret.SetValueAt(0, i, this->GetValueAt(row, i));
	}

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, 1> Matrix<T, R, C>::GetColumn(const uint_t column) const
{
	if (column >= C)
	{
		throw MatrixInvalidIndex();
	}

	Matrix<T, R, 1> ret;

	for (uint_t i = 0; i < R; i++)
	{
		ret.SetValueAt(i, 0, this->GetValueAt(i, column));
	}

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
void Matrix<T, R, C>::Negate()
{
	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			this->SetValueAt(i, j, -this->GetValueAt(i, j));
		}
	}
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, C, R> Matrix<T, R, C>::Transpose(const Matrix<T, R, C>& matrix)
{
	Matrix<T, C, R> ret;

	uint_t counter = 0;

	for (uint_t i = 0; i < R; i++, counter++)
	{
		ret.SetValueAt(i, i, matrix.GetValueAt(i, i));

		for (uint_t j = 0; j < counter; j++)
		{
			ret.SetValueAt(i, j, matrix.GetValueAt(j, i));
			ret.SetValueAt(j, i, matrix.GetValueAt(i, j));
		}
	}

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C> Matrix<T, R, C>::Negate(const Matrix<T, R, C>& matrix)
{
	Matrix<T, R, C> ret;

	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			ret.SetValueAt(i, j, -matrix.GetValueAt(i, j));
		}
	}

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, C, R> Matrix<T, R, C>::ReverseMatrix(const Matrix<T, R, C>& matrix)
{
	T det = matrix.Determinant();

	if (!matrix.IsSquare() || IsNearlyEqual(det, (T)0))
	{
		throw MatrixNonReversible();
	}

	Matrix<T, C, R> ret = matrix.AdjugateMatrix(matrix);

	ret *= (T)1 / (T)det;

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C> Matrix<T, R, C>::CofactorMatrix(const Matrix<T, R, C>& matrix)
{
	if (!matrix.IsSquare())
	{
		throw MatrixNoSquare();
	}

	Matrix<T, R, C> ret;

	if (R == 1)
	{
		ret.SetValueAt(0, 0, 1);

		return ret;
	}

	Matrix<T, R-1, C-1> submatrix;

	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			submatrix = matrix.GetWithRemovedRow(i).GetWithRemovedColumn(j);

			T value = submatrix.Determinant();
			value *= (i + j) % 2 == 0 ? 1 : -1;

			ret.SetValueAt(i, j, value);
		}
	}

	return ret;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, C, R> Matrix<T, R, C>::AdjugateMatrix(const Matrix<T, R, C>& matrix)
{
	Matrix<T, R, C> ret = CofactorMatrix(matrix);
	
	return Transpose(ret);
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R-1, C> Matrix<T, R, C>::GetWithRemovedRow(const uint_t row) const
{
	if (row >= R)
	{
		throw MatrixInvalidIndex();
	}

	Matrix<T, R - 1, C> submatrix;

	uint_t targetRow = 0;
	for (uint_t i = 0; i < R-1; i++, targetRow++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			if (targetRow == row)
			{
				targetRow++;
			}

			submatrix.SetValueAt(i, j, this->GetValueAt(targetRow, j));
		}
	}

	return submatrix;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C-1> Matrix<T, R, C>::GetWithRemovedColumn(const uint_t column) const
{
	if (column >= C)
	{
		throw MatrixInvalidIndex();
	}

	Matrix<T, R, C-1> submatrix;

	for (uint_t i = 0; i < R; i++)
	{
		uint_t targetCol = 0;

		for (uint_t j = 0; j < C-1; j++, targetCol++)
		{
			if (targetCol == column)
			{
				targetCol++;
			}

			submatrix.SetValueAt(i, j, this->GetValueAt(i, targetCol));
		}
	}

	return submatrix;
}

template <typename T, uintm_t R, uintm_t C>
T Matrix<T, R, C>::Determinant() const
{
	if (!this->IsSquare())
	{
		throw MatrixNoSquare();
	}

	if (R == 1)
	{
		return this->GetValueAt(0, 0);
	}

	if (R == 2)
	{
		return this->GetValueAt(0, 0) * this->GetValueAt(1, 1) - this->GetValueAt(0, 1) * this->GetValueAt(1, 0);
	}
	else
	{
		T determinant = 0;

		Matrix<T, R-1, C-1> submatrix;
		for (uint_t i = 0; i < C; i++)
		{
			if (IsNearlyEqual(this->GetValueAt(0, i), 0))
			{
				continue;
			}
			
			T value = this->GetValueAt(0, i);
			value *= ((i + 2) % 2) == 0 ? 1 : -1;
			
			submatrix = this->GetWithRemovedRow(0).GetWithRemovedColumn(i);
			
			determinant += value * submatrix.Determinant();
		}

		return determinant;
	}
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C> Matrix<T, R, C>::CreateIdentity()
{
	if (R != C) 
	{
		throw MatrixInvalidDimension();
	}

	Matrix<T, R, C> identity;

	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			identity.SetValueAt(i, j, (T)(i == j ? 1 : 0));
		}
	}

	return identity;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator+=(const Matrix<T, R, C>& m)
{
	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			SetValueAt(i, j, this->GetValueAt(i, j) + m.GetValueAt(i, j));
		}
	}

	return *this;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator-=(const Matrix<T, R, C>& m)
{
	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			SetValueAt(i, j, this->GetValueAt(i, j) - m.GetValueAt(i, j));
		}
	}

	return *this;
}

template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(double scalar)
{
	for (uint_t i = 0; i < R; i++)
	{
		for (uint_t j = 0; j < C; j++)
		{
			this->SetValueAt(i, j, (T)((double)this->GetValueAt(i, j) * scalar));
		}
	}

	return *this;
}

/* Kinda dirty but works for now */
template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(float scalar)
{
	return (*this *= (double)scalar);
}

/* Even more dirty */
template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(int scalar)
{
	return (*this *= (double)scalar);
}

/* Even more dirty */
template <typename T, uintm_t R, uintm_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(uint_t scalar)
{
	return (*this *= (double)scalar);
}

/* Enforce numeric types */
// We only allow float Matrices for now
template class Matrix<float, 1, 2>;
template class Matrix<float, 1, 3>;
template class Matrix<float, 1, 4>;
template class Matrix<float, 2, 1>;
template class Matrix<float, 2, 2>;
template class Matrix<float, 2, 3>;
template class Matrix<float, 2, 4>;
template class Matrix<float, 3, 1>;
template class Matrix<float, 3, 2>;
template class Matrix<float, 3, 3>;
template class Matrix<float, 3, 4>;
template class Matrix<float, 4, 1>;
template class Matrix<float, 4, 2>;
template class Matrix<float, 4, 3>;
template class Matrix<float, 4, 4>;