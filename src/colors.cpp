#include "colors.h"

namespace MattKavs {
namespace colors {

// Convert a hex string
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
  if(hexColor[0] == '#') {    // If first character is '#', 
      hexColor = hexColor.substr(1, 6); // Extract the substring directly following it
  }

  return RGB{ // Convert each pair of chars into an RGB object
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(0, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(2, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(4, 2), nullptr, 16))
  };
};

}   // namespace colors
}   // namespace MattKavs
