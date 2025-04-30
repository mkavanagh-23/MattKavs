#include "input.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <streambuf>
#include <string>

namespace TestHelpers {
// Define an object for iostream redirection
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

TEST_CASE("input::hasUnextractedData returns true for remaining input after extraction", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("42 this is unextracted string data\n");

  // Load true case and test extraction
  int number;
  std::cin >> number;
  // Verify unextracted output
  REQUIRE(number == 42);
  REQUIRE(MattKavs::input::hasUnextractedData());
}

TEST_CASE("input::hasUnextractedData returns false if all data was extracted", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("This test will extract all data\n");

  // Test False extraction
  std::string text;
  std::getline(std::cin, text);
  // Verify complete extraction
  REQUIRE(text == "This test will extract all data");
  REQUIRE_FALSE(MattKavs::input::hasUnextractedData());
}

TEST_CASE("input::failure returns true for invalid input", "[input]") {
  // Create a redirected teast stream
  TestHelpers::StreamRedirect redirect("Thisisnotanumber\n");

  int number;
  std::cin >> number;

  REQUIRE(MattKavs::input::failure());
}

TEST_CASE("input::reset clears cin error state and ignores to newline char", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("invalid\n123\n");

  int number;
  std::cin >> number;   // This should fail
  REQUIRE(MattKavs::input::failure());

  MattKavs::input::reset(); // reset clears error state and ignores chars up to '\n'
  std::cin >> number;   // This should pass and extract the second line
  REQUIRE_FALSE(MattKavs::input::failure());
  REQUIRE(number == 123);
}

TEST_CASE("input::extract successfully reads int values", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("42\n");

  int number;
  bool success = MattKavs::input::extract(number);
  REQUIRE(success);
  REQUIRE(number == 42);
}

TEST_CASE("input::extract successfully reads string values with spaces", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("This is a string value with spaces\n");

  std::string message;
  bool success = MattKavs::input::extract(message);
  REQUIRE(success);
  REQUIRE(message == "This is a string value with spaces");
}

TEST_CASE("input::extract returns false on invalid int input", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("Thisisnotanint\n");

  int number;
  bool success = MattKavs::input::extract(number);
  REQUIRE_FALSE(success);
}

TEST_CASE("input::extract returns false on empty string input", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect(""); // Test an empty input stream

  std::string message = "placeholder";
  bool success = MattKavs::input::extract(message);
  REQUIRE_FALSE(success);
  REQUIRE(message.empty());
}

TEST_CASE("input::get<T> reads input with prompt", "[input]") {
  // Create a redirected test stream
  TestHelpers::StreamRedirect redirect("123\n"); // Test an empty input stream

  int number = MattKavs::input::get<int>("Enter number: ");
  REQUIRE(number == 123);
  REQUIRE(redirect.output() == "Enter number: ");
}

TEST_CASE("input::get<T> retries on failure", "[input]") {
  // Create redirected test streams
  TestHelpers::StreamRedirect redirect("abc\n123\n");

  int number = MattKavs::input::get<int>("Enter valid int: ");
  REQUIRE(number == 123);

  // Output should prompt twice
  REQUIRE(redirect.output() == "Enter valid int: Enter valid int: ");
}
