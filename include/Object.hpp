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
struct Object {
    ObjectContent content;

    Object() = default;

    inline Object(const ObjectContent& content): content(content) {}
    inline Object(const Value& value): Object(value.as<ValueType::Object>()) {}

    template<typename T>
    constexpr inline auto get(const std::string& name) const -> std::optional<T> {
        const auto& it = content.find(name);
        if (it != content.end() && !it->second.is(ValueType::Null)) {
            return std::get<T>(it->second.value);
        }
        return std::nullopt;
    }

    template<ValueType T>
    constexpr inline auto get(const std::string& name) const {
        return get<typename Trait<T>::Type>(name);
    }

    inline auto getObject(const std::string& name) const -> std::optional<Object> {
        if (auto object = get<ValueType::Object>(name)) {
            return Object { *object };
        }
        return std::nullopt;
    }

    template<typename T>
    constexpr inline auto getBang(const std::string& name) const -> const T& {
        return std::get<T>(content.at(name).value);
    }

    template<ValueType T>
    constexpr inline auto getBang(const std::string& name) const -> const typename Trait<T>::Type& {
        return getBang<typename Trait<T>::Type>(name);
    }

    inline auto getObjectBang(const std::string& name) const -> Object {
        return Object { getBang<ValueType::Object>(name) };
    }

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
