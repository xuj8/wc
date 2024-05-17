#include "wc.h"
#include <CLI11.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    CLI::App app{"cpp implementation of wc"};
    std::string filename;
    bool count_bytes_flag = false;
    bool count_lines_flag = false;
    bool count_words_flag = false;
    bool count_chars_flag = false;

    app.add_option("-f,--file", filename, "File to process (optional, defaults to reading from stdin)")->default_val("");
    app.add_flag("-c", count_bytes_flag, "Count the number of bytes");
    app.add_flag("-l", count_lines_flag, "Count the number of lines");
    app.add_flag("-w", count_words_flag, "Count the number of words");
    app.add_flag("-m", count_chars_flag, "Count the number of characters");

    CLI11_PARSE(app, argc, argv);
    
    
    // set the right flags
    if (!count_bytes_flag && !count_lines_flag && !count_words_flag && !count_chars_flag) {
        // default option: 
        count_bytes_flag = true;
        count_lines_flag = true;
        count_words_flag = true;
    }

    // create istream handle
    std::ifstream file_stream; // it is necessary to put file_stream in same context as in, so it is RAII destroyed
    std::istream& in = [&]() -> std::istream& {
        if (filename.empty()) {
            file_stream.open(filename);
            return file_stream;
        } else {
            return std::cin;
        }
    }();

    // depending on flags, get arguments
    std::vector<size_t> answers;
    if (count_bytes_flag) answers.push_back(count_bytes(in));
    if (count_lines_flag) answers.push_back(count_lines(in));
    if (count_words_flag) answers.push_back(count_words(in));
    if (count_chars_flag) answers.push_back(count_chars(in));

    // print answer
    for (const auto& num: answers)
        std::cout << " " << num;

    if (!filename.empty())
        std::cout << " " << filename;

    std::cout << "\n";
}
