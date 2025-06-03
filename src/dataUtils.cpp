#include "dataUtils.h"

#include <cstdint>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdexcept>

// TODO:
// Add JSON formatting utils

namespace MattKavs {
namespace dataUtils {
  void strToUpper(std::string& str) {
    for(char& ch : str) {
      ch = std::toupper(static_cast<unsigned char>(ch));
    }
  }

  bool isHexDigit(const char& digit) {
    // Check if char is between 0-9 or A-F
    if((digit >= '0' && digit <= '9') || (digit >= 'A' && digit <= 'F') || (digit >= 'a' && digit <= 'f'))
      return true;
    return false;
  }

  // Helper to validate a hex string's characters (1-0 | A-F)
  void validateHexString(const std::string& hex) {
    for (const char& digit : hex) {
      if (!isHexDigit(digit))
        throw std::runtime_error("Invalid character in hex color string");
    }
  }
  
  std::string toHex(std::uint8_t value) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
    return ss.str();
  }

} // namespace dataUtils
} // namespace MattKavs
