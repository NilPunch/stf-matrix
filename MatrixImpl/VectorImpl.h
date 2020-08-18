
#pragma once
#include <stf/MatrixImpl/BaseTemplate.h>
#include <initializer_list>
#include <cmath>

namespace stf
{
	/* VectorN */
	template < size_t THIS_ROWS, typename Ty>
	class Matrix<THIS_ROWS, 1, Ty>
	{
		static_assert(THIS_ROWS > 0, "Colomns and must be more then 0");
	public:
		using value_type = Ty;
		using type = Matrix;
		using pointer = Matrix * ;

	private:
		value_type data[THIS_ROWS] = { static_cast<value_type>(0) };

	public:
		Matrix() = default;
		Matrix(const Matrix& Copy)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] = Copy.data[x];
			}
		}
		Matrix(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] = Val;
		}
		Matrix(std::initializer_list<Matrix::value_type> Args)
		{
			//static_assert(THIS_ROWS == Args.size() + 1, "Can't match args to fill matrix");
			auto from = Args.begin();
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] = *(from);
				++from;
			}
		}

		value_type& operator[] (size_t Idx) { return data[Idx]; }
		const value_type operator[] (size_t Idx) const { return data[Idx]; }

		template < size_t RHS_ROWS >
		Matrix& operator=(const Matrix<RHS_ROWS, 1, Ty>& Rhs)
		{
			constexpr size_t min_rows = RHS_ROWS > THIS_ROWS ? THIS_ROWS : RHS_ROWS;
			for (size_t x = 0; x < min_rows; ++x)
			{
				this->data[x] = Rhs[x];
			}
			return *(this);
		}

		template <>
		Matrix& operator=<THIS_ROWS>(const Matrix<THIS_ROWS, 1, Ty>& Rhs)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] = Rhs[x];
			}
			return *(this);
		}

		Matrix& operator=(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] = Val;
			return *(this);
		}

		Matrix& operator=(std::initializer_list<Matrix::value_type> Args)
		{
			//static_assert(THIS_ROWS == Args.size() + 1U, "Can't match args to fill matrix");
			auto from = Args.begin();
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] = *(from);
				++from;
			}
			return *(this);
		}

		Matrix& operator+=(const Matrix& Rhs)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] += Rhs[x];
			}
			return *(this);
		}
		Matrix& operator+=(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] += Val;
			return *(this);
		}
		Matrix& operator-=(const Matrix& Rhs)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
			{
				this->data[x] -= Rhs[x];
			}
			return *(this);
		}
		Matrix& operator-=(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] -= Val;
			return *(this);
		}

		Matrix& operator*=(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] *= Val;
			return *(this);
		}
		Matrix& operator/=(Matrix::value_type Val)
		{
			for (size_t x = 0; x < THIS_ROWS; ++x)
				this->data[x] /= Val;
			return *(this);
		}
	};

	/* Vec2 */
	template < typename Ty >
	struct Matrix<2, 1, Ty> {
		using value_type = Ty;
		using type = Matrix<2, 1,Ty>;

		union
		{
			struct { Ty x, y; };
			struct { Ty u, v; };
		};

		/* Default constuctors */
		Matrix() : x(static_cast<Ty>(0)), y(static_cast<Ty>(0)) {}
		Matrix(const Ty& X, const Ty& Y) : x(X), y(Y) {}
		Matrix(const Matrix& copy) : x(copy.x), y(copy.y) {}
		Matrix(Matrix&& rvec) : x(rvec.x), y(rvec.y) {}

		/* Any numeric initialisation */
		template < typename Ty_AnyFirst, typename Ty_AnySecond >
		Matrix(const Ty_AnyFirst& X, const Ty_AnySecond& Y)
			: x((Ty)X), y((Ty)Y) {}
		template < typename Ty_AnyFirst, typename Ty_AnySecond >
		Matrix(Ty_AnyFirst&& rX, Ty_AnySecond&& rY)
			: x((Ty)rX), y((Ty)rY) {}
		template < typename Ty_Any >
		Matrix(const Ty_Any& X, const Ty_Any& Y)
			: x((Ty)X), y((Ty)Y) {}
		template < typename Ty_Any >
		Matrix(Ty_Any&& rX, Ty_Any&& rY)
			: x((Ty)rX), y((Ty)rY) {}

		Ty mag() const { return (Ty)sqrt(x * x + y * y); }
		Ty mag_sqr() const { return (Ty)(x * x + y * y); }

		const Ty& max_cord() const { return abs(x) > abs(y) ? x : y; }

		const Ty& min_cord() const { return abs(x) < abs(y) ? x : y; }

		Matrix& normalize() { Ty lenght = (Ty)sqrt(x * x + y * y); x /= lenght; y /= lenght; return *this; }

		void rotate(const double angle)
		{
			Ty t_sin = (Ty)sin(angle);
			Ty t_cos = (Ty)cos(angle);
			Ty temp = x * t_cos - y * t_sin;
			y = x * t_sin + y * t_cos;
			x = temp;
		}

		template < typename Ty_vImpl >
		operator Matrix<2, 1, Ty_vImpl>() const
		{
			return Matrix<2, 1, Ty_vImpl>{ (Ty_vImpl)this->x, (Ty_vImpl)this->y };
		}

		value_type& operator[] (size_t Idx) { return *(&x + Idx); }
		const value_type operator[] (size_t Idx) const { return *(&x + Idx); }

		Matrix operator- (const Ty& Rhs) const { return Matrix(this->x - Rhs, this->y - Rhs); }
		Matrix operator+ (const Ty& Rhs) const { return Matrix(this->x + Rhs, this->y + Rhs); }
		Matrix operator* (const Ty& Rhs) const { return Matrix(this->x * Rhs, this->y * Rhs); }
		Matrix operator/ (const Ty& Rhs) const { return Matrix(this->x / Rhs, this->y / Rhs); }

		void operator+= (const Matrix& Val) { this->x += Val.x; this->y += Val.y; }
		void operator-= (const Matrix& Val) { this->x -= Val.x; this->y -= Val.y; }
		void operator+= (const Ty& Rhs) { this->x += Rhs; this->y += Rhs; }
		void operator-= (const Ty& Rhs) { this->x -= Rhs; this->y -= Rhs; }
		void operator*= (const Ty& Rhs) { this->x *= Rhs; this->y *= Rhs; }
		void operator/= (const Ty& Rhs) { this->x /= Rhs; this->y /= Rhs; }

		Matrix& operator= (const Matrix& Val) { this->x = Val.x; this->y = Val.y; return *this; }

		bool operator== (const Matrix& Val) const { return (this->x == Val.x) && (this->y == Val.y); }
		bool operator!= (const Matrix& Val) const { return (this->x != Val.x) || (this->y != Val.y); }
	};

	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator+ (const Matrix<2, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<2, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<2, 1,decltype(Lhs.x + Rhs.x)>(Lhs.x + Rhs.x, Lhs.y + Rhs.y);
	}
	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator- (const Matrix<2, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<2, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<2, 1,decltype(Lhs.x - Rhs.x)>(Lhs.x - Rhs.x, Lhs.y - Rhs.y);
	}
	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator* (const Matrix<2, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<2, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<2, 1,decltype(Lhs.x * Rhs.x)>(Lhs.x * Rhs.x, Lhs.y * Rhs.y);
	}

	/* Vector3 */
	template < typename Ty >
	struct Matrix<3, 1, Ty> {
		using value_type = Ty;
		using type = Matrix<3, 1,Ty>;

		union
		{
			struct { Ty x, y, z; };
			struct { Ty r, g, b; };
		};

		/* Default constuctors */
		Matrix() : x(static_cast<Ty>(0)), y(static_cast<Ty>(0)), z(static_cast<Ty>(0)) {}
		Matrix(const Ty& X, const Ty& Y, const Ty& Z) : x(X), y(Y), y(Z) {}
		Matrix(const Matrix& copy) : x(copy.x), y(copy.y), z(copy.z) {}
		Matrix(Matrix&& rvec) : x(rvec.x), y(rvec.y), z(rvec.z) {}

		/* Any numeric initialisation */
		template < typename Ty_AnyFirst, typename Ty_AnySecond, typename Ty_AnyThird >
		Matrix(const Ty_AnyFirst& X, const Ty_AnySecond& Y, const Ty_AnyThird& Z)
			: x((Ty)X), y((Ty)Y), z((Ty)Z) {}
		template < typename Ty_AnyFirst, typename Ty_AnySecond, typename Ty_AnyThird >
		Matrix(Ty_AnyFirst&& rX, Ty_AnySecond&& rY, Ty_AnyThird&& rZ)
			: x((Ty)rX), y((Ty)rY), z((Ty)rZ) {}
		template < typename Ty_Any >
		Matrix(const Ty_Any& X, const Ty_Any& Y, const Ty_Any& Z)
			: x((Ty)X), y((Ty)Y), z((Ty)Z) {}
		template < typename Ty_Any >
		Matrix(Ty_Any&& rX, Ty_Any&& rY, Ty_Any&& rZ)
			: x((Ty)rX), y((Ty)rY), z((Ty)rZ) {}

		Ty mag() const { return (Ty)sqrt(x * x + y * y + z * z); }
		Ty mag_sqr() const { return (Ty)(x * x + y * y + z * z); }

		const Ty& max_cord() const { return abs(x) > abs(y) ? (abs(x) > abs(z) ? x : z) : (abs(y) > abs(z) ? y : z); }
		const Ty& min_cord() const { return abs(x) < abs(y) ? (abs(x) < abs(z) ? x : z) : (abs(y) < abs(z) ? y : z); }

		void normalize() { Ty lenght = (Ty)mag(); x /= lenght; y /= lenght; z /= lenght; ; }

		template < typename Ty_vImpl >
		operator Matrix<3, 1, Ty_vImpl>() const
		{
			return Matrix<3, 1, Ty_vImpl>{ (Ty_vImpl)this->x, (Ty_vImpl)this->y, (Ty_vImpl)this->z };
		}
		template < typename Ty_vImpl >
		operator Matrix<2, 1, Ty_vImpl>() const
		{
			return Matrix<2, 1, Ty_vImpl>{ (Ty_vImpl)this->x, (Ty_vImpl)this->y };
		}

		value_type& operator[] (size_t Idx) { return *(&x + Idx); }
		const value_type operator[] (size_t Idx) const { return *(&x + Idx); }

		Matrix operator- (const Ty& Rhs) const { return Matrix(this->x - Rhs, this->y - Rhs, this->z - Rhs); }
		Matrix operator+ (const Ty& Rhs) const { return Matrix(this->x + Rhs, this->y + Rhs, this->z + Rhs); }
		Matrix operator* (const Ty& Rhs) const { return Matrix(this->x * Rhs, this->y * Rhs, this->z * Rhs); }
		Matrix operator/ (const Ty& Rhs) const { return Matrix(this->x / Rhs, this->y / Rhs, this->z / Rhs); }

		void operator+= (const Matrix& Val) { this->x += Val.x; this->y += Val.y, this->z += Val.z; }
		void operator-= (const Matrix& Val) { this->x -= Val.x; this->y -= Val.y, this->z -= Val.z; }
		void operator+= (const Ty& Rhs) { this->x += Rhs; this->y += Rhs; this->z += Rhs; }
		void operator-= (const Ty& Rhs) { this->x -= Rhs; this->y -= Rhs; this->z -= Rhs; }
		void operator*= (const Ty& Rhs) { this->x *= Rhs; this->y *= Rhs; this->z *= Rhs; }
		void operator/= (const Ty& Rhs) { this->x /= Rhs; this->y /= Rhs; this->z *= Rhs; }

		Matrix& operator= (const Matrix& Val) { this->x = Val.x; this->y = Val.y; this->z = Val.z; return *this; }

		bool operator== (const Matrix& Val) const { return (this->x == Val.x) && (this->y == Val.y) && (this->z == Val.z); }
		bool operator!= (const Matrix& Val) const { return (this->x != Val.x) || (this->y != Val.y) || (this->z != Val.z); }
	};

	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator+ (const Matrix<3, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<3, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<3, 1,decltype(Lhs.x + Rhs.x)>(Lhs.x + Rhs.x, Lhs.y + Rhs.y, Lhs.z + Rhs.z);
	}
	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator- (const Matrix<3, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<3, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<3, 1,decltype(Lhs.x - Rhs.x)>(Lhs.x - Rhs.x, Lhs.y - Rhs.y, Lhs.z - Rhs.z);
	}
	template < typename LHS_VALUE_TYPE, typename RHS_VALUE_TYPE >
	auto operator* (const Matrix<3, 1,LHS_VALUE_TYPE>& Lhs, const Matrix<3, 1,RHS_VALUE_TYPE>& Rhs)
	{
		return Matrix<3, 1,decltype(Lhs.x * Rhs.x)>(Lhs.y * Rhs.z - Lhs.z * Rhs.y, Lhs.z * Rhs.x - Lhs.x * Rhs.z, Lhs.x * Rhs.y - Lhs.y * Rhs.x);
	}
}

#include <stf/MatrixImpl/MatMul.h>