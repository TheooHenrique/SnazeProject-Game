#include "reader.hpp"
#include "simulation.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
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

void Reader::parse_cfg(std::ifstream file){
    std::string line;

    while (std::getline(file, line)){
        size_t x;
        size_t y;
        bool storemaze;
        trim(line);
        if (line.empty()){continue;}
        for (size_t i{0}; i < line.size() ; ++i){
            if (storemaze){
                for (size_t j{0}; j < y; ++j){
                    
                }
            }
            if (line[i] == ' '){
                std::string subs1 = line.substr(0, i -1);
                std::string subs2 = line.substr(i + 1, line.size());
                if (std::all_of(subs1.begin(), subs1.end(), ::isdigit) && std::all_of(subs2.begin(), subs2.end(), ::isdigit)){
                    x = std::stoi(subs1);
                    y = std::stoi(subs2);
                    storemaze = true;
                }
            }
        }
    }
}
