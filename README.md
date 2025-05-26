# SimpleJSON
A simple yet flexible JSON parser for C++.

*SimpleJSON* can parse any standard conforming JSON data (except floating point numbers) and represent it in C++ code.

## Building
To use this library, simply add the file [parser.cpp][2] to your build system. It should compile without warnings.

> [!TIP]
> Example compilation:
> ```shell
> c++ -c -Wall -Wextra -pedantic -std=c++17 -I<path/to/SimpleJSON>/include <path/to/SimpleJSON>/src/parser.cpp
> ```

## Usage
Simply include the header [SimpleJSON/SimpleJSON.hpp][3].

### Full example
Using the accessors described [below][7], writing a data transfer object (DTO) becomes quite simple:
```c++
// main.cpp

#include <SimpleJSON/SimpleJSON.hpp>

#include <sstream> // For the std::istringstream used below
#include <iostream> // For std::cout ...

/* The example file to be parsed */
constexpr auto file = R"(
{
  "name": "simple_json",
  "license": {
    "name": "CC0",
    "open source": true
  },
  "includeFiles": [
    "Exception.hpp",
    "Object.hpp",
    "parser.hpp",
    "SimpleJSON.hpp",
    "Trait.hpp",
    "Value.hpp",
    "ValueType.hpp"
  ]
}
)";

class ProjectDTO {
    simple_json::Object underlying;

public:
    ProjectDTO(simple_json::Object underlying): underlying(underlying) {}

    class License {
        simple_json::Object underlying;
        
    public:
        License(simple_json::Object underlying): underlying(underlying) {}
        
        /* Returns std::string */
        auto name() {
            return underlying.getBang<simple_json::ValueType::String>("name");
        }
        
        /* Returns bool */
        auto isOpenSource() {
            return underlying.getBang<simple_json::ValueType::Bool>("open source");
        }
    };
    
    /* Returns std::string */
    auto name() {
        return underlying.getBang<simple_json::ValueType::String>("name");
    }
    
    /* Returns std::optional<License> */
    auto license() {
        return underlying.maybeGetAs<License>("license");
    }
    
    /* Returns std::vector<simple_json::Value> */
    auto includeFiles() {
        return underlying.getBang<simple_json::ValueType::Array>("includeFiles");
    }
};

int main() {
    auto stream = std::istringstream(file);
    
    auto project = ProjectDTO(simple_json::parse(stream));
    
    std::cout << "   Name: " << project.name() << std::endl
              << "License: " << project.license().value().name()
              << std::endl;
    
    std::cout << "Header files:" << std::endl;
    for (const auto& file : project.includeFiles()) {
        std::cout << file.as<simple_json::ValueType::String>() << std::endl;
    }
}
```

### Parsing
Parse a JSON file by passing its input stream to the `parse` function:
```c++
// main.cpp

#include <SimpleJSON/SimpleJSON.hpp>

int main() {
    auto stream = std::ifstream("file.json");
    
    auto data = simple_json::parse(stream);
}
```

If the parsing has failed, an [appropriate exception][4] is thrown.

> [!NOTE]
> Do note that `parse` returns a [`Value`][5] and not an [`Object`][6].
> 
> The parsed value can simply be cast to the desired JSON type by using the method `as`:
> ```c++
> auto object = data.as<simple_json::ValueType::Object>();
> ```
> For JSON objects, an implicit cast is possible as well:
> ```c++
> simple_json::Object object = data;
> 
> // This yields the same:
> auto object = simple_json::Object(data);
> ```
> 
> The following is also a possibility:
> ```c++
> auto object = simple_json::parse<simple_json::ValueType::Object>(stream);
> ```

### Accessing the contents
The parsed data of an [object][6] can be accessed in two ways.

#### Fail-safe access
In case the desired value is absent or `null`, the member functions `get`, `getObject` and `maybeGetAs` can be used.

##### `get`
Returns an optional with the desired [value type][5].

**Example:**
```c++
simple_json::Object object = simple_json::parse(stream);

auto name = object.get<simple_json::ValueType::String>("name");
```

##### `getObject`
Returns an optional with a [JSON object][6].

**Example:**
```c++
simple_json::Object object = simple_json::parse(stream);

auto innerObject = object.getObject("innerDataName");
```

##### `maybeGetAs`
Returns an optional with the contained object wrapped into an instance of the given class.

**Example:**
```c++
class Wrapper {
public:
    Wrapper(simple_json::Object object);
};

// ...

simple_json::Object object = simple_json::parse(stream);

auto wrapped = object.maybeGetAs<Wrapper>("innerObjectName");
```

#### Direct access
If the desired JSON value is always present, the direct accessors can be used.  
In case the desired value is not present or `null`, an exception is thrown.

##### `getBang`
Returns a reference to the [JSON value][5] of the given name. The contained value is not copied.

**Example:**
```c++
simple_json::Object object = simple_json::parse(stream);

auto name = object.getBang<simple_json::ValueType::String>("name");
```

##### `getObjectBang`
Returns the contained object.

**Example:**
```c++
simple_json::Object object = simple_json::parse(stream);

auto innerObject = object.getObjectBang("innerObjectName");
```

## Dependencies
This library adheres to the C++17 standard. No other dependencies are required.

# Final notes
This project is marked with CC0 1.0 Universal.

Written in 2024 - 2025 by [mhahnFr][1]

[1]: https://github.com/mhahnFr
[2]: src/parser.cpp
[3]: include/SimpleJSON/SimpleJSON.hpp
[4]: include/SimpleJSON/Exception.hpp
[5]: include/SimpleJSON/Value.hpp
[6]: include/SimpleJSON/Object.hpp
[7]: #accessing-the-contents