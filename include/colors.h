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

  // Construct an RGB object from vals
  RGB(std::uint8_t R, std::uint8_t G, std::uint8_t B)
  : r{ R }, g{ G }, b{ B }
  {}

  // Copy constructor
  RGB(const RGB& other)
  : r{ other.r }, g{ other.g }, b{ other.b }
  {}

  // Overload Assignment operator
  RGB& operator=(const RGB& other) {
    if(this != &other) {
      r = other.r;
      g = other.g;
      b = other.b;
    }
    return *this;
  }

  // Move semantics
  RGB(RGB&&) noexcept = default; 
  RGB& operator=(RGB&&) noexcept = default;

  // Destructor
  ~RGB() = default;

  // Overide Operator<< to print the object
  friend std::ostream& operator<<(std::ostream& out, const RGB& color);
  // Override comparison operators
  // Equality operator
  friend bool operator==(const RGB& lhs, const RGB& rhs) {
    return lhs.r == rhs.r &&
           lhs.g == rhs.g &&
           lhs.b == rhs.b;
  }
  // Inequal operator
  friend bool operator!=(const RGB& lhs, const RGB& rhs) {
    return !(lhs == rhs);
  }
};  // End RGB

struct RGBA: public RGB {
  std::uint8_t a{ 255 };    // Alpha transparency

  // Constructors
  RGBA(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A)
  : RGB{ R, G, B }, a{ A }
  {}

  RGBA(const RGB& rgb, std::uint8_t alpha)
  : RGB{ rgb }, a{ alpha }
  {}

  // Copy constructor
  RGBA(const RGBA& other)
  : RGB{ other }, a{ other.a }
  {}

  // Overload assignment operator
  RGBA& operator=(const RGBA& other) {
    if(this != &other) {
      RGB::operator=(other);
      a = other.a;
    }
    return *this;
  }

  // Move semantics
  RGBA(RGBA&&) noexcept = default;
  RGBA& operator=(RGBA&&) noexcept = default;
  
  // Destructor
  ~RGBA() = default;

  // Equality operator
  friend bool operator==(const RGBA& lhs, const RGBA& rhs) {
    // Reuse RGB's comparison logic
    return static_cast<const RGB&>(lhs) == static_cast<const RGB&>(rhs) &&
      lhs.a == rhs.a;
    }
    // Optional: not-equal operator
    friend bool operator!=(const RGBA& lhs, const RGBA& rhs) {
      return !(lhs == rhs);
    }
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
