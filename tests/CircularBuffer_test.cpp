#include "Utils.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_session.hpp"

TEST_CASE("CircularBuffer add function")
{
    CircularBuffer<int, 5> buffer;

    // Add elements to buffer
    REQUIRE(buffer.add(1) == std::nullopt);
    REQUIRE(buffer.add(2) == std::nullopt);
    REQUIRE(buffer.add(3) == std::nullopt);
    REQUIRE(buffer.add(4) == std::nullopt);
    REQUIRE(buffer.add(5) == std::nullopt);

    // Adding an additional element should cause the oldest element to be overwritten
    REQUIRE(buffer.add(6) == 1);

    // Check that buffer size is correct
    REQUIRE(buffer.size() == 5);
    REQUIRE(buffer.realSize() == 6);

    // Check that elements are in the correct order
    REQUIRE(buffer[0] == 2);
    REQUIRE(buffer[1] == 3);
    REQUIRE(buffer[2] == 4);
    REQUIRE(buffer[3] == 5);
    REQUIRE(buffer[4] == 6);
}

TEST_CASE("CircularBuffer at function")
{
    CircularBuffer<int, 5> buffer;

    // Add elements to buffer
    buffer.add(1);
    buffer.add(2);
    buffer.add(3);
    buffer.add(4);
    buffer.add(5);

    // Check that elements can be accessed using 'at' function
    REQUIRE(buffer.at(0) == 1);
    REQUIRE(buffer.at(1) == 2);
    REQUIRE(buffer.at(2) == 3);
    REQUIRE(buffer.at(3) == 4);
    REQUIRE(buffer.at(4) == 5);

    // Check that out of range access throws exception
    REQUIRE_THROWS_AS(buffer.at(5), std::out_of_range);
    REQUIRE_THROWS_AS(buffer.at(-1), std::out_of_range);
}

TEST_CASE("CircularBuffer top and pop functions")
{
    CircularBuffer<int, 5> buffer;

    // Add elements to buffer
    buffer.add(1);
    buffer.add(2);
    buffer.add(3);

    // Check that top function returns first element
    REQUIRE(buffer.top() == 1);

    // Check that pop function removes and returns last element
    REQUIRE(buffer.pop() == 3);
    REQUIRE(buffer.size() == 2);
    REQUIRE(buffer.realSize() == 2);
    REQUIRE(buffer[0] == 1);
    REQUIRE(buffer[1] == 2);

    // Check that popping from an empty buffer throws exception
    buffer.pop();
    buffer.pop();
    REQUIRE_THROWS_AS(buffer.pop(), std::underflow_error);
}

