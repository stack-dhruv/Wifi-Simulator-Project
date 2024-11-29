#include "DisplayParser.h"
#include <iostream>
#include <iomanip>

// Template function to display integers and strings with color formatting
template <typename T>
void DisplayParser<T>::display(const T& data) const {
    if constexpr (std::is_integral<T>::value) {
        displayInt(data);  // Call the helper function for integers
    } else if constexpr (std::is_same<T, std::string>::value) {
        displayString(data);  // Call the helper function for strings
    }
}

// Helper function to display integers in cyan (bold)
template <typename T>
void DisplayParser<T>::displayInt(int data) const {
    std::cout << "\033[1;36m" << data << "\033[0m"; // Cyan color (bold)
}

// Helper function to display strings in green
template <typename T>
void DisplayParser<T>::displayString(const std::string& data) const {
    std::cout << "\033[1;32m" << data << "\033[0m"; // Green color
}

// Explicit template instantiations for supported types
template class DisplayParser<int>;
template class DisplayParser<std::string>;
