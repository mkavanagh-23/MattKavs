#include "colors.h"
#include <catch2/catch_test_macros.hpp>

// Test conversions from Hex String to RGB objects
TEST_CASE("colors::hexToRGB handles leading '#'", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("#800080") == MattKavs::colors::RGB{ 128, 0, 128 });
  REQUIRE(MattKavs::colors::hexToRGB("#AF1234") == MattKavs::colors::hexToRGB("AF1234"));
}

TEST_CASE("colors::hexToRGB handles no leading '#'", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("800080") == MattKavs::colors::RGB{ 128, 0, 128 });
}

TEST_CASE("colors::hexToRGB converts primary colors", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("#FF0000" ) == MattKavs::colors::RGB{ 255, 0, 0 });
  REQUIRE(MattKavs::colors::hexToRGB("#00FF00" ) == MattKavs::colors::RGB{ 0, 255, 0 });
  REQUIRE(MattKavs::colors::hexToRGB("#0000FF" ) == MattKavs::colors::RGB{ 0, 0, 255 });
}

TEST_CASE("colors::hexToRGB converts secondary colors", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("#FFFF00" ) == MattKavs::colors::RGB{ 255, 255, 0 });
  REQUIRE(MattKavs::colors::hexToRGB("#FF00FF" ) == MattKavs::colors::RGB{ 255, 0, 255 });
  REQUIRE(MattKavs::colors::hexToRGB("#00FFFF" ) == MattKavs::colors::RGB{ 0, 255, 255 });
}

TEST_CASE("colors::hexToRGB converts monochromatic colors", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("#000000" ) == MattKavs::colors::RGB{ 0, 0, 0 });
  REQUIRE(MattKavs::colors::hexToRGB("#FFFFFF" ) == MattKavs::colors::RGB{ 255, 255, 255 });
  REQUIRE(MattKavs::colors::hexToRGB("#808080" ) == MattKavs::colors::RGB{ 128, 128, 128 });
}

TEST_CASE("colors::hexToRGB throws on empty input string", "[colors]") {
  REQUIRE_THROWS(MattKavs::colors::hexToRGB(""));
}

TEST_CASE("colors::hexToRGB throws on invalid input size", "[colors]") {
  // test too small
  REQUIRE_THROWS(MattKavs::colors::hexToRGB("010A"));
  // test 6 digits with '#'
  REQUIRE_THROWS(MattKavs::colors::hexToRGB("#010A1"));
  // test too large
  REQUIRE_THROWS(MattKavs::colors::hexToRGB("FFFFFFA"));
}

// TODO: Test hexToRGBA

//TEST_CASE("colors::hexToRGBA converts full alpha (FF)", "[colors]") {
//
//}
//
//TEST_CASE("colors::hexToRGBA converts partial alpha values", "[colors]") {
//
//}
//
//TEST_CASE("colors::hexToRGBA converts zero alpha values (00)", "[colors]") {
//
//}
//
//TEST_CASE("colors::hexToRGBA works under edge cases (opaque white and clear black", "[colors]") {
//
//}
//
//TEST_CASE("colors::hexToRGBA throws on empty input string", "[colors]") {
//
//}
//
//TEST_CASE("colors::hexToRGBA throws on invalid input size", "[colors]") {
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//// Test conversion from RGB objects to hex strings
//TEST_CASE("colors::RGBtoHex creates a 7-digit string (contains leading '#'", "[colors]") {
//
//}
//
//TEST_CASE("colors::RGBAtoHex creates a 9-digit string (contains leading '#'", "[colors]") {
//
//}
//
//// Test operator<< overload for printing RGB and RGBA objects
//TEST_CASE("RGB objects are successfully converted to ostream", "[colors]") {
//
//}
//
//TEST_CASE("RGBA objects are successfully converted to ostream", "[colors]") {
//
//}

