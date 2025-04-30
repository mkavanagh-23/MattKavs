#ifndef MATTKAVS_COLORS_H
#define MATTKAVS_COLORS_H

#include <cstdint>
#include <iostream>
#include <string_view>

namespace MattKavs {
namespace colors {

struct RGB {
  std::uint8_t r { 255 };
  std::uint8_t g { 255 };
  std::uint8_t b { 255 };

  // Overide Operator<< to print the object
  friend std::ostream& operator<<(std::ostream& out, const RGB& color);
};  // End RGB

struct RGBA: public RGB {
  std::uint8_t a{ 255 };    // Alpha transparency
};

// Convert a hex color value to an RGB/A object
RGB hexToRGB(std::string_view hex);
RGBA hexToRGBA(std::string_view hex);

// Convert an RGB/A object to a hex string
std::string RGBtoHex(const RGB& color);
std::string RGBAtoHex(const RGBA& color);

} // namespcae colors
} // namespace MattKavs

#endif
