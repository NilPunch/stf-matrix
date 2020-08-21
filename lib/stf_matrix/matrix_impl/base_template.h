/*
	* Base matrix template.
*/
#pragma once

// You can define your own default type for use
#ifndef STF_MATRIX_DEFAULT_VALUE_TYPE 
	#define STF_MATRIX_DEFAULT_VALUE_TYPE float		
#endif											  

#define STF_UNSIGNED_BYTE unsigned char

namespace stf
{
	template < size_t THIS_ROWS, size_t THIS_COLS = THIS_ROWS, class Ty = STF_MATRIX_DEFAULT_VALUE_TYPE >
	class Matrix;
}