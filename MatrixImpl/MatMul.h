/*
	* For clearness library handle different multiplication cases:
	* Matrix vs Matrix
	* Matrix vs Vector
	* Vector vs Matrix
*/

#include <type_traits>

namespace stf
{

#if defined(STF_MATRIX_H) && !defined(STF_USE_MATRIX_MULTIPLICATION_CASE)
	#define STF_USE_MATRIX_MULTIPLICATION_CASE

	// Matrix vs Matrix multiplication
	template <size_t LHS_ROWS, size_t LHS_COLS, size_t RHS_COLS, typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE,
		typename RETURN_VALUE_TYPE = decltype(static_cast<LHS_VALUE_TYPE>(0) + static_cast<RHS_VALUE_TYPE>(0))>
	Matrix<LHS_ROWS, RHS_COLS, RETURN_VALUE_TYPE> operator*(const Matrix<LHS_ROWS, LHS_COLS, LHS_VALUE_TYPE>& Lhs, const Matrix<LHS_COLS, RHS_COLS, RHS_VALUE_TYPE>& Rhs)
	{
		Matrix<LHS_ROWS, RHS_COLS, RETURN_VALUE_TYPE> result_mat;
		for (size_t x = 0; x < LHS_ROWS; ++x)
			for (size_t y = 0; y < RHS_COLS; ++y)
			{
				RETURN_VALUE_TYPE sum = static_cast<RETURN_VALUE_TYPE>(0);
				for (size_t k = 0; k < LHS_COLS; ++k)
					sum += Lhs[x][k] * Rhs[k][y];
				result_mat[x][y] = sum;
			}
		return result_mat;
	}

#endif

#if defined(STF_MATRIX_H) && defined(STF_VECTOR_H) && !defined(STF_USE_VECTOR_MULTIPLICATION_CASE)
	#define STF_USE_VECTOR_MULTIPLICATION_CASE

	// Matrix vs Vector multiplication
	template < size_t LHS_ROWS, size_t LHS_COLS, typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE,
		typename RETURN_VALUE_TYPE = decltype(static_cast<LHS_VALUE_TYPE>(0) + static_cast<RHS_VALUE_TYPE>(0)) >
	Matrix<LHS_ROWS, 1, RETURN_VALUE_TYPE> operator*(const Matrix<LHS_ROWS, LHS_COLS, LHS_VALUE_TYPE>& Lhs, const Matrix<LHS_COLS, 1, RHS_VALUE_TYPE>& Rhs)
	{
		Matrix<LHS_ROWS, 1, RETURN_VALUE_TYPE> result_mat;
		for (size_t x = 0; x < LHS_ROWS; ++x)
		{
			RETURN_VALUE_TYPE sum = static_cast<RETURN_VALUE_TYPE>(0);
			for (size_t k = 0; k < LHS_COLS; ++k)
				sum += Lhs[x][k] * Rhs[k];
			result_mat[x] = sum;
		}
		return result_mat;
	}

	// Vector vs Matrix multiplication
	template < size_t LHS_ROWS, size_t RHS_COLS, typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE,
		typename RETURN_VALUE_TYPE = decltype(static_cast<LHS_VALUE_TYPE>(0) + static_cast<RHS_VALUE_TYPE>(0)) >
	Matrix<LHS_ROWS, RHS_COLS, RETURN_VALUE_TYPE> operator*(const Matrix<LHS_ROWS, 1, LHS_VALUE_TYPE>& Lhs, const Matrix<1, RHS_COLS, RHS_VALUE_TYPE>& Rhs)
	{
		Matrix<LHS_ROWS, RHS_COLS, RETURN_VALUE_TYPE> result_mat;
		for (size_t x = 0; x < LHS_ROWS; ++x)
			for (size_t y = 0; y < RHS_COLS; ++y)
			{
				result_mat[x][y] = static_cast<RETURN_VALUE_TYPE>(Lhs[x] * Rhs[0][y]);
			}
		return result_mat;
	}

#endif
}