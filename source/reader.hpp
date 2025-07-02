#ifndef READER
#define READER
#include <string>
class Reader{
    private:
    std::string m_filename;

    public:
    void trim(std::string);
    void parse_cfg(std::string);
};


#endif