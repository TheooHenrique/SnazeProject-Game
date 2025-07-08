#include "reader.hpp"
#include "level.hpp"
#include "simulation.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Reader::trim(std::string &s){
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    s.assign(start, end + 1);
}

std::vector<Level> Reader::parse_cfg(std::ifstream &file){
    std::string line;
    std::vector<Level> level_list;

    while (std::getline(file, line)){
        trim(line);
        if (line.empty()){continue;}
        size_t height, width;
        std::istringstream iss(line);
        if (iss >> height >> width && iss.eof()){
            Level lvl;
            lvl.set_length(width);
            lvl.set_width(height);
            lvl.get_maze().reserve(height);
            for (size_t idx{0}; idx < height; ++idx ){
                if (std::getline(file, line)){
                    trim(line);
                    if (line.length() != width){
                        std::cerr << "Warning: The length or width of the maze do not fit with his declaration on the .dat file!\n";
                        exit(1);
                    }
                    lvl.get_maze().push_back(line); 
                }
                else { std::cerr << "Error! Some error occurred at the load of the levels! Please check your .dat file!\n"; break;}
            }
            level_list.push_back(lvl);
        }
    }
    return level_list;
}
