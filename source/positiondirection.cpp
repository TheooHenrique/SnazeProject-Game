//====================Position Func========================
#include <cstddef>
#include "positiondirection.hpp"
size_t Position::get_x(){return this->m_x;}
size_t Position::get_y(){return this->m_y;}
void Position::set_y(size_t y){ this->m_y = y;}
void Position::set_x(size_t x){ this->m_x = x;}

//====================Direction Func========================
void Direction::set_dir(std::string dir){this->m_current_dir = dir;}
std::string Direction::get_dir(){return this->m_current_dir;}