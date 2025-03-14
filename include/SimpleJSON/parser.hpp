/*
 * SimpleJSON - Simple yet flexible JSON parser for C++
 *
 * Copyright (C) 2024 - 2025  mhahnFr
 *
 * This file is part of SimpleJSON.
 *
 * SimpleJSON is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SimpleJSON is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * SimpleJSON, see the file LICENSE.  If not, see <https://www.gnu.org/licenses/>.
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
