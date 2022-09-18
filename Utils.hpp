#pragma once

// CORE INCLUDES
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

// EXTERN INCLUDES

////////////////////////
/// STRUCTURES
////////////////////////

////////////////////////
/// VECTOR2D
////////////////////////

/**
 * A collection which mirrors a 2D array.
 */
template <typename T>
class Vec2D
{
public:
	/**
	 * Initializes an empty 2D vector of given width and height.
	 */
	Vec2D(const std::size_t width, const std::size_t height)
		: data(width* height)
		, width(width)
		, height(height)

	{
	}
	/**
	 * Initializes a 2D vector of given width and height, filled with the provided default value.
	 */
	Vec2D(const std::size_t width, const std::size_t height, T defaultValue)
		: data(width* height, defaultValue)
		, width(width)
		, height(height)

	{
	}
	/**
	 * Returns the element at row, column. Const qualified.
	 */
	[[nodiscard]] const T& at(std::size_t row, std::size_t col) const
	{
		assert(row < this->height&& col < this->width); // In range check (Only for debug mode)
		return this->data[col + row * this->width];

	}
	/**
	 * Returns the element at row, column. Can be overwritten.
	 */
	T& at(std::size_t row, std::size_t col)
	{
		assert(row < this->height&& col < this->width); // In range check (Only for debug mode)
		return this->data[col + row * this->width];
	}
	/**
	 * Retrieve the underlying vector.
	 */
	std::vector<T>& getData()
	{
		return this->data;
	}
	/**
	 * Retrieve the underlying vector. Const qualified.
	 */
	[[nodiscard]] const std::vector<T>& getData() const
	{
		return this->data;
	}
	/**
	 * Returns whether the vector 2D is empty or not.
	 */
	[[nodiscard]] bool empty() const
	{
		return this->data.empty();
	}
	/**
	 * Copy the values of a raw 2D vector.
	 *
	 */
	void copy(const std::vector<std::vector<T>>& other)
	{
		assert(other.size() == this->height);
		for (std::size_t y = 0; y < other.size(); ++y)
		{
			for (std::size_t x = 0; x < other.at(0).size(); ++x)
			{
				assert(other.at(y).size() <= this->width);
				if (x >= other.at(y).size())
				{
					this->at(y, x) = T();
					continue;
				}
				this->at(y, x) = other.at(y).at(x);
			}
		}
	}
	/**
	 * Converts a raw 2D vector into Vec2D.
	 */
	static Vec2D<T> convert(const std::vector<std::vector<T>>& other)
	{
		std::size_t largestWidth = 0;
		auto findLargestWidth = [&](const auto& vec) {if (vec.size() > largestWidth) largestWidth = vec.size(); };
		std::for_each(other.begin(), other.end(), findLargestWidth);
		Vec2D<T> convertedVector(largestWidth, other.size());
		convertedVector.copy(other);
		return convertedVector;
	}
	// Members
private:
	std::vector<T> data;

public:
	const std::size_t width;  ///< Width of the 2D vector.
	const std::size_t height; ///< Height of the 2D vector.
};


////////////////////////
/// VECTOR3D
////////////////////////

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
	[[nodiscard]] float& operator [] (int i)
	{
		return ((&x)[i]);
	}

	// Index Vector
	[[nodiscard]] const float& operator [] (int i) const
	{
		return ((&x)[i]);
	}

	// Scalar Multiplication
	[[nodiscard]] Vector3D& operator *=(float s) noexcept
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	// Scalar Division
	[[nodiscard]] Vector3D& operator /=(float s) noexcept
	{
		float s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
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

struct Matrix3D
{
	public: 

	Matrix3D() = default;

	Matrix3D(
		float n00, float n01, float n02,
		float n03, float n04, float n05,
		float n06, float n07, float n08
	)
	{
		n[0][0] = n00, n[0][1] = n01, n[0][2] = n02,
		n[0][3] = n03, n[0][4] = n04, n[0][5] = n05,
		n[0][6] = n06, n[0][7] = n07, n[0][8] = n08;
	}

private:
	float n[3][3];
};


////////////////////////
/// INLINE FUNCTION
////////////////////////
 
////////////////////////
// BASIC MANIPULATION
////////////////////////

// Scalar Multiplication
[[nodiscard]] inline constexpr Vector3D operator *(const Vector3D& v, float s) noexcept
{
	return Vector3D(v.x * s, v.y * s, v.z * s);
}

// Scalar Division
[[nodiscard]] inline constexpr Vector3D operator /(const Vector3D& v, float s) noexcept
{
	s = 1.0f / s;
	return Vector3D(v.x * s, v.y * s, v.z * s);
}

// Invert Vector
[[nodiscard]] inline constexpr Vector3D operator -(const Vector3D& v) noexcept
{
	return Vector3D(-v.x, -v.y, -v.z);
}

// Vector Addition
[[nodiscard]] inline constexpr Vector3D operator +(const Vector3D& v, const Vector3D& b) noexcept
{
	return Vector3D(v.x + b.x, v.y + b.y, v.z + b.z);
}

// Vector Subtraction
[[nodiscard]] inline constexpr Vector3D operator +(const Vector3D& v, const Vector3D& b) noexcept
{
	return Vector3D(v.x - b.x, v.y - b.y, v.z - b.z);
}


////////////////////////
/// SPECIAL
////////////////////////

// Compute Magnitude
[[nodiscard]] inline float Magnitude(const Vector3D& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

}

// Normalize Vector
[[nodiscard]] inline Vector3D Normalize(const Vector3D& v)
{
	return v / Magnitude(v);
}

////////////////////////
/// VISITOR PATTERN STRUCT
////////////////////////

/**
* A struct used for inlining basic overloads for a variant type.
* 
* Example usage: (Overloading for equalily)
* 
*	auto equal = std::visist(overloaded 
*	{
*		 // float overload
*		 [this](double d1, double d2) -> bool
*		 {
*			return d1 == d2;
*		 },
*	
*        // int overload
*		 [this](int i1, int i2) -> bool
*        {
*			return i1 == i2;
*        },
* 
*        // bool overload
*		 [this](int b1, int b2) -> bool
*        {
*			return b1 == b2;
*        }
*	},
*	std::variant value parameter);
*/
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

