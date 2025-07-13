#ifndef posdic
#define posdic

#include <cstddef>
class Position{
    private:
    size_t m_x;
    size_t m_y;

    public:
    Position(){ } //Default constructor
    Position(size_t x, size_t y){ m_x = x; m_y = y; } //Receiving x and y constructor 
    /*bool operator!=(const Position& other){ return (!(this->m_x == other.m_x && this->m_y == other.m_y)); } //Comparation (different) operator
    bool operator==(const Position& other){ return (this->m_x == other.m_x && this->m_y == other.m_y); }*/ //Comparation (equal) operator

    bool operator==(const Position& other) const {
        return m_x == other.m_x && m_y == other.m_y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    //Setters
    void set_y(size_t);
    void set_x(size_t);

    //Getters
    size_t get_x();
    size_t get_y();
};

struct Direction{
    public:

    //constructor
    Direction(){};
    //Constructor with determined direction
    Direction(size_t x){m_current_dir = x;};
    size_t m_current_dir;
    enum directions : size_t{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

    public:

    bool operator==(const Direction& other){ return (this->m_current_dir == other.m_current_dir); } //Comparation (equal) operator

    //Setters
    void set_dir(size_t);

    //Getters
    size_t get_dir();
};

#endif