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

#ifndef SimpleJSON_parser_hpp
#define SimpleJSON_parser_hpp

#include <istream>

#include "Object.hpp"

namespace simple_json {
/**
 * Parses a JSON object or array from the given input stream.
 *
 * Does not check for the integrity of JSON data.
 *
 * @param stream the input stream to read the JSON data from
 * @return the JSON data as @c Value
 * @throws Exception if the parsing failed
 */
auto parse(std::istream& stream) -> Value;

/**
 * Parses a JSON object or array from the given input stream.
 *
 * Does not check for the integrity of JSON data.
 *
 * @param stream the input stream to read the JSON data from
 * @return the JSON data as @c Value
 * @throws Exception if the parsing failed
 */
static inline auto parse(std::istream&& stream) -> Value {
    return parse(stream);
}

/**
 * Parses a JSON object or array from the given input stream.
 *
 * Does not check for the integrity of the JSON data.
 *
 * @param stream the input stream to read the JSON data from
 * @tparam T the @c ValueType to cast the parsed data to
 * @return the parsed data casted to the given JSON value type
 * @throws Exception if the parsing failed or the contained data has a different type
 */
template<ValueType T>
constexpr inline auto parse(std::istream& stream) {
    return parse(stream).as<T>();
}

/**
 * Parses a JSON object or array from the given input stream.
 *
 * Does not check for the integrity of the JSON data.
 *
 * @param stream the input stream to read the JSON data from
 * @tparam T the @c ValueType to cast the parsed data to
 * @return the parsed data casted to the given JSON value type
 * @throws Exception if the parsing failed or the contained data has a different type
 */
template<ValueType T>
constexpr inline auto parse(std::istream&& stream) {
    return parse(stream).as<T>();
}
}

#endif /* SimpleJSON_parser_hpp */
