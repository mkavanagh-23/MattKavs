#include "dataUtils.h"
#include <catch2/catch_test_macros.hpp>
#include <array>

TEST_CASE("dataUtils::strToUpper converts lowercase chars in a string to uppercase", "[dataUtils]") {
  std::string test1{ "thiswillbeupper" };
  MattKavs::dataUtils::strToUpper(test1);
  REQUIRE(test1 == "THISWILLBEUPPER");

  std::string test2{ "MiXed c@sES & $yMbOls" };
  MattKavs::dataUtils::strToUpper(test2);
  REQUIRE(test2 == "MIXED C@SES & $YMBOLS");
}

TEST_CASE("dataUtils::isHexDigit returns true for 0-9 and A-F", "[dataUtils]") {
  std::array<char, 22> testChars{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    'A', 'B', 'C', 'D', 'E', 'F',
    'a', 'b', 'c', 'd', 'e', 'f'
  };
  
  for(const char& ch : testChars){
    REQUIRE(MattKavs::dataUtils::isHexDigit(ch));
  }
}

TEST_CASE("dataUtils::isHexDigit returns false for invalid digits", "[dataUtils]") {
  std::array<char, 3> testChars {
    'Z', '$', 'g'
  };

  for(const char& ch : testChars) {
    REQUIRE_FALSE(MattKavs::dataUtils::isHexDigit(ch));
  }
}

TEST_CASE("dataUtils::validateHexString throws on invalid chars", "[dataUtils]") {
  std::string test1{ "19FZ00" };
  REQUIRE_THROWS(MattKavs::dataUtils::validateHexString(test1));

  std::string test2{ "FFFFFF" };
  REQUIRE_NOTHROW(MattKavs::dataUtils::validateHexString(test2));
}
