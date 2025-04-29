#include "input.h"

#include <iostream>
#include <limits>

namespace MattKavs {
namespace input {
    // Clear the input buffer up to and including '\n'
    void ignoreLine() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

    // Check for remaining input after extraction
    bool hasUnextractedInput() {
      // Peek the next char
      int next = std::cin.peek();
      return next != EOF && next != '\n';
    }

    // Check for failed extraction
    bool failure() { return !std::cin; }
    
    // Reset and clear input stream
    void reset() {
        std::cin.clear();   // Reset the error state
        ignoreLine();       // And clear the buffer
    }
} // namespace input
} // namespace MattKavs
