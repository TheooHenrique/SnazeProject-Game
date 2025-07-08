#include "level.hpp"
#include <iostream>

void Level::set_width(size_t width){this->m_width = width; }
void Level::set_length(size_t len){this->m_length = len; }
void Level::set_food_amount(size_t amount){this->food_amount = amount; }
std::vector<std::string>& Level::get_maze(){ return this->m_level_maze; }
Position Level::get_spawnpoint(){return m_spawnpoint;}

Position Level::generate_food(){
    Position lalala;
    return lalala;
}

void Level::print_level(Level lvl){
    for (int j{0}; j < lvl.get_maze().size(); ++j){
        std::cout << lvl.get_maze()[j] << std::endl;
    }
}
char Level::get_item_pos(std::vector<std::string> layout, size_t x, size_t y){
    return layout[y][x];
}