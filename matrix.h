
#pragma once
#include "matrix_impl/base_template.h"

#define STF_MATRIX_H

/* Matrix defines */
namespace stf
{
	/* Untyped matrices */
	template < size_t ROWS, size_t COLS, typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using Mat = Matrix<ROWS, COLS, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tMat4 = Mat<4, 4, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tMat3 = Mat<3, 3, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tMat2 = Mat<2, 2, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tMat2x3 = Mat<2, 3, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tMat3x2 = Mat<3, 2, Ty>;

	/* Default matrices */
	typedef tMat4<>	   Mat4;
	typedef tMat3<>	   Mat3;
	typedef tMat2<>	   Mat2;
	typedef tMat2x3<>  Mat2x3;
	typedef tMat3x2<>  Mat3x2;

	/* Typed matrices */
	typedef tMat4<float>	   fMat4;
	typedef tMat3<float>	   fMat3;
	typedef tMat2<float>	   fMat2;
	typedef tMat2x3<float>  fMat2x3;
	typedef tMat3x2<float>  fMat3x2;

	typedef tMat4<double>   dMat4;
	typedef tMat3<double>   dMat3;
	typedef tMat2<double>   dMat2;
	typedef tMat2x3<double> dMat2x3;
	typedef tMat3x2<double> dMat3x2;

	typedef tMat4<int>   iMat4;
	typedef tMat3<int>   iMat3;
	typedef tMat2<int>   iMat2;
	typedef tMat2x3<int> iMat2x3;
	typedef tMat3x2<int> iMat3x2;

	typedef tMat4<STF_UNSIGNED_BYTE>   ubMat4;
	typedef tMat3<STF_UNSIGNED_BYTE>   ubMat3;
	typedef tMat2<STF_UNSIGNED_BYTE>   ubMat2;
	typedef tMat2x3<STF_UNSIGNED_BYTE> ubMat2x3;
	typedef tMat3x2<STF_UNSIGNED_BYTE> ubMat3x2;

	typedef tMat4<bool>   bMat4;
	typedef tMat3<bool>   bMat3;
	typedef tMat2<bool>   bMat2;
	typedef tMat2x3<bool> bMat2x3;
	typedef tMat3x2<bool> bMat3x2;
}

#include "matrix_impl/matrix_impl.h"

/* In this file you can extend matrix functionality */
#include "matrix_impl/matrix_ext.h"
