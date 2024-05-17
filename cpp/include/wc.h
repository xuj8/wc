#pragma once

#include <fstream>
#include <iostream>

size_t count_words(std::istream& stream);

size_t count_lines(std::istream& stream);

size_t count_bytes(std::istream& stream);

size_t count_chars(std::istream& stream);
