#ifndef LEVEL
#define LEVEL
#include <cstddef>
#include <string>
#include <vector>
#include "positiondirection.hpp"

class Level{
    private:
    
    size_t m_width;
    size_t m_length;
    std::vector<std::string> m_level_maze;
    
    size_t food_amount;
    Position m_spawnpoint;
    Position m_food_coords;
    

    public:
    Level(){

    }
    Level(size_t x, size_t y, Position spawn, std::string maze){
        this->m_length = y;
        this->m_width = x;
        this->m_spawnpoint = spawn;
    }
    void set_width(size_t);
    void set_length(size_t);
    void set_maze(std::vector<std::string>);
    void set_food_amount(size_t);
    void set_spawnpoint(Position);

    char get_item_pos(std::vector<std::string>, size_t, size_t);
    void print_level(Level);
    void place_food_in_maze(Position&);
    std::vector<std::string>& get_maze();
    Position get_spawnpoint();
    Position generate_food();
    
};

#endif