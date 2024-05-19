#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include "utils.h"

typedef uint32_t code_point_t;

struct Encoding {
    char mask, value;
    size_t extra;
};

static constexpr Encoding UTF8_ENCODING[] = {
    {0x80, 0x00, 0},
    {0xE0, 0xC0, 1},
    {0xF0, 0xE0, 2},
    {0xF8, 0xF0, 3}
};


// BufferReader state:
// next_pos points to the currently unread character.
// if it is null, then it means it has either reached EOF, or fail or bad bit in the stream
// calling next_byte with EOF or bad state will return a null
struct BufferReader {
    static constexpr size_t BUFFER_SIZE = 1 << 15;

    BufferReader(std::istream& _stream);

    operator bool() const {
        return good();
    }

    inline bool good() const {
        return next_pos.has_value();
    }

    inline std::optional<char> next_byte() {
        if (next_pos.has_value()) {
            char return_val = buffer[*next_pos];
            next_pos = *next_pos + 1;
            if (*next_pos >= cur_read_size) [[unlikely]] {
                update_buffer();    
            }
            return return_val;
        } else return std::nullopt;
    }

    inline std::optional<char> peek() {
        if (next_pos.has_value()) {
            char return_val = buffer[*next_pos];
            return return_val;
        } else return std::nullopt;
    }
private:
    void update_buffer();
    std::istream& stream;
    size_t cur_read_size;
    char buffer[BUFFER_SIZE];
    std::optional<size_t> next_pos;
};

inline code_point_t read_code_point(BufferReader& input, code_point_t result, size_t extra) {
    for(int i = 0; i < extra; i++) {
        if (!input) throw std::runtime_error("Stream premature stopping");
        code_point_t next = *input.next_byte();
        if ((next & 0xC0) != 0x80) throw std::runtime_error("Encountered invalid continuation character.");
        result = (result << 6) | (next & 0x3F);
    }
    return result;
}

inline std::pair<code_point_t, size_t> next_code_point(BufferReader& input) {
    if (!input) throw std::runtime_error("Stream no longer valid");
    code_point_t starting_char = *input.next_byte();
    
    for (const Encoding& encoding: UTF8_ENCODING) {
        if ((starting_char & encoding.mask) == encoding.value) {
            return {read_code_point(input, starting_char & ~encoding.mask, encoding.extra), encoding.extra + 1};
        }
    }

    throw std::runtime_error("Invalid first character");
}

inline bool is_unicode_whitespace(code_point_t code_point) {
    static const std::vector<code_point_t> unicode_whitespaces = {
        0x0009, // Tab
        0x000A, // Line Feed
        0x000B, // Vertical Tab
        0x000C, // Form Feed
        0x000D, // Carriage Return
        0x0020, // Space
        0x0085, // Next Line
        0x00A0, // No-Break Space
        0x1680, // Ogham Space Mark
        0x2000, // En Quad
        0x2001, // Em Quad
        0x2002, // En Space
        0x2003, // Em Space
        0x2004, // Three-Per-Em Space
        0x2005, // Four-Per-Em Space
        0x2006, // Six-Per-Em Space
        0x2007, // Figure Space
        0x2008, // Punctuation Space
        0x2009, // Thin Space
        0x200A, // Hair Space
        0x2028, // Line Separator
        0x2029, // Paragraph Separator
        0x202F, // Narrow No-Break Space
        0x205F, // Medium Mathematical Space
        0x3000  // Ideographic Space
    };
    for (uint32_t ws : unicode_whitespaces) {
        if (code_point == ws) {
            return true;
        }
    }
    return false;
}

inline bool is_newline(code_point_t code_point) {
    return code_point == 0x000A;
}

