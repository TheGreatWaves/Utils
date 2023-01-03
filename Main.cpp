#include "Utils.hpp"
#include <iostream>

// Test here, make sure you discard it from the commit.
int main()
{
    std::vector<std::vector<int>> rawVector = {
       { 1, 2, 3 },
       { 4, 5, 6 },
       { 7, 8, 9 }
    };

    Vec2D<int> vec2D(rawVector);

    for (std::size_t y = 0; y < vec2D.height; ++y)
    {
        for (std::size_t x = 0; x < vec2D.width; ++x)
        {
            std::cout << vec2D(x, y) << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}