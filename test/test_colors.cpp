#include "colors.h"
#include <catch2/catch_test_macros.hpp>

// Test conversions from Hex String to RGB objects

// TODO:
// Need to define constructor for creating RGB and RGBA objects
// Need to define equality/isEqual() function to allow for object comparison
TEST_CASE("colors::hexToRGB handles leading '#'", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("#800080") == MattKavs::colors::RGB{128, 0, 128});
}

TEST_CASE("colors::hexToRGB handles no leading '#'", "[colors]") {
  REQUIRE(MattKavs::colors::hexToRGB("800080") == MattKavs::colors::RGB{128, 0, 128});
}

TEST_CASE("colors::hexToRGB converts to uppercase values", "[colors]") {

}

TEST_CASE("colors::hexToRGB converts primary colors", "[colors]") {

}

TEST_CASE("colors::hexToRGB converts secondary colors", "[colors]") {

}

TEST_CASE("colors::hexToRGB converts monochromatic colors", "[colors]") {

}

TEST_CASE("colors::hexToRGB throws a runtime on invalid input size", "[colors]") {

}

TEST_CASE("colors::hexToRGB throws a runtime error on non-hex values", "[colors]") {

}

TEST_CASE("colors::hexToRGBA converts full alpha (FF)", "[colors]") {

}

TEST_CASE("colors::hexToRGBA converts partial alpha values", "[colors]") {

}

TEST_CASE("colors::hexToRGBA converts zero alpha values (00)", "[colors]") {

}

TEST_CASE("colors::hexToRGBA works under edge cases (opaque white and clear black", "[colors]") {

}

// Test conversion from RGB objects to hex strings
TEST_CASE("colors::RGBtoHex creates a 7-digit string (contains leading '#'", "[colors]") {

}

TEST_CASE("colors::RGBAtoHex creates a 9-digit string (contains leading '#'", "[colors]") {

}

// Test operator<< overload for printing RGB and RGBA objects
TEST_CASE("RGB objects are successfully converted to ostream", "[colors]") {

}

TEST_CASE("RGBA objects are successfully converted to ostream", "[colors]") {

}

