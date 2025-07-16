#include "snake.hpp"
#include "positiondirection.hpp"
//Methods
void Snake::add_segment(const Position& pos) { m_snake_body.push_front(pos); }

void Snake::remove_last_segment() {
    if (!m_snake_body.empty()) { m_snake_body.pop_back(); }
}

void Snake::initialize_body(const Position& head_pos) {
    m_snake_body.clear(); // Clear Previous Body
}

//Getters
Direction& Snake::get_dir(){return this->m_current_dir; }
size_t Snake::get_size(){ return this->m_current_size; }
size_t Snake::get_eated(){ return this->m_eaten_food; }
size_t Snake::get_lives(){ return this->m_lives; }
size_t Snake::get_score(){ return this->m_current_score; }
std::deque<Position>& Snake::get_body(){ return this->m_snake_body;}
Position Snake::get_current_pos(){ return this->m_current_pos; }
Position Snake::get_current_pos2(){ return this->m_current_pos2; }

//Setters
void Snake::set_body(std::deque<Position> bd){ this->m_snake_body = bd; }
void Snake::set_current_pos(Position pos){ this->m_current_pos = pos; }
void Snake::set_dir(size_t dir){ this->m_current_dir = dir;}
void Snake::set_current_pos2(Position dir){ this->m_current_pos2 = dir; }
void Snake::set_size(size_t new_size){
    this->m_current_size = new_size;
}
void Snake::set_eated(size_t n){ this->m_eaten_food = n; }
void Snake::set_lives(size_t n ){ this->m_lives = n; }
void Snake::set_score(size_t){}
void Snake::set_position(Level &lvl, char c, Position pos){ 
    if (pos.get_y() < lvl.get_maze().size() && pos.get_x() < lvl.get_maze()[pos.get_y()].size()) {
        if (lvl.get_maze()[pos.get_y()][pos.get_x()] == 'f') {
            m_current_size += 1;
            m_eaten_food += 1;
        }
        lvl.get_maze()[pos.get_y()][pos.get_x()] = c;
    }
}