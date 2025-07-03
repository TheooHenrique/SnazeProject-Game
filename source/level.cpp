#include "level.hpp"
#include "positiondirection.hpp"

void Level::set_width(size_t width){this->m_width = width;}
void Level::set_length(size_t len){this->m_length = len;}
void Level::set_food_amount(size_t amount){this->food_amount = amount;}
Position Level::get_spawnpoint(){return m_spawnpoint;}

Position Level::generate_food(){
    Position lalala;
    return lalala;
}