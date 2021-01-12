// Example that shows simple usage of the INIReader class

#include <iostream>
#include <sstream>
#include "INIReader.h"

std::string sections(INIReader &reader)
{
    std::stringstream ss;
    const INIReader::sections configs = reader.get_sections();
    for (auto heading : configs) {
        ss << heading.first << ",";
        std::cout << "heading: " << heading.first << std::endl;
        for (auto kvs : heading.second) {
            std::cout << "first: " << kvs.first << " second: " << kvs.second << std::endl;
        }
    }
    return ss.str();
}

int main()
{
    INIReader reader("test.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'test.ini'\n";
        return 1;
    }
    std::cout << "Config loaded from 'test.ini': found sections=" << sections(reader)
              << std::endl
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", multi="
              << reader.Get("user", "multi", "UNKNOWN") << ", pi="
              << std::endl;
    
    std::cout <<  "Example(exist section)" << std::endl;
    for (auto kv : reader.get_section("kafka")) {
        std::cout << kv.first << "=" <<  kv.second << std::endl;
    }

    std::cout <<  "Example(not exist section)" << std::endl;
    for (auto kv : reader.get_section("kafka2")) {
        std::cout << kv.first << "=" <<  kv.second << std::endl;
    }
    return 0;
}
