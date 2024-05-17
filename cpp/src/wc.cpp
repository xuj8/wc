#include "wc.h"

size_t count_words(std::istream& stream) {
    size_t count=0;
    std::string cur_word;
    while(stream >> cur_word) count++;
    return count;
};

size_t count_lines(std::istream& stream) {
    size_t count=0;
    std::string cur_line;
    while(std::getline(stream, cur_line))
        count++;
    return count;
}

size_t count_bytes(std::istream& stream) {
    size_t count=0;
    std::string cur_line;
    
}

size_t count_chars(std::istream& stream) {
    
}