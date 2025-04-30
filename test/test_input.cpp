#include "input.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <streambuf>
#include <string>

TEST_CASE("input::ignoreLine clears remaining input", "[input]") {
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

TEST_CASE("input::hasUnextractedData returns true for remaining input after extraction", "[input]") {
  // Load the sample input streams
  std::istringstream inputFalse("This test will return false\n");
  std::istringstream inputTrue("42 this test will return true\n");

  // Store a ptr to original cin and load false case
  std::streambuf* orig = std::cin.rdbuf(inputFalse.rdbuf());

  // Test False extraction
  std::string text;
  std::getline(std::cin, text);
  // Verify FALSE extraction
  REQUIRE_FALSE(MattKavs::input::hasUnextractedData());

  // Load true case and test extraction
  std::cin.rdbuf(inputTrue.rdbuf());
  int number;
  std::cin >> number;
  // Verify TRUE extraction
  REQUIRE(MattKavs::input::hasUnextractedData());

  // Restore cin to the original input stream
  std::cin.rdbuf(orig);
}

TEST_CASE("input::failure returns true for invalid input", "[input]") {
  // Load the sample input stream
  std::istringstream input("Thisisnotanumber\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  int number;
  std::cin >> number;

  REQUIRE(MattKavs::input::failure());

  std::cin.rdbuf(orig);
}

TEST_CASE("input::reset clears cin error state and ignores to newline char", "[input]") {
  std::istringstream input("invalid\n123\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  int number;
  std::cin >> number;   // This should fail
  REQUIRE(MattKavs::input::failure());

  MattKavs::input::reset(); // reset clears error state and ignores chars up to '\n'
  std::cin >> number;   // This should pass and extract the second line
  REQUIRE_FALSE(MattKavs::input::failure());
  REQUIRE(number == 123);

  std::cin.rdbuf(orig);
}

TEST_CASE("input::extract successfully reads int values", "[input]") {
  std::istringstream input("42\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  int number;
  bool success = MattKavs::input::extract(number);
  REQUIRE(success);
  REQUIRE(number == 42);

  std::cin.rdbuf(orig);
}

TEST_CASE("input::extract successfully reads string values with spaces", "[input]") {
  std::istringstream input("This is a string value with spaces\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  std::string message;
  bool success = MattKavs::input::extract(message);
  REQUIRE(success);
  REQUIRE(message == "This is a string value with spaces");

  std::cin.rdbuf(orig);
}

TEST_CASE("input::extract returns false on invalid int input", "[input]") {
  std::istringstream input("Thisisnotanint\n");
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  int number;
  bool success = MattKavs::input::extract(number);
  REQUIRE_FALSE(success);

  std::cin.rdbuf(orig);
}

TEST_CASE("input::extract returns false on empty string input", "[input]") {
  std::istringstream input(""); // Test an empty string
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  std::string message = "placeholder";
  bool success = MattKavs::input::extract(message);
  REQUIRE_FALSE(success);
  REQUIRE(message.empty());

  std::cin.rdbuf(orig);
}
