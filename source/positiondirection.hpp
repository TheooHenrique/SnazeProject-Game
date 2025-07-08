#ifndef posdic
#define posdic

#include <cstddef>
#include <string>
class Position{
    private:
    size_t m_x;
    size_t m_y;

    public:
    Position(){
        
    }
  
    Position(size_t x, size_t y){
        m_x = x;
        m_y = y;
    }

    size_t get_x();
    size_t get_y();
    void set_y(size_t);
    void set_x(size_t);
};

class Direction{
    private:
    std::string m_current_dir;

    public:
    void set_dir(std::string);
    std::string get_dir();
};

#endif