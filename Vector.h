
#pragma once
#include <stf/MatrixImpl/BaseTemplate.h>

#define STF_VECTOR_H

/* Matrix defines */
namespace stf
{
	/* Untyped vectors */
	template < size_t ROWS, typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using Vec = Matrix<ROWS, 1, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tVec2 = Vec<2, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tVec3 = Vec<3, Ty>;
	template < typename Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	using tVec4 = Vec<4, Ty>;

	/* Default vectors */
	typedef tVec2<>	Vec2;
	typedef tVec3<>	Vec3;
	typedef tVec4<>	Vec4;

	/* Typed vectors */
	typedef tVec2<float>	fVec2;
	typedef tVec3<float>	fVec3;
	typedef tVec4<float>	fVec4;

	typedef tVec2<double> dVec2;
	typedef tVec3<double> dVec3;
	typedef tVec4<double> dVec4;

	typedef tVec2<int> iVec2;
	typedef tVec3<int> iVec3;
	typedef tVec4<int> iVec4;

	typedef tVec2<STF_UNSIGNED_BYTE> ubVec2;
	typedef tVec3<STF_UNSIGNED_BYTE> ubVec3;
	typedef tVec4<STF_UNSIGNED_BYTE> ubVec4;

	typedef tVec2<bool> bVec2;
	typedef tVec3<bool> bVec3;
	typedef tVec4<bool> bVec4;
}

#include <stf/MatrixImpl/VectorImpl.h>

/* In this file you can extend vector functionality */
#include <stf/MatrixImpl/VectorExt.h>