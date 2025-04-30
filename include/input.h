#ifndef MATTKAVS_INPUT_H
#define MATTKAVS_INPUT_H

#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

namespace MattKavs {
namespace input {
    // Clear the input buffer up to '/n'
    void ignoreLine();
    // Check for remaining input after extraction
    bool hasUnextractedData();
    // Check for failed extraction
    bool failure();
    // Reset and clear input stream
    void reset();

    // Internal helper: extract input correctly depending on type
    template <typename T>
    bool extract(T& dest) {
        // Check for string type argument
        if constexpr (std::is_same_v<T, std::string>) {
            // Extract the entire line (incl spaces)
            std::getline(std::cin, dest);
            // Check for failure
            if (dest.empty() && std::cin.eof()) {
                reset();
                return false;
            }
        } else {
            // Extract normally for the type
            std::cin >> dest;
            // Check for failure
            if (failure()) {
                if(std::cin.eof())
                    std::exit(1);
                reset();
                return false;
            }
            // Clear the input buffer
            ignoreLine();
        }
        return true;
    }

    // Extract a value into the dest object
    template <typename T>
    void get(std::string_view message, T& dest) {
        while (true) {
            std::cout << message;
            // Get input from the user
            if (extract(dest))
                return;
        }
    }

    // Get a value of type T
    template <typename T>
    T get(std::string_view message) {
        T dest;
        // Get input from the user
        get(message, dest);
        return dest;
    }
} // namespace input

} // namespace MattKavs

#endif
