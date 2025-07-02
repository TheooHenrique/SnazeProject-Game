#include "reader.hpp"
#include <string>

void Reader::trim(std::string s){
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    s.assign(start, end + 1);
}

void Reader::parse_cfg(std::string){
    
}