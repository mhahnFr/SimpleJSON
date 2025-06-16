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

#ifndef SimpleJSON_Trait_hpp
#define SimpleJSON_Trait_hpp

#include <map>
#include <string>
#include <vector>

#include "ValueType.hpp"

namespace simple_json {
struct Value;

/**
 * The type used for the content of a JSON object.
 */
using ObjectContent = std::map<std::string, Value>;

/**
 * This structure contains an @c using declaration for the value type represented
 * by the given value type enumeration value.
 *
 * @tparam T the value type enumeration value
 */
template<ValueType T>
struct Trait;

template<>
struct Trait<ValueType::Int> {
    using Type = long;
};

template<>
struct Trait<ValueType::Array> {
    using Type = std::vector<Value>;
};

template<>
struct Trait<ValueType::String> {
    using Type = std::string;
};

template<>
struct Trait<ValueType::Bool> {
    using Type = bool;
};

template<>
struct Trait<ValueType::Object> {
    using Type = ObjectContent;
};
}

#endif /* SimpleJSON_Trait_hpp */
