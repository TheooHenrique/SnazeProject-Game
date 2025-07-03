#ifndef READER
#define READER
#include <fstream>
#include <string>
class Reader{
    private:
    std::string m_filename;

    public:
    Reader(){} //Constructor

    void trim(std::string);
    void parse_cfg(std::ifstream);
};


#endif