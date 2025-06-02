#include "colors.h"
#include "dataUtils.h"
#include <cstddef>
#include <stdexcept>

namespace MattKavs {
namespace colors {


// Convert a hex string
RGB hexToRGB(std::string_view hex) {
  // Store data in a temp string for processing
  std::string hexColor{ hex };

  // Verify hexColor isnt empty
  if(hexColor.empty())
    throw std::runtime_error("Invalid RGB hex color string: string is empty");

  // Remove leading '#' if present
  if(hexColor[0] == '#') 
    hexColor = hexColor.substr(1);

  // Validate string length for 6-digit hex code
  if(hexColor.size() != 6)
    throw std::runtime_error("Invalid RGB hex string: expected 6 hex digits");

  // Convert the string to all uppercase
  MattKavs::dataUtils::strToUpper(hexColor);

  // Validate each char for valid hex digits
  MattKavs::dataUtils::validateHexString(hexColor);

  // We have a valid hex string so convert to RGB values
  return RGB{
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(0, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(2, 2), nullptr, 16)),
    static_cast<std::uint8_t>(std::stoi(hexColor.substr(4, 2), nullptr, 16))
  };
};

RGBA hexToRGBA(std::string_view hex) {
  // Store data in a temp string for processing
  std::string hexColor{ hex };

  // Verify hexColor isnt empty
  if(hexColor.empty())
    throw std::runtime_error("Invalid RGBA hex color string: string is empty");

  // Remove leading '#' if present
  if(hexColor[0] == '#')
    hexColor = hexColor.substr(1);
  
  // Extract the length of the string
  std::size_t length = hexColor.size();

  // Validate string length for 8-digit hex code
  if(length != 8)
    throw std::runtime_error("Invalid RGBA hex string: expected 8 hex digits");

  // Convert the string to all uppercase
  MattKavs::dataUtils::strToUpper(hexColor);

  // Extract the main color into an RGB object
  RGB baseColor{ hexToRGB(hexColor.substr(0, length - 2)) }; // Start at idx 0 and extract all but last 2 chars

  // Extract the Alpha channel
  std::string alphaChannel{ hexColor.substr(length - 2) }; // Extract the last 2 chars

  // Validate the Alpha channel hex chars (the rest are validated elsewhere
  MattKavs::dataUtils::validateHexString(alphaChannel);

  return RGBA{ baseColor, static_cast<std::uint8_t>(std::stoi(alphaChannel, nullptr, 16)) };
}

// Convert an RGB/A object to a hex string
std::string RGBtoHex(const RGB& color) {
  return "#" + dataUtils::toHex(color.r) + dataUtils::toHex(color.g) + dataUtils::toHex(color.b);
}
std::string RGBAtoHex(const RGBA& color) {
  return "#" + dataUtils::toHex(color.r) + dataUtils::toHex(color.g) + dataUtils::toHex(color.b) + dataUtils::toHex(color.a);
}
}   // namespace colors
}   // namespace MattKavs
