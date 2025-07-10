#include <cstddef>
#include "positiondirection.hpp"
//====================Position Func========================
//Getters
size_t Position::get_x(){return this->m_x;}
size_t Position::get_y(){return this->m_y;}

//Setters
void Position::set_y(size_t y){ this->m_y = y;}
void Position::set_x(size_t x){ this->m_x = x;}

//====================Direction Func========================
//Setters
void Direction::set_dir(size_t dir){this->m_current_dir = dir;}

//Getters
size_t Direction::get_dir(){return this->m_current_dir;}