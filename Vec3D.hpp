#pragma once

////////////////////////
/// VECTOR3D
////////////////////////

/*
* Be aware, this is NOT a collection. 
*/

struct Vector3D
{
	float x, y, z;

	Vector3D() = default;

	constexpr Vector3D(float _x, float _y, float _z) noexcept
		: x{ _x }
		, y{ _y }
		, z{ _z }
	{
	}

	// Index Vector
	[[nodiscard]] float& operator [](int i)
	{
		return ((&x)[i]);
	}

	// Index Vector
	[[nodiscard]] const float& operator [](int i) const
	{
		return ((&x)[i]);
	}

	// Scalar Multiplication
	[[nodiscard]] Vector3D& operator *=(const float s) noexcept
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	// Scalar Division
	[[nodiscard]] Vector3D& operator /=(const float s) noexcept
	{
		const float t = 1.0f / s;
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	// Vector Addition
	[[nodiscard]] Vector3D& operator +=(const Vector3D& v) noexcept
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	// Vector Subtraction
	[[nodiscard]] Vector3D& operator -=(const Vector3D& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
};

////////////////////////
// BASIC MANIPULATION
////////////////////////

// Scalar Multiplication
[[nodiscard]] inline constexpr Vector3D operator *(const Vector3D& v, float s) noexcept
{
	return { v.x * s, v.y * s, v.z * s };
}

// Scalar Division
[[nodiscard]] inline constexpr Vector3D operator /(const Vector3D& v, float s) noexcept
{
	s = 1.0f / s;
	return { v.x * s, v.y * s, v.z * s };
}

// Invert Vector
[[nodiscard]] inline constexpr Vector3D operator-(const Vector3D& v) noexcept
{
	return { -v.x, -v.y, -v.z };
}

// Vector Addition
[[nodiscard]] inline constexpr Vector3D operator+(const Vector3D& v, const Vector3D& b) noexcept
{
	return { v.x + b.x, v.y + b.y, v.z + b.z };
}

// Vector Subtraction
[[nodiscard]] inline constexpr Vector3D operator-(const Vector3D& v, const Vector3D& b) noexcept
{
	return { v.x - b.x, v.y - b.y, v.z - b.z };
}

////////////////////////
/// SPECIAL
////////////////////////

// Compute Magnitude
[[nodiscard]] inline float magnitude(const Vector3D& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Normalize Vector
[[nodiscard]] inline Vector3D normalize(const Vector3D& v)
{
	return v / magnitude(v);
}
