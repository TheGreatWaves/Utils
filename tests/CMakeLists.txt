# Specify the test executable and its source files
add_executable(All_tests CircularBuffer_test.cpp Vec2D_test.cpp "tmain.cpp")

# Link the test executable with the Catch2 library
target_link_libraries(All_tests PRIVATE Catch2::Catch2)

# Set the include directories for the test executable
target_include_directories(All_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

# Add the tests to the project
add_test(NAME All_tests COMMAND All_tests)
