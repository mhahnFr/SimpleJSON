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

#include <SimpleJSON/Exception.hpp>
#include <SimpleJSON/parser.hpp>

namespace simple_json {
/**
 * Skips the next whitespaces in the given input stream.
 *
 * @param in the input stream
 */
static inline void skipWhitespaces(std::istream& in) {
    while (std::isspace(in.peek())) {
        in.get();
    }
}

/**
 * Expects the next character in the given stream to be the given one.
 *
 * @param in the input stream
 * @param expected the expected character
 * @param skipWhite whether to skip remaining whitespaces before checking the character
 * @throws Exception if the character is not the expected one
 */
static inline void expect(std::istream& in, char expected, bool skipWhite = true) {
    if (skipWhite) {
        skipWhitespaces(in);
    }
    if (in.peek() != expected) {
        throw Exception(expected, static_cast<char>(in.peek()), in.tellg());
    }
}

/**
 * @brief Expects the next character in the given stream to be the given one.
 *
 * The expected character is consumed if found.
 *
 * @param in the input stream
 * @param expected the expected character
 * @param skipWhite whether to skip remaining whitespaces before checking the character
 * @throws Exception if the character is not the expected one
 */
static inline void expectConsume(std::istream& in, char expected, bool skipWhite = true) {
    expect(in, expected, skipWhite);
    in.get();
}

/**
 * Reads a string surrounded by quotes.
 *
 * @param in the input stream to read from
 * @return the read string as @c Value
 */
static inline auto readString(std::istream& in) -> Value {
    expectConsume(in, '"');

    std::string buffer;
    while (in.peek() != '"') {
        if (in.peek() == '\\') in.get();
        buffer += static_cast<char>(in.get());
    }
    expectConsume(in, '"');
    return Value { ValueType::String, buffer };
}

/**
 * Reads a primitive value from the given stream.
 *
 * Primitives are numbers (parsed as base 10), @c true, @c false and @c null .
 *
 * @param in the input stream
 * @return the read primitive as @c Value
 */
static inline auto readPrimitive(std::istream& in) -> Value {
    std::string buffer;
    while (!std::isspace(in.peek()) && in.peek() != ',' && in.peek() != ']' && in.peek() != '}') {
        buffer += static_cast<char>(in.get());
    }
    if (buffer == "true" || buffer == "false") {
        return Value { ValueType::Bool, buffer == "true" };
    } else if (buffer == "null") {
        return Value { ValueType::Null, 0 };
    }
    return Value { ValueType::Int, std::strtol(buffer.c_str(), nullptr, 10) };
}

/**
 * Parses a JSON object surrounded by curly brackets.
 *
 * @param in the input stream
 * @return the parsed object as @c Value
 */
static inline auto readObject(std::istream& in) -> Value;

/**
 * @brief Parses a JSON array surrounded by square brackets.
 *
 * JSON arrays may contain any kind of JSON value, including a mixture of types.
 *
 * @param in the input stream
 * @return the parsed array as @c Value
 */
static inline auto readArray(std::istream& in) -> Value {
    expectConsume(in, '[');
    skipWhitespaces(in);
    auto content = std::vector<Value>();
    while (in.peek() != ']') {
        Value value;
        switch (in.peek()) {
            case '"': value = readString(in); break;
            case '[': value = readArray(in);  break;
            case '{': value = readObject(in); break;

            default: value = readPrimitive(in); break;
        }
        content.push_back(value);
        skipWhitespaces(in);
        if (in.peek() == ',') {
            in.get();
            skipWhitespaces(in);
        }
    }
    expectConsume(in, ']');
    return Value { ValueType::Array, content };
}

static inline auto readObject(std::istream& in) -> Value {
    skipWhitespaces(in);
    expectConsume(in, '{');

    auto toReturn = std::map<std::string, Value>();
    skipWhitespaces(in);
    while (in.peek() != '}') {
        auto name = readString(in);
        expectConsume(in, ':');
        skipWhitespaces(in);
        Value value;
        switch (in.peek()) {
            case '"': value = readString(in); break;
            case '[': value = readArray(in);  break;
            case '{': value = readObject(in); break;

            default: value = readPrimitive(in); break;
        }
        toReturn.emplace(std::make_pair(std::get<std::string>(name.value), value));
        skipWhitespaces(in);
        if (in.peek() == ',') {
            in.get();
            skipWhitespaces(in);
        }
    }
    expectConsume(in, '}');
    return { ValueType::Object, toReturn };
}

auto parse(std::istream& in) -> Value {
    skipWhitespaces(in);

    switch (in.peek()) {
        case '{': return readObject(in);
        case '[': return readArray(in);

        default: throw Exception('{', char(in.peek()), in.tellg());
    }
}
}
