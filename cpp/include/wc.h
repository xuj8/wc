#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include "buffer_reader.h"


struct WcConfig {
    std::string filename;
    bool count_bytes, count_lines, count_words, count_chars;

    WcConfig(int argc, char* argv[]);

    void parse_args(int argc, char* argv[]);
};

std::vector<size_t> handle_queries(std::istream& stream, const WcConfig& config);

// size_t count_words(std::istream& stream);

// size_t count_lines(std::istream& stream);

// size_t count_bytes(std::istream& stream);

// size_t count_chars(std::istream& stream);
