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

#ifndef SimpleJSON_ValueType_hpp
#define SimpleJSON_ValueType_hpp

namespace simple_json {
/**
 * An enumeration of the known value types.
 */
enum class ValueType {
    /** An integral number.                    */
    Int,
    /** A string.                              */
    String,
    /** An array (can contain multiple types). */
    Array,
    /** A boolean value.                       */
    Bool,
    /** An object.                             */
    Object,
    /** The special value `null`.              */
    Null
};
}

#endif /* SimpleJSON_ValueType_hpp */
