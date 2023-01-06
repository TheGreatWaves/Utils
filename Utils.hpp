#pragma once

// CORE INCLUDES
#include <vector>
#include <cassert>
#include <algorithm>
#include <optional>
#include <execution>
#include <iostream>
#include <functional>
#include <array>

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
	 * STL compatible. (Thankfully nothing really needs to be done thanks to the underlying vector)
	 */
	using value_type = T;
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;
	using reverse_iterator = typename std::vector<T>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

	iterator begin() noexcept
	{
		return data.begin();
	}

	[[nodiscard]] const_iterator begin() const noexcept
	{
		return data.begin();
	}

	iterator end() noexcept
	{
		return data.end();
	}

	[[nodiscard]] const_iterator end() const noexcept
	{
		return data.end();
	}

	reverse_iterator rbegin() noexcept
	{
		return data.rbegin();
	}

	[[nodiscard]] const_reverse_iterator rbegin() const noexcept
	{
		return data.rbegin();
	}

	reverse_iterator rend() noexcept
	{
		return data.rend();
	}

	[[nodiscard]] const_reverse_iterator rend() const noexcept
	{
		return data.rend();
	}

	/**
	 * Initializes a 2D vector of given width and height, filled with the provided default value (if provided).
	 */
	Vec2D(const std::size_t width, const std::size_t height, std::optional<T> defaultValue = {})
		: width(width)
		, height(height)
		, data(width * height, defaultValue.value_or(T{}))
	{
	}

	/**
	 * Initializes a Vec2D object from a raw 2D vector.
	 */
	explicit Vec2D(const std::vector<std::vector<T>>& other)
		: width(std::reduce(other.begin(), other.end(), std::size_t{ 0 }, [](const auto& a, const auto& b) { return std::max(a, b.size()); }))
		, height(other.size())
		, data(width* height)
	{
		for (std::size_t y = 0; y < other.size(); ++y)
		{
			for (std::size_t x = 0; x < other[y].size(); ++x)
			{
				this->at(y, x) = other[y][x];
			}
		}
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
	 * Returns the element at row, column. Can be overwritten.
	 */
	T& operator()(std::size_t x, std::size_t y)
	{
		return this->at(y, x);
	}

	/**
	 * Returns the element at row, column. Const qualified.
	 */
	const T& operator()(std::size_t x, std::size_t y) const
	{
		return this->at(y, x);
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
	 * Fill all elements with the given value.
	 */
	void fill(const T& value)
	{
		std::fill(data.begin(), data.end(), value);
	}

	/**
	 * Swaps the contents of the Vec2D object with another Vec2D object.
	 */
	void swap(Vec2D& other) noexcept
	{
		auto tempData = std::move(data);
		data = std::move(other.data);
		other.data = std::move(tempData);
		std::size_t tempWidth = width;
		width = other.width;
		other.width = tempWidth;

		std::size_t tempHeight = height;
		height = other.height;
		other.height = tempHeight;
	}

	/**
	* Removes all elements from the Vec2D object.
	*/
	void clear()
	{
		data.clear();
	}

	/**
	 * Reserves a specific amount of memory for the Vec2D object.
	 */
	void reserve(std::size_t n)
	{
		data.reserve(n);
	}

	/**
	 * Searches the Vec2D object for a specific element.
	 * Returns an std::optional containing the position of the element if found, or an empty std::optional if not found.
	 */
	[[nodiscard]] std::optional<std::pair<std::size_t, std::size_t>> find(const T& value) const
	{
		// Use std::find to search for the specified value in the data member
		auto it = std::find(data.begin(), data.end(), value);

		// If the value was not found, return an empty std::optional
		if (it == data.end())
		{
			return std::nullopt;
		}

		// Calculate the index of the element in the data member
		const std::size_t index = std::distance(data.begin(), it);

		// Calculate the position of the element using the index and the width of the Vec2D object
		return std::make_pair(index % width, index / width);
	}

	/**
	 *	Add current 2D Vector with another one and return the result.
	 */
	Vec2D& operator+=(const Vec2D& other)
	{
		assert(this->width == other.width && this->height == other.height);
		std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<T>());
		return *this;
	}

	/**
	 *	Minus current 2D Vector with another one and return the result.
	 */
	Vec2D& operator-=(const Vec2D& other)
	{
		assert(this->width == other.width && this->height == other.height);
		std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<T>());
		return *this;
	}
	
	/**
	 * Return the summation of two 2D vectors.
	 */
	friend Vec2D operator+(Vec2D lhs, const Vec2D& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	/**
	 * Return the subtraction result of two 2D vectors.
	 */
	friend Vec2D operator-(Vec2D lhs, const Vec2D& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	/**
	 * Check to see if two vectors are equivalent.
	 */
	friend bool operator==(const Vec2D& lhs, const Vec2D& rhs) 
	{
		// Check that the dimensions of the two Vec2D objects are equal
		if (lhs.width != rhs.width || lhs.height != rhs.height) 
		{
			return false;
		}

		// Check that the elements of the two Vec2D objects are equal
		return lhs.data == rhs.data;
	}

	/**
	 * Check to see if two vectors are not equivalent.
	 */
	friend bool operator!=(const Vec2D& lhs, const Vec2D& rhs) 
	{
		return !(lhs == rhs);
	}


	[[nodiscard]] std::pair<std::size_t, std::size_t> dim() const
	{
		return { width, height };
	}
	

	/**
	 * Hash function.
	 */
	friend struct std::hash<Vec2D<T>>;

private:
	std::size_t width;  	///< Width of the 2D vector.
	std::size_t height; 	///< Height of the 2D vector.
	std::vector<T> data;	///< Underlying collection.

};

template <typename T>
struct std::hash<Vec2D<T>> 
{
	std::size_t operator()(const Vec2D<T>& vec) const 
	{
		std::size_t h = 0;
		for (const auto& element : vec.data) 
		{
			h ^= std::hash<T>()(element);
		}
		return h;
	}
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
	float n[3][3]{};
};


////////////////////////
/// CIRCULAR BUFFER
////////////////////////

template <typename T, size_t N>
class CircularBuffer
{
public:
    CircularBuffer()
        : capacity{ N }
    {   
    }

	/**
	 * @brief Adds an element and returns the ejected element ( if any )
	 * 
	 * @param elem The element being added
	 * @return std::optional<T> The ejected element
	 */
    std::optional<T> add(T elem)
	{
		std::optional<T> old_elem;

		if (current == capacity)
		{
			old_elem = std::move(data[current % capacity]);
			start = (start + 1) % capacity;
		}

		data[current % capacity] = std::move(elem);
		++current;

		return old_elem;
	}

	/**
	 * @brief Access the element at the given index ( ref ), with no bounds checking
	 * 
	 * @param index Index of element
	 * @return T& The element
	 */
	T& operator[](int index)
	{
		return data[(start + index) % capacity];
	}

	/**
	 * @brief Access the element at the given index ( const ref ), with no bounds checking
	 * 
	 * @param index Index of element
	 * @return const T& The element
	 */
	const T& operator[](int index) const
	{
		return data[(start + index) % capacity];
	}

    /**
     * @brief Access the element at the given index ( const ref ), with bounds checking
     * 
     * @param index Index of element
     * @return const T& The element
     */
    const T& at(int index) const
	{
		if (index < 0 || index >= size())
			throw std::out_of_range("Index out of range");

		return (*this)[index];
	}

	/**
	 * @brief Access the element at the given index ( ref ), with bounds checking
	 * 
	 * @param index Index of element
	 * @return T& The element
	 */
	T& at(int index)
	{
		if (index < 0 || index >= size())
			throw std::out_of_range("Index out of range");

		return (*this)[index];
	}

	/**
	 * @brief Returns a reference to the first element in the buffer
	 * 
	 * @return T& The element
	 */
	T& top()
	{
		if (current == 0)
			throw std::underflow_error("Buffer is empty");

		return data[start];
	}

	/**
	 * @brief Removes the last element from the buffer and returns it
	 * 
	 * @return T The element
	 */
	T pop()
	{
		if (current == 0)
			throw std::underflow_error("Buffer is empty");

		--current;
		return data[current % capacity];
	}

    int startPos() const noexcept { return start; }
    [[nodiscard]] size_t realSize() const noexcept { return current; }
    [[nodiscard]] size_t size() const noexcept { return current > capacity ? capacity : current; }
    [[nodiscard]] bool empty() const noexcept { return current == 0; }

	/**
	 * @brief Removes all elements from the buffer
	 */
	void clear()
	{
		current = 0;
		start = 0;
	}

	/**
	 * @brief Changes the size of the buffer
	 * 
	 * @param new_size The new size of the buffer
	 */
	void resize(size_t new_size)
	{
		if (new_size <= 0)
			throw std::invalid_argument("Size must be positive");

		if (new_size > N)
			throw std::length_error("Size exceeds maximum capacity");

		if (new_size < size())
		{
			current = new_size;
			start = 0;
		}
		else
		{
			capacity = new_size;
		}
	}

private:
    int current = 0;
    int start = 0;
    size_t capacity;
    std::array<T, N> data;
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
template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator()...;
};
