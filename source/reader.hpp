#ifndef READER
#define READER
#include <string>
class Reader{
    private:
    std::string m_filename;

    public:
    std::string trim();
    void parse_cfg(std::string);
};



#endif