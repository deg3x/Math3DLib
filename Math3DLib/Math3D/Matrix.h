#pragma once
#include "Math3dException.h"
#include <iostream>

namespace math3d
{
	typedef unsigned int uint_t;

	template <typename T>
	class Matrix
	{
	protected:
		T* values = nullptr;
		uint_t rows;
		uint_t columns;

	public:
		Matrix() {}
		Matrix(const uint_t rows, const uint_t columns);
		Matrix(const uint_t rows, const uint_t columns, const T* values);
		Matrix(const Matrix<T>& m);
		virtual ~Matrix();

		void CleanupMatrixData();

		Matrix<T> GetRow(const uint_t row) const;												//
		Matrix<T> GetColumn(const uint_t column) const;											//
		Matrix<T> GetWithRemovedRows(const uint_t row_s, const uint_t row_e) const;				//
		Matrix<T> GetWithRemovedColumns(const uint_t column_s, const uint_t column_e) const;	//
		Matrix<T> GetSubmatrix(const uint_t row_s, const uint_t column_s, const uint_t row_e, const uint_t column_e) const;	//
		T Determinant() const;
		void Transpose();
		void Negate();
		bool Reverse();

		static Matrix<T> Transpose(const Matrix<T>& matrix);		//
		static Matrix<T> Negate(const Matrix<T>& matrix);			//
		static Matrix<T> ReverseMatrix(const Matrix<T>& matrix);	//
		static Matrix<T> CofactorMatrix(const Matrix<T>& matrix);	//
		static Matrix<T> AdjugateMatrix(const Matrix<T>& matrix);	//
		static Matrix<T> CreateIdentity(const uint_t size);			//

		Matrix<T>& operator+=(const Matrix<T>& m);
		Matrix<T>& operator-=(const Matrix<T>& m);
		Matrix<T>& operator*=(const Matrix<T>& m);
		Matrix<T>& operator*=(const double& scalar);
		Matrix<T>& operator*=(const float& scalar);
		Matrix<T>& operator*=(const int& scalar);
		Matrix<T>& operator*=(const uint_t& scalar);
		/*Matrix<T>& operator[](const int index);
		const Matrix<T>& operator[](const int index) const;*/
		
		inline bool IsSquare() const
		{
			return (rows == columns);
		}

		inline uint_t GetNumberOfRows() const
		{
			return rows;
		}

		inline uint_t GetNumberOfColumns() const
		{
			return columns;
		}

		inline T GetValueAt(const uint_t row, const uint_t column) const
		{
			if (row >= rows || column >= columns)
			{
				throw MatrixInvalidIndex();
			}

			return *(values + row * columns + column);
		}

		inline void SetValueAt(const uint_t row, const uint_t column, const T value)
		{
			if (row >= rows || column >= columns)
			{
				throw MatrixInvalidIndex();
			}

			*(values + row * columns + column) = value;
		}

		friend std::ostream& operator<<(std::ostream& out, const Matrix& m)
		{
			if (m.values == nullptr)
			{
				return out;
			}

			out << std::endl;

			for (int i = 0; i < m.rows; i++)
			{
				out << "|\t";
				for (int j = 0; j < m.columns; j++)
				{
					out << *(m.values + i*m.columns + j) << "\t";
				}
				out << "|" << std::endl;
			}

			out << std::endl;

			return out;
		}
	};

	template <typename T>
	Matrix<T> operator+(Matrix<T> matrixA, const Matrix<T>& matrixB)
	{
		return matrixA += matrixB;
	}

	template <typename T>
	Matrix<T> operator-(Matrix<T> matrixA, const Matrix<T>& matrixB)
	{
		return matrixA -= matrixB;
	}

	template <typename T>
	Matrix<T> operator*(Matrix<T> matrix, const double& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T>
	Matrix<T> operator*(Matrix<T> matrix, const float& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T>
	Matrix<T> operator*(Matrix<T> matrix, const int& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T>
	Matrix<T> operator*(Matrix<T> matrix, const uint_t& scalar)
	{
		return matrix *= scalar;
	}
}
