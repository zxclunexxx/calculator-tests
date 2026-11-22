#pragma once

#include <istream>
#include <ostream>
#include <string>

bool ParseInteger(const std::string& text, int& number);
bool ReadInteger(std::istream& input, std::ostream& output,
    const std::string& prompt, int& number);
bool ReadNumbers(std::istream& input, std::ostream& output,
    int& first, int& second);
