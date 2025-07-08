#ifndef READER
#define READER
#include "level.hpp"
#include <fstream>
#include <string>
#include <vector>
class Reader{
    private:
    std::string m_filename;

    public:
    Reader(){} //Constructor

    void trim(std::string&);
    std::vector<Level> parse_cfg(std::ifstream&);
};


#endif