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
auto parse(std::istream& stream) -> Value;

static inline auto parse(std::istream&& stream) -> Value {
    return parse(stream);
}

template<ValueType T>
constexpr inline auto parse(std::istream& stream) {
    return parse(stream).as<T>();
}

template<ValueType T>
constexpr inline auto parse(std::istream&& stream) {
    return parse(stream).as<T>();
}
}

#endif /* SimpleJSON_parser_hpp */
