# Specify the test executable and its source file
add_executable(VEC2D_test Vec2D_test.cpp)

# Link the test executable with the Catch2 library
target_link_libraries(VEC2D_test PRIVATE Catch2::Catch2)

# Set the include directories for the test executable
target_include_directories(VEC2D_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

# Add the test to the project
add_test(NAME VEC2D_test COMMAND VEC2D_test)
