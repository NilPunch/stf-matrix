
#pragma once
#include "base_template.h"
#include <initializer_list>

namespace stf
{
	template < size_t THIS_ROWS, size_t THIS_COLS, class Ty>
	class Matrix
	{
		static_assert(THIS_ROWS > 0 && THIS_COLS > 0, "Colomns and rows must be more then 0");

	public:
		using value_type = Ty;
		using type = Matrix;
		using pointer = Matrix * ;

	private:
		value_type data[THIS_ROWS][THIS_COLS] = { static_cast<value_type>(0) };

	public:
		Matrix() = default;
		Matrix(const Matrix& Copy) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = Copy.data[x][y];
				}
		}
		Matrix(Matrix&& Rhs) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = Rhs.data[x][y];
				}
		}
		Matrix(Matrix::value_type Val) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
					this->data[x][y] = Val;
		}
		constexpr Matrix(std::initializer_list<Matrix::value_type> Args)
		{
			//static_assert(THIS_ROWS * THIS_COLS == Args.size() + 1, "Can't match args to fill matrix");
			auto from = Args.begin();
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = *(from);
					++from;
				}
		}

		value_type* operator[] (size_t Idx) { return data[Idx]; }
		const value_type* operator[] (size_t Idx) const { return data[Idx]; }

		template < size_t RHS_ROWS, size_t RHS_COLS >
		Matrix& operator=(const Matrix<RHS_ROWS, RHS_COLS>& Rhs) noexcept
		{
			constexpr size_t min_rows = RHS_ROWS > THIS_ROWS ? THIS_ROWS : RHS_ROWS;
			constexpr size_t min_cols = RHS_COLS > THIS_COLS ? THIS_COLS : RHS_COLS;
			for (size_t x = 0; x < min_rows; ++x)
				for (size_t y = 0; y < min_cols; ++y)
				{
					this->data[x][y] = Rhs[x][y];
				}
			return *(this);
		}
		template <>
		Matrix& operator=<THIS_ROWS, THIS_COLS>(const Matrix<THIS_ROWS, THIS_COLS>& Rhs) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = Rhs[x][y];
				}
			return *(this);
		}

		Matrix& operator=(Matrix::value_type Val) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
					this->data[x][y] = Val;
			return *(this);
		}

		Matrix& operator=(std::initializer_list<Matrix::value_type> Args)
		{
			//static_assert(THIS_ROWS * THIS_COLS == Args.size() + 1U, "Can't match args to fill matrix");
			auto from = Args.begin();
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = *(from);
					++from;
				}
			return *(this);
		}

		Matrix& operator+=(const Matrix& Rhs) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
				{
					this->data[x][y] = Rhs[x][y];
				}
			return *(this);
		}
		Matrix& operator+=(Matrix::value_type Val) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
					this->data[x][y] += Val;
			return *(this);
		}
		Matrix& operator*=(Matrix::value_type Val) noexcept
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				for (size_t y = 0; y < THIS_COLS; ++y)
					this->data[x][y] *= Val;
			return *(this);
		}
	};
}

#include <stf/MatrixImpl/MatMul.h>
