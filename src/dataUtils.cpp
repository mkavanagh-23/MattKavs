#include "dataUtils.h"

#include <string>
#include <stdexcept>

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
} // namespace dataUtils
} // namespace MattKavs
