#pragma once

#include <optional>
#include <array>
#include <stdexcept>

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
