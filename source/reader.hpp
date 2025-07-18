#ifndef READER
#define READER

#include "level.hpp"
#include <deque>
#include <fstream>
#include <string>

/**
 * @file reader.hpp
 * @brief Defines the Reader class for parsing level configuration files.
 */

/**
 * @class Reader
 * @brief A utility class to read and parse game level data from a file.
 */
class Reader{
    private:
        /// @brief The filename of the input file (not currently used).
        std::string m_filename;

    public:
        /**
         * @brief Default constructor.
         */
        Reader(){}

        /**
         * @brief Trims leading and trailing whitespace from a string.
         * @param s The string to be trimmed in-place.
         */
        void trim(std::string& s);

        /**
         * @brief Parses an input file stream containing one or more levels.
         * @param file The input file stream to read from.
         * @return A deque of Level objects parsed from the file.
         */
        std::deque<Level> parse_cfg(std::ifstream& file);
};

#endif
