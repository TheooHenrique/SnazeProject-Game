#include "reader.hpp"
#include "level.hpp"
#include <cctype>
#include <cstddef>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @file reader.cpp
 * @brief Implements the file parsing logic for the Reader class.
 */

/**
 * @brief Removes leading and trailing whitespace from a given string.
 * @param s The string to be modified.
 */
void Reader::trim(std::string &s){
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    s.assign(start, end + 1);
}

/**
 * @brief Parses a configuration file stream to extract game levels.
 *
 * This function reads the file line by line. It expects a line with
 * dimensions (height width), followed by `height` lines of maze data.
 * This process can repeat for multiple levels within the same file.
 *
 * @param file An open ifstream connected to the level data file.
 * @return A deque containing all successfully parsed Level objects.
 */
std::deque<Level> Reader::parse_cfg(std::ifstream &file){
    std::string line;
    std::deque<Level> level_list;

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
