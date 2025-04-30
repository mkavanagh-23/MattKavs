#include "colors.h"
#include <cstddef>
#include <stdexcept>

namespace MattKavs {
namespace colors {

// Convert a hex string
// TODO: Define a MattKavs::DataUtils namespace which contains:
//    all uppercase string function (toUpper())
//    hex digit validation function (isHexDigit())
// FIX: Function can take in a 6 or 7 char string object
// If the length is 7, the first char must be a #
// If the length is 6, the first char must be alphanumeric
// Add exceptions for invalid input values
// If we pass this, then remove the '#'
// Each Char after must be a valid hex digit ('1' - 'F')
// Should normalize case to all upper - need to define a string processing function
// Create test cases and build from a test-drivcen context
// The same should be implemented for colors with alpha values, using an 8 or 9 char string
RGB hexToRGB(std::string_view hex) {
  std::string hexColor{ hex };  // Store the value in a temp string for processing

  // Extract the length of the input string
  std::size_t length = hexColor.size();

  // Remove leading '#' if present
  if(hexColor[0] == '#') {    // If first character is '#', 
      hexColor = hexColor.substr(1, length - 1); // Extract the substring directly following it
  }

  // Extract the new length value
  length = hexColor.size();
  if(length != 6)
    throw std::runtime_error("Attempted to convert hex color string with invalid length");

  // Validate each char for valid hex digits
  for(const auto& digit : hexColor) { // check if each digit is a valid hex digit
    if(!Mattkavs::dataUtils::isHexDigit(digit)) {
      throw std::runtime_error("Attempted to convert hex color string with invalid contents");
    }
  }

  return RGB{ // Convert each pair of chars into an RGB object
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(0, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(2, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(4, 2), nullptr, 16))
  };
};

}   // namespace colors
}   // namespace MattKavs
