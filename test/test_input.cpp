#include "input.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <streambuf>
#include <string>

TEST_CASE("input::ignoreLine() clears remaining input", "[input]") {
    // Load sample input into the std::cin stream
    std::istringstream input("42 this is extraneous data\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    // Test extracting the integer value
    int number;
    std::cin >> number;
    MattKavs::input::ignoreLine();

    // Verify extraction and stream state
    REQUIRE(number == 42);
    REQUIRE(std::cin.peek() == std::char_traits<char>::eof());

    // Restore cin to the original input stream
    std::cin.rdbuf(orig);
}

TEST_CASE("input::hasUnextractedData() checks for remaining input after extraction", "[input]") {
  // Load the sample input streams
  std::istringstream inputFalse("This test will return false\n");
  std::istringstream inputTrue("42 This test will return true\n");

  // Store a ptr to original cin and load false case
  std::streambuf* orig = std::cin.rdbuf(inputFalse.rdbuf());

  // Test False extraction
  std::string text;
  std::getline(std::cin, text);
  // Verify FALSE extraction
  REQUIRE(!MattKavs::input::hasUnextractedData());

  // Load true case and test extraction
  std::cin.rdbuf(inputTrue.rdbuf());
  int number;
  std::cin >> number;
  // Verify TRUE extraction
  REQUIRE(MattKavs::input::hasUnextractedData());

  // Restore cin to the original input stream
  std::cin.rdbuf(orig);
}

TEST_CASE("input::failure() checks for failed extraction of data", "[input]") {
  // Load the sample input stream
  std::istringstream input("Thisisnotanumber\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  int number;
  std::cin >> number;

  REQUIRE(MattKavs::input::failure());

  std::cin.rdbuf(orig);
}
