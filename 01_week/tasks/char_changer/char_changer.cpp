#include <cstddef>
#include <cctype>
#include <cstring>

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t write_idx = 0;
    auto get_mapped_char = [&](char ch) -> char {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            return delimiter;
        } else if (std::isdigit(static_cast<unsigned char>(ch))) {
            return '*';
        } else if (std::isalpha(static_cast<unsigned char>(ch))) {
            return std::toupper(static_cast<unsigned char>(ch));
        } else {
            return '_';}
    };
    size_t read_idx = 0;
    while (read_idx < size && array[read_idx] != '\0') {
        char current_char = array[read_idx];
        char mapped_char = get_mapped_char(current_char);
        size_t count = 1;
        size_t next_idx = read_idx + 1;
        while (next_idx < size && array[next_idx] != '\0') {
            char next_char = array[next_idx];
            char mapped_next_char = get_mapped_char(next_char);
            if (mapped_next_char != mapped_char) break;
            if (mapped_char == '*' || mapped_char == '_') {
                if (current_char != next_char) break; 
            }
            if (mapped_char >= 'A' && mapped_char <= 'Z') {
                bool current_is_lower = std::islower(static_cast<unsigned char>(current_char));
                bool next_is_lower = std::islower(static_cast<unsigned char>(next_char));
                
                if (current_is_lower != next_is_lower) break;
            }
            count++;
            next_idx++;}
        bool is_delimiter_sequence = (mapped_char == delimiter) && std::isspace(static_cast<unsigned char>(current_char));
        if (is_delimiter_sequence) {
            if (write_idx == 0 || array[write_idx - 1] != delimiter) {
                array[write_idx++] = delimiter;
            }
        } else {
            array[write_idx++] = mapped_char;

            if (count > 1) {
                if (count < 10) {
                    array[write_idx++] = '0' + count;
                } else {
                    array[write_idx++] = '0';}
            }
        }
        read_idx += count;}
    array[write_idx] = '\0';
    return write_idx;
}