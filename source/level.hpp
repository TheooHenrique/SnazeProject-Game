#ifndef LEVEL
#define LEVEL
#include <cstddef>
#include <string>
#include "positiondirection.hpp"

class Level{
    private:
    
    size_t m_width;
    size_t m_length;
    size_t food_amount;
    Position m_spawnpoint;
    Position m_food_coords;
    std::string m_level_maze;

    public:
    Level(){

    }
    Level(size_t x, size_t y, Position spawn, std::string maze){
        this->m_length = y;
        this->m_width = x;
        this->m_spawnpoint = spawn;
        this->m_level_maze = maze;
    }
    void set_width(size_t);
    void set_length(size_t);
    void set_food_amount(size_t);
    Position get_spawnpoint();
    Position generate_food();
};

#endif