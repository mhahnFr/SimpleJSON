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

#ifndef SimpleJSON_Object_hpp
#define SimpleJSON_Object_hpp

#include <map>
#include <optional>

#include "Value.hpp"

namespace simple_json {
/**
 * @brief Represents a JSON object.
 *
 * It can be constructed from JSON values (if they contain an object) or from
 * the raw content of a JSON object (the `ObjectContent` type).
 *
 * Various accessors enable the simple usage of the content of an JSON object.
 */
struct Object {
    /** The raw content of this object. */
    ObjectContent content;

    Object() = default;

    /**
     * Constructs a JSON object from the given raw JSON object content.
     *
     * @param content the raw JSON content
     */
    inline Object(const ObjectContent& content): content(content) {}

    /**
     * @brief Constructs a JSON object from the given JSON value.
     *
     * Will throw an exception if the given value does not contain a JSON object.
     *
     * @param value the JSON value
     */
    inline Object(const Value& value): Object(value.as<ValueType::Object>()) {}

    /**
     * @brief Gets the contained value for the given key.
     *
     * Throws an exception if the value is found but the type does not match
     * the given type.
     *
     * @param name the key whose mapped value to get
     * @tparam T the type of the contained value
     * @return the value for the given key or `std::nullopt` if not found or `null`
     */
    template<typename T>
    constexpr inline auto get(const std::string& name) const -> std::optional<T> {
        const auto& it = content.find(name);
        if (it != content.end() && !it->second.is(ValueType::Null)) {
            return std::get<T>(it->second.value);
        }
        return std::nullopt;
    }

    /**
     * @brief Gets the contained value for the given key.
     *
     * Throws an exception if the value is found but the type does not match
     * the given type.
     *
     * @param name the key whose mapped value to get
     * @tparam T the value type enumeration value of the desired type
     * @return the value for the given key or `std::nullopt` if not found or @c null
     */
    template<ValueType T>
    constexpr inline auto get(const std::string& name) const {
        return get<typename Trait<T>::Type>(name);
    }

    /**
     * @brief Gets the contained object for the given key.
     *
     * Throws an exception if the value  is found but is not a JSON object.
     *
     * @param name the key whose mapped object to get
     * @return the object for the given key or `std::nullopt` if not found or @c null
     */
    inline auto getObject(const std::string& name) const -> std::optional<Object> {
        if (auto object = get<ValueType::Object>(name)) {
            return Object { *object };
        }
        return std::nullopt;
    }

    /**
     * @brief Returns a reference to the value referred to by the given key.
     *
     * Throws an exception if the value is not found or the type does not match.
     *
     * @param name the key whose mapped value to get
     * @tparam T the type of the contained value
     * @return the mapped value
     */
    template<typename T>
    constexpr inline auto getBang(const std::string& name) const -> const T& {
        return std::get<T>(content.at(name).value);
    }

    /**
     * @brief Returns a reference to the value referred to by the given key.
     *
     * Throws an exception if the value is not found or the type does not match.
     *
     * @param name the key whose mapped value to get
     * @tparam T the value type enumeration value of the desired type
     * @return the mapped value
     */
    template<ValueType T>
    constexpr inline auto getBang(const std::string& name) const -> const typename Trait<T>::Type& {
        return getBang<typename Trait<T>::Type>(name);
    }

    /**
     * @brief Gets the object referred to by the given key.
     *
     * Throws an exception if the object is not found or is not a JSON object.
     *
     * @param name the key whose mapped object to get
     * @return the mapped object
     */
    inline auto getObjectBang(const std::string& name) const -> Object {
        return Object { getBang<ValueType::Object>(name) };
    }

    /**
     * @brief Gets the object referred to by the given key and casts it to the
     * given type.
     *
     * Uses the functional style cast.
     *
     * @param name the key whose mapped object to get
     * @tparam T the type to construct from the contained JSON object
     * @return the mapped object casted to the given type or `std::nullopt` if not found or @c null
     */
    template<
#if __cplusplus >= 202002L
    std::constructible_from<Object>
#else
    typename
#endif
    T>
    constexpr inline auto maybeGetAs(const std::string& name) const -> std::optional<T> {
        static_assert(std::is_constructible_v<T, Object>,
                      "Given type must be constructible from simple_json::Object");

        if (auto&& object = getObject(name)) {
            return T(std::move(*object));
        }
        return std::nullopt;
    }
};
}

#endif /* SimpleJSON_Object_hpp */
