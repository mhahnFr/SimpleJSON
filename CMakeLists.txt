# SimpleJSON - Simple yet flexible JSON parser for C++
#
# Written in 2026 by mhahnFr
#
# This file is part of SimpleJSON.
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with SimpleJSON,
# see the file LICENSE. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required(VERSION 3.22)

project(SimpleJSON LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SimpleJSON SHARED)

target_sources(SimpleJSON PRIVATE
        include/SimpleJSON/Exception.hpp
        include/SimpleJSON/Object.hpp
        include/SimpleJSON/parser.hpp
        include/SimpleJSON/SimpleJSON.hpp
        include/SimpleJSON/Trait.hpp
        include/SimpleJSON/Value.hpp
        include/SimpleJSON/ValueType.hpp
        src/parser.cpp
)

target_include_directories(SimpleJSON PUBLIC include)