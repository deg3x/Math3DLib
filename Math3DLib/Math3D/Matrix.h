#pragma once
#include "Math3dException.h"
#include <iostream>
//#include <cstdint>

namespace math3d
{
	typedef unsigned int uint_t;
	typedef unsigned char uintm_t;

	template <typename T, uintm_t R, uintm_t C>
	class Matrix
	{
	protected:
		T values[R * C];

	public:
		Matrix();
		Matrix(const T* values);
		Matrix(const Matrix<T, R, C>& m);
		virtual ~Matrix() {}

		Matrix<T, 1, C> GetRow(const uint_t row) const;
		Matrix<T, R, 1> GetColumn(const uint_t column) const;
		Matrix<T, R-1, C> GetWithRemovedRow(const uint_t row) const;
		Matrix<T, R, C-1> GetWithRemovedColumn(const uint_t column) const;
		//Matrix<T> GetSubmatrix(const uint_t row_s, const uint_t column_s, const uint_t row_e, const uint_t column_e) const;
		T Determinant() const;
		void Negate();

		static Matrix<T, C, R> Transpose(const Matrix<T, R, C>& matrix);
		static Matrix<T, R, C> Negate(const Matrix<T, R, C>& matrix);
		static Matrix<T, C, R> ReverseMatrix(const Matrix<T, R, C>& matrix);
		static Matrix<T, R, C> CofactorMatrix(const Matrix<T, R, C>& matrix);
		static Matrix<T, C, R> AdjugateMatrix(const Matrix<T, R, C>& matrix);
		static Matrix<T, R, C> CreateIdentity();

		//Matrix<T, R, C>& operator=(Matrix<T, R, C> m);
		Matrix<T, R, C>& operator+=(const Matrix<T, R, C>& m);
		Matrix<T, R, C>& operator-=(const Matrix<T, R, C>& m);
		//Matrix<T, R, C>& operator*=(const Matrix<T, R, C>& m);
		Matrix<T, R, C>& operator*=(const double& scalar);
		Matrix<T, R, C>& operator*=(const float& scalar);
		Matrix<T, R, C>& operator*=(const int& scalar);
		Matrix<T, R, C>& operator*=(const uint_t& scalar);
		
		inline T operator()(const uintm_t row, const uintm_t col)
		{
			return GetValueAt(row, col);
		}
		
		inline bool IsSquare() const
		{
			return (R == C);
		}

		inline uint_t GetNumberOfRows() const
		{
			return R;
		}

		inline uint_t GetNumberOfColumns() const
		{
			return C;
		}

		inline T GetValueAt(const uint_t row, const uint_t column) const
		{
			if (row >= R || column >= C)
			{
				throw MatrixInvalidIndex();
			}

			return *(values + row * C + column);
		}

		inline void SetValueAt(const uint_t row, const uint_t column, const T value)
		{
			if (row >= R || column >= C)
			{
				throw MatrixInvalidIndex();
			}

			*(values + row * C + column) = value;
		}

		friend void Swap(Matrix<T, R, C>& matrixA, Matrix<T, R, C>& matrixB)
		{
			std::swap(matrixA.values, matrixB.values);
		}

		friend std::ostream& operator<<(std::ostream& out, const Matrix<T, R, C>& m)
		{
			out << std::endl;

			for (int i = 0; i < R; i++)
			{
				out << "|\t";
				for (int j = 0; j < C; j++)
				{
					out << *(m.values + i*C + j) << "\t";
				}
				out << "|" << std::endl;
			}

			out << std::endl;

			return out;
		}
	};

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator+(Matrix<T, R, C> matrixA, const Matrix<T, R, C>& matrixB)
	{
		return matrixA += matrixB;
	}

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator-(Matrix<T, R, C> matrixA, const Matrix<T, R, C>& matrixB)
	{
		return matrixA -= matrixB;
	}

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator*(Matrix<T, R, C> matrix, const double& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator*(Matrix<T, R, C> matrix, const float& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator*(Matrix<T, R, C> matrix, const int& scalar)
	{
		return matrix *= scalar;
	}

	template <typename T, uint_t R, uint_t C>
	Matrix<T, R, C> operator*(Matrix<T, R, C> matrix, const uint_t& scalar)
	{
		return matrix *= scalar;
	}
}
