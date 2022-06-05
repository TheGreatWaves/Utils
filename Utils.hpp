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
/// ALGORITHMS
////////////////////////