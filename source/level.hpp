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
    
    size_t food_amount = 2;
    Position m_spawnpoint;
    Position m_food_coords;
    

    public:
    Level(){ }//Default constructor
    Level(size_t x, size_t y, Position spawn, std::string maze){ //Constructor
        this->m_length = y;
        this->m_width = x;
        this->m_spawnpoint = spawn;
    }

    public:
    //Methods
    void print_level(Level);
    void place_food_in_maze(Position&);
    void generate_food();

    //Setters
    void set_width(size_t);
    void set_length(size_t);
    void set_maze(std::vector<std::string>);
    void set_food_amount(size_t);
    void set_spawnpoint(Position);
    void set_position(Position, char);

    //Getters
    size_t get_food_amount();
    char get_item_pos(std::vector<std::string>, size_t, size_t);
    std::vector<std::string>& get_maze();
    Position get_spawnpoint();
    Position& get_food_cords();
    
};

#endif