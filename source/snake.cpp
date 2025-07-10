#include "snake.hpp"
#include "positiondirection.hpp"
//Methods


//Getters
Direction& Snake::get_dir(){return this->m_current_dir; }
size_t Snake::get_size(){ return this->m_current_size; }
size_t Snake::get_eated(){ return this->m_eaten_food; }
size_t Snake::get_lives(){ return this->m_lives; }
size_t Snake::get_score(){ return this->m_current_score; }
std::deque<Position> Snake::get_body(){ return this->m_snake_body;}
Position Snake::get_current_pos(){ return this->m_current_pos; }
Position Snake::get_current_pos2(){ return this->m_current_pos2; }

//Setters
void Snake::set_current_pos(Position pos){ m_current_pos = pos; }
void Snake::set_dir(size_t dir){ this->m_current_dir = dir;}
void Snake::set_current_pos2(Position dir){ this->m_current_pos2 = dir; }
void Snake::set_size(size_t){}
void Snake::set_eated(size_t){}
void Snake::set_lives(size_t){}
void Snake::set_score(size_t){}
void Snake::set_position(Level &lvl, char c, Position pos){ lvl.get_maze()[pos.get_y()][pos.get_x()] = c; }