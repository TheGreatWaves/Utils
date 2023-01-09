#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <cassert>
#include <algorithm>
#include <execution>

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
		, data(width* height, defaultValue.value_or(T{}))
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
