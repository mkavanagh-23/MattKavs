#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>
#include <sstream>
#include <streambuf>

namespace TestHelpers {
// Define an object for iostream redirection
struct StreamRedirect {
  std::streambuf* origCin;
  std::streambuf* origCout;
  std::istringstream testIn;
  std::ostringstream testOut;

  StreamRedirect(const std::string& inputData)
  : origCin(std::cin.rdbuf()), origCout(std::cout.rdbuf()), testIn(inputData) {
    std::cin.rdbuf(testIn.rdbuf());
    std::cout.rdbuf(testOut.rdbuf());
  }

  ~StreamRedirect() {
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
  }

  std::string output() const { return testOut.str(); }
};
} // namespace TestHelpers

#endif
