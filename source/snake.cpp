#include "snake.hpp"
#include "positiondirection.hpp"

/**
 * @file snake.cpp
 * @brief Implements the methods of the Snake class.
 */

// Methods
void Snake::add_segment(const Position& pos) { m_snake_body.push_front(pos); }
void Snake::remove_last_segment() { if (!m_snake_body.empty()) { m_snake_body.pop_back(); } }
void Snake::initialize_body(const Position& head_pos) { m_snake_body.clear(); }

// Getters
Direction& Snake::get_dir(){return this->m_current_dir; }
size_t Snake::get_size(){ return this->m_current_size; }
size_t Snake::get_eated(){ return this->m_eaten_food; }
size_t Snake::get_lives(){ return this->m_lives; }
size_t Snake::get_initial_lives(){ return this->m_initial_lives; }
size_t Snake::get_score(){ return this->m_current_score; }
std::deque<Position>& Snake::get_body(){ return this->m_snake_body;}
Position Snake::get_current_pos(){ return this->m_current_pos; }
Position Snake::get_current_pos2(){ return this->m_current_pos2; }

// Setters
void Snake::set_body(std::deque<Position> bd){ this->m_snake_body = bd; }
void Snake::set_current_pos(Position pos){ this->m_current_pos = pos; }
void Snake::set_dir(size_t dir){ this->m_current_dir = dir;}
void Snake::set_current_pos2(Position dir){ this->m_current_pos2 = dir; }
void Snake::set_size(size_t new_size){ this->m_current_size = new_size; }
void Snake::set_eated(size_t n){ this->m_eaten_food = n; }

/**
 * @brief Sets the current number of lives.
 * @param n The new number of lives.
 */
void Snake::set_lives(size_t n ){
    this->m_lives = n;
}

/**
 * @brief Initializes the snake's lives at the start of the game.
 * Sets both the current and initial life counts.
 * @param n The number of lives to start with.
 */
void Snake::set_initial_lives(size_t n) {
    this->m_lives = n;
    this->m_initial_lives = n;
}
void Snake::set_score(size_t score){ this->m_current_score = score; }

/**
 * @brief Updates the character at a specific position in the level's grid.
 * Also handles the logic for when the snake's head moves onto a food pellet.
 * @param lvl A reference to the current Level object.
 * @param c The character to place in the grid.
 * @param pos The position to place the character.
 */
void Snake::set_position(Level &lvl, char c, Position pos){
    if (pos.get_y() < lvl.get_maze().size() && pos.get_x() < lvl.get_maze()[pos.get_y()].size()) {
        // If the head moves onto a food tile, increment size and eaten count.
        if (lvl.get_maze()[pos.get_y()][pos.get_x()] == 'f') {
            m_current_size += 1;
            m_eaten_food += 1;
        }
        lvl.get_maze()[pos.get_y()][pos.get_x()] = c;
    }
}
