#ifndef MATTKAVS_DATAUTILS_H
#define MATTKAVS_DATAUTILS_H

#include <cstdint>
#include <string>

namespace MattKavs {
namespace dataUtils {
  // TODO: Build definitions for the following:
  bool isHexDigit(const char& digit);
  void validateHexString(const std::string& hex);
  void strToUpper(std::string& string);
  std::string toHex(std::uint8_t value);
} // namespace input
} // namespace dataUtils

#endif
