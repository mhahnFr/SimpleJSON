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

#ifndef SimpleJSON_Value_hpp
#define SimpleJSON_Value_hpp

#include <variant>

#include "Trait.hpp"

namespace simple_json {
/**
 * Represents a JSON value.
 */
struct Value {
    /** The type of the contained value. */
    ValueType type;
    /** The actual contained value.      */
    std::variant<
        Trait<ValueType::Int>::Type,
        Trait<ValueType::Array>::Type,
        Trait<ValueType::String>::Type,
        Trait<ValueType::Bool>::Type,
        Trait<ValueType::Object>::Type
    > value;

    /**
     * @brief Returns the contained value casted as the given type.
     *
     * Throws an exception if the contained value is not of the given type.
     * Consider checking the type (for instance with `is(ValueType)`) before
     * casting.
     *
     * @tparam T the value type to cast the contained value to
     * @return the casted value
     */
    template<ValueType T>
    constexpr inline auto as() const {
        return std::get<typename Trait<T>::Type>(value);
    }

    /**
     * Returns whether the contained type is equal to the given type.
     *
     * @param type the type to compare against
     * @return whether the types match
     */
    constexpr inline auto is(ValueType type) const -> bool {
        return Value::type == type;
    }
};
}

#endif /* SimpleJSON_Value_hpp */
