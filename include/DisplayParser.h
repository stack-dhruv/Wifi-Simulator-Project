#ifndef DISPLAYPARSER_H
#define DISPLAYPARSER_H

#include <iostream>
#include <string>

template <typename T>
class DisplayParser {
public:
    // Display function to handle any type of input
    void display(const T& data) const;

private:
    // Helper function for displaying integers in cyan color (bold)
    void displayInt(int data) const;

    // Helper function for displaying strings in green color
    void displayString(const std::string& data) const;
};

#endif
