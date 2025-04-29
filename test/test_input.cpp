#include "input.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <streambuf>
#include <string>

TEST_CASE("Input::ignoreLine() clears remaining input", "[input]") {
    // Load sample input into the std::cin stream
    std::istringstream input("42 this is extraneous data\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    // Test extracting the integer value
    int number;
    std::cin >> number;
    Input::ignoreLine();

    // Verify extraction and stream state
    REQUIRE(number == 42);
    REQUIRE(std::cin.peek() == std::char_traits<char>::eof());

    // Restore cin to the original input stream
    std::cin.rdbuf(orig);
}