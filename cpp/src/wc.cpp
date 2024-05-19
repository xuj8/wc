#include "wc.h"
#include <CLI11.hpp>
#include <iostream>

WcConfig::WcConfig(int argc, char* argv[]) {
    parse_args(argc, argv);
}

void WcConfig::parse_args(int argc, char* argv[]) {
    CLI::App app{"cpp implementation of wc"};
    app.add_option("filename", filename, "File to process (optional, defaults to reading from stdin)")
        ->default_val("");
    app.add_flag("-c", count_bytes, "Count the number of bytes");
    app.add_flag("-l", count_lines, "Count the number of lines");
    app.add_flag("-w", count_words, "Count the number of words");
    app.add_flag("-m", count_chars, "Count the number of characters");
    app.parse(argc, argv);

    if (!count_bytes && !count_lines && !count_words && !count_chars) {
        // default option: 
        count_bytes = true;
        count_lines = true;
        count_words = true;
    }
}

// we're gonna have to process byte by byte because we cannot seek to 0 in the case of cin nor store the 
// entire thing in memory.
std::vector<size_t> handle_queries(std::istream& stream, const WcConfig& config) {
    std::vector<size_t> answers;

    size_t num_lines = 0, num_words = 0, num_chars = 0, num_bytes = 0;

    bool was_whitespace = true;

    BufferReader input(stream);

    while(input) {
        auto [cur_code_point, cur_bytes] = next_code_point(input);

        // if (cur_bytes > 1) {
        //     std::cout << "found > 1 char\n";
        // }

        // process bytes
        num_bytes += cur_bytes;

        // process lines
        num_lines += is_newline(cur_code_point);

        // process words

        // we increment the number of words when the last character was a whitespace or beginning of the file
        // and the current character isn't
        bool cur_is_whitespace = is_unicode_whitespace(cur_code_point);
        if (was_whitespace && !cur_is_whitespace) num_words++;
        was_whitespace = cur_is_whitespace; 

        // process chars
        // we increment character count on beginning of a utf8 encoded character
        num_chars++;
    }
    
    if (config.count_lines) answers.push_back(num_lines);
    if (config.count_words) answers.push_back(num_words);
    if (config.count_chars) answers.push_back(num_chars);
    if (config.count_bytes) answers.push_back(num_bytes);

    return answers;
}
