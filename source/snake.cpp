#include "snake.hpp"
#include "positiondirection.hpp"
Direction Snake::get_dir(){return this->m_current_dir; }
size_t Snake::get_size(){ return this->m_current_size; }
size_t Snake::get_eated(){ return this->m_eaten_food; }
size_t Snake::get_lives(){ return this->m_lives; }
size_t Snake::get_score(){ return this->m_current_score; }
std::vector<Position> Snake::get_body(){ return this->m_snake_body;}
void Snake::set_dir(Direction){

}
void Snake::set_size(size_t){

}
void Snake::set_eated(size_t){

}
void Snake::set_lives(size_t){

}
void Snake::set_score(size_t){
    
}
void Snake::set_position(Level lvl, char c, Position pos){
    lvl.get_maze()[pos.get_y()][pos.get_x()] = c;
}