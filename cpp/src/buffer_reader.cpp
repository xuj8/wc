#include "buffer_reader.h"

BufferReader::BufferReader(std::istream& _stream): stream(_stream) {
    update_buffer();
}

void BufferReader::update_buffer() {
    if (stream) {
        // attempt to read stream
        stream.read(buffer, BUFFER_SIZE);
        cur_read_size = stream.gcount();
        next_pos = cur_read_size > 0 ? std::optional<size_t>(0) : std::nullopt;
    } else {
        next_pos = std::nullopt;
    }
}

