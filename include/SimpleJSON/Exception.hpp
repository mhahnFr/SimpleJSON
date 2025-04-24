/*
 * SimpleJSON - Simple yet flexible JSON parser for C++
 *
 * Written in 2024 - 2025 by mhahnFr
 *
 * This file is part of SimpleJSON.
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along with SimpleJSON,
 * see the file LICENSE. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef SimpleJSON_Exception_hpp
#define SimpleJSON_Exception_hpp

#include <stdexcept>
#include <string>

namespace simple_json {
/**
 * @brief Represents a parsing exception.
 *
 * Its message includes the location of the error in the parsed stream.
 */
class Exception: public std::runtime_error {
public:
    /**
     * Constructs an exception with the given information.
     *
     * @param expected the expected character
     * @param got the character that was actually at that position
     * @param pos the position in the stream
     */
    inline Exception(char expected, char got, long long pos):
        std::runtime_error(std::string { "Expected '" } + expected + "', got '" + got + "', position: " + std::to_string(pos + 1)) {}

    Exception() = delete;
};
}

#endif /* SimpleJSON_Exception_hpp */
