#include "Utils.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_session.hpp"

int main( int argc, char* argv[] ) {
  // your setup ...

  int result = Catch::Session().run( argc, argv );

  // your clean-up...

  return result;
}

TEST_CASE("Test case 1", "[Vec2D]")
{
    std::vector<std::vector<int>> rawVector = {
       { 1, 2, 3 },
       { 4, 5, 6 },
       { 7, 8, 9 }
    };
    Vec2D<int> vec2D(rawVector);

    REQUIRE(vec2D.at(0, 0) == 1);
    REQUIRE(vec2D.at(0, 1) == 2);
    REQUIRE(vec2D.at(0, 2) == 3);
    REQUIRE(vec2D.at(1, 0) == 4);
    REQUIRE(vec2D.at(1, 1) == 5);
    REQUIRE(vec2D.at(1, 2) == 6);
    REQUIRE(vec2D.at(2, 0) == 7);
    REQUIRE(vec2D.at(2, 1) == 8);
    REQUIRE(vec2D.at(2, 2) == 9);
}

TEST_CASE("Construction")
{
    SECTION("Size constructor")
    {
        Vec2D<int> vec2D(5, 4);
        auto [width, height] = vec2D.dim();
        REQUIRE(width == 5);
        REQUIRE(height == 4);
    }

    SECTION("Size and default value constructor")
    {
        Vec2D<int> vec2D(5, 4, 1);
        auto [width, height] = vec2D.dim();
        REQUIRE(width == 5);
        REQUIRE(height == 4);
        REQUIRE(vec2D.at(0, 0) == 1);
    }

    SECTION("Raw 2D vector constructor")
    {
        std::vector<std::vector<int>> rawVector = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        Vec2D<int> vec2D(rawVector);
        auto [width, height] = vec2D.dim();
        REQUIRE(width == 3);
        REQUIRE(height == 3);
        REQUIRE(vec2D(0, 0) == 1);
        REQUIRE(vec2D(1, 0) == 2);
        REQUIRE(vec2D(2, 0) == 3);
        REQUIRE(vec2D(0, 1) == 4);
        REQUIRE(vec2D(1, 1) == 5);
        REQUIRE(vec2D(2, 1) == 6);
        REQUIRE(vec2D(0, 2) == 7);
        REQUIRE(vec2D(1, 2) == 8);
        REQUIRE(vec2D(2, 2) == 9);
    }
}

TEST_CASE("Modifiers")
{
    Vec2D<int> vec2D(3, 3, 1);

    SECTION("Fill")
    {
        vec2D.fill(2);
        REQUIRE(vec2D.at(0, 0) == 2);
        REQUIRE(vec2D.at(1, 0) == 2);
        REQUIRE(vec2D.at(2, 0) == 2);
        REQUIRE(vec2D.at(0, 1) == 2);
        REQUIRE(vec2D.at(1, 1) == 2);
        REQUIRE(vec2D.at(2, 1) == 2);
        REQUIRE(vec2D.at(0, 2) == 2);
        REQUIRE(vec2D.at(1, 2) == 2);
        REQUIRE(vec2D.at(2, 2) == 2);
    }

    SECTION("Clear")
    {
        vec2D.clear();
        REQUIRE(vec2D.empty());
    }
}

TEST_CASE("Observers")
{
    Vec2D<int> vec2D(3, 3, 1);

    SECTION("Data")
    {
        auto data = vec2D.getData();
        REQUIRE(data[0] == 1);
        REQUIRE(data[1] == 1);
        REQUIRE(data[2] == 1);
        REQUIRE(data[3] == 1);
        REQUIRE(data[4] == 1);
        REQUIRE(data[5] == 1);
        REQUIRE(data[6] == 1);
        REQUIRE(data[7] == 1);
        REQUIRE(data[8] == 1);
    }

    SECTION("Find")
    {
        REQUIRE(vec2D.find(1).has_value());
        REQUIRE(vec2D.find(1).value().first == 0);
        REQUIRE(vec2D.find(1).value().second == 0);
        REQUIRE(vec2D.find(2).has_value() == false);
    }
}

TEST_CASE("Operations")
{
    Vec2D<int> vec2D1(3, 3, 1);
    Vec2D<int> vec2D2(3, 3, 2);

    SECTION("Swap")
    {
        vec2D1.swap(vec2D2);
        REQUIRE(vec2D1.at(0, 0) == 2);
        REQUIRE(vec2D2.at(0, 0) == 1);
    }

    SECTION("Addition")
    {
        auto vec2D3 = vec2D1 + vec2D2;
        REQUIRE(vec2D3.at(0, 0) == 3);
        REQUIRE(vec2D3.at(1, 0) == 3);
        REQUIRE(vec2D3.at(2, 0) == 3);
        REQUIRE(vec2D3.at(0, 1) == 3);
        REQUIRE(vec2D3.at(1, 1) == 3);
        REQUIRE(vec2D3.at(2, 1) == 3);
        REQUIRE(vec2D3.at(0, 2) == 3);
        REQUIRE(vec2D3.at(1, 2) == 3);
        REQUIRE(vec2D3.at(2, 2) == 3);
    }

    SECTION("Subtraction")
    {
        auto vec2D3 = vec2D1 - vec2D2;
        REQUIRE(vec2D3.at(0, 0) == -1);
        REQUIRE(vec2D3.at(1, 0) == -1);
        REQUIRE(vec2D3.at(2, 0) == -1);
        REQUIRE(vec2D3.at(0, 1) == -1);
        REQUIRE(vec2D3.at(1, 1) == -1);
        REQUIRE(vec2D3.at(2, 1) == -1);
        REQUIRE(vec2D3.at(0, 2) == -1);
        REQUIRE(vec2D3.at(1, 2) == -1);
        REQUIRE(vec2D3.at(2, 2) == -1);
    }
}