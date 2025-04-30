#include "input.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <streambuf>
#include <string>

namespace TestHelpers {
// Define a class for iostream redirection
struct StreamRedirect {
  std::streambuf* origCin;
  std::streambuf* origCout;
  std::istringstream testIn;
  std::ostringstream testOut;

  StreamRedirect(const std::string& inputData)
  : origCin(std::cin.rdbuf()), origCout(std::cout.rdbuf()), testIn(inputData) {
    std::cin.rdbuf(testIn.rdbuf());
    std::cout.rdbuf(testOut.rdbuf());
  }

  ~StreamRedirect() {
      std::cin.rdbuf(origCin);
      std::cout.rdbuf(origCout);
  }

  std::string output() const { return testOut.str(); }
};
} // namespace TestHelpers

TEST_CASE("input::ignoreLine clears remaining input", "[input]") {

  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("42 this is extraneous data\n");

  // Test extracting the integer value
  int number;
  std::cin >> number;
  MattKavs::input::ignoreLine();

  // Verify extraction and stream state
  REQUIRE(number == 42);
  REQUIRE(std::cin.peek() == std::char_traits<char>::eof());
}

// TODO: Modify the rest of the tests to utilize our StreamRedirect object

TEST_CASE("input::hasUnextractedData returns true for remaining input after extraction", "[input]") {
  // Load the sample input streams
  std::istringstream input("42 this test will return true\n");

  // Store a ptr to original cin and load false case
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  // Load true case and test extraction
  int number;
  std::cin >> number;
  // Verify TRUE extraction
  REQUIRE(number == 42);
  REQUIRE(MattKavs::input::hasUnextractedData());

  // Restore cin to the original input stream
  std::cin.rdbuf(orig);
}

TEST_CASE("input::hasUnextractedData returns false if all data was extracted", "[input]") {
  // Load the sample input streams
  std::istringstream input("This test will return false\n");

  // Store a ptr to original cin and load false case
  std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

  // Test False extraction
  std::string text;
  std::getline(std::cin, text);
  // Verify FALSE extraction
  REQUIRE(text == "This test will return false");
  REQUIRE_FALSE(MattKavs::input::hasUnextractedData());

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

TEST_CASE("input::get<T> reads input with prompt", "[input]") {
  std::istringstream input("123\n");
  std::ostringstream output;
  std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
  std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());

  int number = MattKavs::input::get<int>("Enter number: ");
  REQUIRE(number == 123);
  REQUIRE(output.str() == "Enter number: ");

  std::cin.rdbuf(origCin);
  std::cout.rdbuf(origCout);
}

TEST_CASE("input::get<T> retries on failure", "[input]") {
  std::istringstream input("abc\n123\n");
  std::ostringstream output;
  std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
  std::streambuf* origCout = std::cout.rdbuf(output.rdbuf());

  int number = MattKavs::input::get<int>("Enter valid int: ");
  REQUIRE(number == 123);

  // Output should prompt twice
  REQUIRE(output.str() == "Enter valid int: Enter valid int: ");

  std::cin.rdbuf(origCin);
  std::cout.rdbuf(origCout);
}
