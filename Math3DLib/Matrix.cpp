#include "Matrix.h"
#include "Math3dUtil.h"
#include "Math3dException.h"
#include <iostream>

using namespace math3d;

template <typename T>
Matrix<T>::Matrix(const uint_t rows, const uint_t columns) : rows(rows), columns(columns)
{
	if (rows == 0 || columns == 0)
	{
		throw MatrixInvalidDimension();
	}
	
	try
	{
		this->values = new T[rows * columns];
	}
	catch (std::bad_alloc& ex)
	{
		this->CleanupMatrixData();

		std::cerr << "[!] " << ex.what() << std::endl;
	}

	for (uint_t i = 0; i < rows * columns; i++)
	{
		*(this->values + i) = 0;
	}
}

/* Caller is responsible for handling memory violation via out of bounds values pointer dereference */
template <typename T>
Matrix<T>::Matrix(const uint_t rows, const uint_t columns, const T* values) : Matrix(rows, columns)
{
	if (this->values == nullptr)
	{
		return;
	}

	for (uint_t i = 0; i < rows; i++)
	{
		for (uint_t j = 0; j < columns; j++)
		{
			*(this->values + i*columns + j) = *(values + i*columns + j);
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) : rows(m.rows), columns(m.columns)
{
	if (this->values != nullptr)
	{
		this->CleanupMatrixData();
	}

	try
	{
		this->values = new T[m.rows * m.columns];
	}
	catch (std::bad_alloc& ex)
	{
		this->CleanupMatrixData();

		std::cerr << "[!] " << ex.what() << std::endl;

		return;
	}

	for (uint_t i = 0; i < m.rows * m.columns; i++)
	{
		*(this->values + i) = *(m.values + i);
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	delete[] this->values;
	this->values = nullptr;
}

template <typename T>
void Matrix<T>::CleanupMatrixData()
{
	if (this->values != nullptr)
	{
		delete[] values;
		this->values = nullptr;
	}

	this->rows = 0;
	this->columns = 0;
}

template <typename T>
Matrix<T>* Matrix<T>::GetRow(const uint_t row) const
{
	if (row >= this->rows)
	{
		throw MatrixInvalidIndex();
	}

	try
	{
		Matrix<T>* ret = new Matrix<T>(1, this->columns);

		for (uint_t i = 0; i < this->columns; i++)
		{
			ret->SetValueAt(0, i, this->GetValueAt(row, i));
		}

		return ret;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::GetColumn(const uint_t column) const
{
	if (column >= this->columns)
	{
		throw MatrixInvalidIndex();
	}

	try
	{
		Matrix<T>* ret = new Matrix<T>(this->rows, 1);

		for (uint_t i = 0; i < this->rows; i++)
		{
			ret->SetValueAt(i, 0, this->GetValueAt(i, column));
		}

		return ret;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
void Matrix<T>::Transpose()
{
	uint_t counter = 1;
	T placeholder;

	for (uint_t i = 1; i < this->rows; i++, counter++)
	{
		for (uint_t j = 0; j < counter; j++)
		{
			placeholder = this->GetValueAt(i, j);
			this->SetValueAt(i, j, this->GetValueAt(j, i));
			this->SetValueAt(j, i, placeholder);
		}
	}
}

template <typename T>
void Matrix<T>::Negate()
{
	for (uint_t i = 0; i < this->rows; i++)
	{
		for (uint_t j = 0; j < this->columns; j++)
		{
			this->SetValueAt(i, j, -this->GetValueAt(i, j));
		}
	}
}


template <typename T>
bool Matrix<T>::Reverse()
{
	if (!this->IsSquare() || IsNearlyEqual(this->Determinant(), (T)0))
	{
		return false;
	}

	Matrix<T>* tmpMatrix = ReverseMatrix(*this);

	this->CleanupMatrixData();

	*this = *tmpMatrix;

	return true;
}

template <typename T>
Matrix<T>* Matrix<T>::Transpose(const Matrix<T>& matrix)
{
	try
	{
		Matrix<T>* ret = new Matrix<T>(matrix.rows, matrix.columns);

		uint_t counter = 0;

		for (uint_t i = 0; i < matrix.rows; i++, counter++)
		{
			ret->SetValueAt(i, i, matrix.GetValueAt(i, i));

			for (uint_t j = 0; j < counter; j++)
			{
				ret->SetValueAt(i, j, matrix.GetValueAt(j, i));
				ret->SetValueAt(j, i, matrix.GetValueAt(i, j));
			}
		}

		return ret;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::Negate(const Matrix<T>& matrix)
{
	try
	{
		Matrix<T>* ret = new Matrix<T>(matrix.rows, matrix.columns);

		for (uint_t i = 0; i < matrix.rows; i++)
		{
			for (uint_t j = 0; j < matrix.columns; j++)
			{
				ret->SetValueAt(i, j, -matrix.GetValueAt(i, j));
			}
		}

		return ret;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::ReverseMatrix(const Matrix<T>& matrix)
{
	T det = matrix.Determinant();

	if (!matrix.IsSquare() || IsNearlyEqual(det, (T)0))
	{
		return nullptr;
	}

	Matrix<T>* ret = matrix.AdjugateMatrix(matrix);

	*ret *= 1.0 / (double)det;

	return ret;
}

template <typename T>
Matrix<T>* Matrix<T>::CofactorMatrix(const Matrix<T>& matrix)
{
	if (!matrix.IsSquare())
	{
		return nullptr;
	}

	try
	{
		Matrix<T>* ret = new Matrix<T>(matrix.rows, matrix.columns);

		if (matrix.rows == 1)
		{
			ret->SetValueAt(0, 0, 1);

			return ret;
		}

		Matrix<T>* submatrix;
		Matrix<T>* tmpReference;

		for (uint_t i = 0; i < matrix.rows; i++)
		{
			for (uint_t j = 0; j < matrix.columns; j++)
			{
				tmpReference = matrix.GetWithRemovedRows(i, i);
				submatrix = tmpReference->GetWithRemovedColumns(j, j);

				T value = submatrix->Determinant();
				value *= (i+j) % 2 == 0 ? 1 : -1;

				ret->SetValueAt(i, j, value);

				delete tmpReference;
				delete submatrix;
			}
		}

		return ret;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::AdjugateMatrix(const Matrix<T>& matrix)
{
	Matrix<T>* ret = CofactorMatrix(matrix);
	
	ret->Transpose();
	
	return ret;
}

template <typename T>
Matrix<T>* Matrix<T>::GetWithRemovedRows(const uint_t row_s, const uint_t row_e) const
{
	if (row_s >= this->rows ||
		row_e >= this->rows ||
		row_s > row_e)
	{
		throw MatrixInvalidIndex();
	}

	try
	{
		uint_t rowCount = this->rows - (row_e - row_s + 1);
		Matrix<T>* submatrix = new Matrix<T>(rowCount, this->columns);

		uint_t targetRow = 0;
		for (uint_t i = 0; i < submatrix->rows; i++, targetRow++)
		{
			for (uint_t j = 0; j < submatrix->columns; j++)
			{
				while (targetRow >= row_s && targetRow <= row_e)
				{
					targetRow++;
				}

				submatrix->SetValueAt(i, j, this->GetValueAt(targetRow, j));
			}
		}

		return submatrix;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::GetWithRemovedColumns(const uint_t column_s, const uint_t column_e) const
{
	if (column_s >= this->columns ||
		column_e >= this->columns ||
		column_s > column_e)
	{
		throw MatrixInvalidIndex();
	}
	
	try
	{
		uint_t colCount = this->columns - (column_e - column_s + 1);
		Matrix<T>* submatrix = new Matrix<T>(this->rows, colCount);
		
		for (uint_t i = 0; i < submatrix->rows; i++)
		{
			uint_t targetCol = 0;

			for (uint_t j = 0; j < submatrix->columns; j++, targetCol++)
			{
				while (targetCol >= column_s && targetCol <= column_e)
				{
					targetCol++;
				}
				
				submatrix->SetValueAt(i, j, this->GetValueAt(i, targetCol));
			}
		}

		return submatrix;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;

		return nullptr;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::GetSubmatrix(const uint_t row_s, const uint_t column_s, const uint_t row_e, const uint_t column_e) const
{
	if (row_s >= this->rows || column_s >= this->columns ||
		row_e >= this->rows || column_e >= this->columns ||
		row_s > row_e || column_s > column_e)
	{
		throw MatrixInvalidIndex();
	}

	uint_t rowCount = row_e - row_s + 1;
	uint_t colCount = column_e - column_s + 1;
	try 
	{
		Matrix<T>* submatrix = new Matrix<T>(rowCount, colCount);
		
		for (uint_t i = 0; i < rowCount; i++)
		{
			for (uint_t j = 0; j < colCount; j++)
			{
				submatrix->SetValueAt(i, j, this->GetValueAt(row_s + i, column_s + j));
			}
		}

		return submatrix;
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << ex.what() << std::endl;
		
		return nullptr;
	}
}

template <typename T>
T Matrix<T>::Determinant() const
{
	if (!this->IsSquare())
	{
		throw MatrixNoSquare();
	}

	if (this->rows == 1)
	{
		return this->GetValueAt(0, 0);
	}

	if (this->rows == 2)
	{
		return this->GetValueAt(0, 0) * this->GetValueAt(1, 1) - this->GetValueAt(0, 1) * this->GetValueAt(1, 0);
	}
	else
	{
		T determinant = 0;

		Matrix<T>* submatrix = nullptr;
		Matrix<T>* tmpReference;

		for (uint_t i = 0; i < this->columns; i++)
		{
			if (IsNearlyEqual(this->GetValueAt(0, i), 0))
			{
				continue;
			}

			double value = this->GetValueAt(0, i);
			value *= ((i + 2) % 2) == 0 ? 1 : -1;

			submatrix = this->GetWithRemovedRows(0, 0);
			tmpReference = submatrix;					//	Avoid memory leaks
			submatrix = submatrix->GetWithRemovedColumns(i, i);
			delete tmpReference;

			determinant += value * submatrix->Determinant();
		}
		
		delete submatrix;

		return determinant;
	}
}

template <typename T>
Matrix<T>* Matrix<T>::CreateIdentity(const uint_t size)
{
	Matrix<T> *identity = new Matrix<T>(size, size);

	for (uint_t i = 0; i < size; i++)
	{
		for (uint_t j = 0; j < size; j++)
		{
			identity->SetValueAt(i, j, (T)(i == j ? 1 : 0));
		}
	}

	return identity;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
	if (m.rows != this->rows || m.columns != this->columns)
	{
		throw MatrixInvalidDimension();
	}

	for (uint_t i = 0; i < this->rows; i++)
	{
		for (uint_t j = 0; j < this->columns; j++)
		{
			SetValueAt(i, j, this->GetValueAt(i, j) + m.GetValueAt(i, j));
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
	if (m.rows != this->rows || m.columns != this->columns)
	{
		throw MatrixInvalidDimension();
	}

	for (uint_t i = 0; i < this->rows; i++)
	{
		for (uint_t j = 0; j < this->columns; j++)
		{
			SetValueAt(i, j, this->GetValueAt(i, j) - m.GetValueAt(i, j));
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m)
{
	if (this->columns != m.rows)
	{
		throw MatrixInvalidDimension();
	}

	Matrix<T> resMatrix(this->rows, m.columns);

	for (uint_t i = 0; i < resMatrix.rows; i++)
	{
		for (uint_t j = 0; j < resMatrix.columns; j++)
		{
			Matrix<T>* tmpA = this->GetRow(i);
			Matrix<T>* tmpB = m.GetColumn(j);

			T sum = (T)0;
			for (uint_t x = 0; x < this->columns; x++)
			{
				sum += tmpA->GetValueAt(0, x) * tmpB->GetValueAt(x, 0);
			}

			resMatrix.SetValueAt(i, j, sum);

			tmpA->CleanupMatrixData();
			tmpB->CleanupMatrixData();
		}
	}

	this->CleanupMatrixData();
	*this = resMatrix;
	resMatrix.values = nullptr;
	
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const double& scalar)
{
	for (uint_t i = 0; i < this->rows; i++)
	{
		for (uint_t j = 0; j < this->columns; j++)
		{
			this->SetValueAt(i, j, (T)((double)this->GetValueAt(i, j) * scalar));
		}
	}

	return *this;
}

/* Kinda dirty but works for now */
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const float& scalar)
{
	return (*this *= (double)scalar);
}

/* Even more dirty */
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const int& scalar)
{
	return (*this *= (double)scalar);
}

/* Even more dirty */
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const uint_t& scalar)
{
	return (*this *= (double)scalar);
}

template <typename T>
Matrix<T>* Matrix<T>::operator[](const int index) const
{
	if (this->rows == 1)
	{
		if (this->columns <= index)
		{
			throw MatrixInvalidIndex();
		}

		return this->GetColumn(index);
	}

	if (this->rows <= index)
	{
		throw MatrixInvalidIndex();
	}

	return this->GetRow(index);
}

/* Enforce numeric types */
//// We do not allow int matrices for now, until the solution
//// for the reverse matrix problem has been decided
// template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;