#ifndef READER
#define READER
#include "level.hpp"
#include <deque>
#include <fstream>
#include <string>
class Reader{
    private:
    std::string m_filename;

    public:
    Reader(){} //Constructor

    void trim(std::string&);
    std::deque<Level> parse_cfg(std::ifstream&);
};


#endif