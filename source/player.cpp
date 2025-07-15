#include "player.hpp"
#include "positiondirection.hpp"
#include <algorithm>
#include <random>
#include <vector>
//==============Player funct================
//Methods
Direction Player::next_move(){
    Direction lalala;
    return lalala;
};



void Player::change_direction(Direction &dir){
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<size_t> dirvec;

    if (dir.get_dir() == Direction::UP) {
        dirvec = { Direction::LEFT, Direction::RIGHT};
    } else if (dir.get_dir() == Direction::DOWN) {
        dirvec = { Direction::LEFT, Direction::RIGHT};
    } else if (dir.get_dir() == Direction::LEFT) {
        dirvec = {Direction::UP, Direction::DOWN};
    } else if (dir.get_dir() == Direction::RIGHT) {
        dirvec = {Direction::UP, Direction::DOWN};
    }

    if (!dirvec.empty()){
        std::shuffle(dirvec.begin(), dirvec.end(), g);
        dir.set_dir(dirvec[0]);
    } else{
        
    }

}

bool Player::is_snake_body( Position& check_pos,  std::deque<Position>& snake_body) {
    for (auto& segment_pos : snake_body) {
        if (check_pos.get_x() == segment_pos.get_x() && check_pos.get_y() == segment_pos.get_y()) {
            return true; // A posição faz parte do corpo da cobra
        }
    }
    return false; // A posição não faz parte do corpo da cobra
}

bool Player::check_if_snake_is_prision(Level lvl, Position pos, Direction dir, std::deque<Position>& snake_body){

    //CHECK IF THE SNAKE IS AT PRISION IF THE SNAKE IS GOING UP
    if (dir == Direction::UP){
        Position up_pos(pos.get_x(), pos.get_y() - 1);
        Position right_pos(pos.get_x() + 1, pos.get_y());
        Position left_pos(pos.get_x() - 1, pos.get_y());

        if (((lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '.') || is_snake_body(right_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '.') || is_snake_body(left_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '.') || is_snake_body(up_pos, snake_body))){
            return true;
        }
    }
    //CHECK IF THE SNAKE IS AT PRISION IF THE SNAKE IS GOING DOWN
    else if (dir == Direction::DOWN){
        Position down_pos(pos.get_x(), pos.get_y() + 1);
        Position right_pos(pos.get_x() + 1, pos.get_y());
        Position left_pos(pos.get_x() - 1, pos.get_y());

        if (((lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '.') || is_snake_body(right_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '.') || is_snake_body(left_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '.') || is_snake_body(down_pos, snake_body))){
            return true;
        }

    }
    else if (dir == Direction::LEFT){
        Position up_pos(pos.get_x(), pos.get_y() - 1);
        Position down_pos(pos.get_x(), pos.get_y() + 1);
        Position left_pos(pos.get_x() - 1, pos.get_y());

        if (((lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '.') || is_snake_body(up_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), left_pos.get_x(), left_pos.get_y()) == '.') || is_snake_body(left_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '.') || is_snake_body(down_pos, snake_body))){
            return true;
        }

    }
    else if (dir == Direction::RIGHT){
        Position up_pos(pos.get_x(), pos.get_y() - 1);
        Position down_pos(pos.get_x(), pos.get_y() + 1);
        Position right_pos(pos.get_x() + 1, pos.get_y());

        if (((lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), up_pos.get_x(), up_pos.get_y()) == '.') || is_snake_body(up_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), right_pos.get_x(), right_pos.get_y()) == '.') || is_snake_body(right_pos, snake_body))
            && ((lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), down_pos.get_x(), down_pos.get_y()) == '.') || is_snake_body(down_pos, snake_body))){
            return true;
        }
    }

    return false;
}

bool Player::check_if_next_is_playable(Level lvl, Position pos, Direction dir, std::deque<Position>& snake_body){
    Position next_pos;

    // Calcular a próxima posição baseada na direção
    if (dir.m_current_dir == 0) { // Cima
        next_pos = Position(pos.get_x(), pos.get_y() - 1);
    } else if (dir.m_current_dir == 1) { // Baixo
        next_pos = Position(pos.get_x(), pos.get_y() + 1);
    } else if (dir.m_current_dir == 2) { // Esquerda
        next_pos = Position(pos.get_x() - 1, pos.get_y());
    } else if (dir.m_current_dir == 3) { // Direita
        next_pos = Position(pos.get_x() + 1, pos.get_y());
    }

    //checking the colision with the wall
    char item_at_next_pos = lvl.get_item_pos(lvl.get_maze(), next_pos.get_x(), next_pos.get_y());
    if (item_at_next_pos == '#' || item_at_next_pos == '.') {
        return false; 
    }

    //Checking the colision with snake body
    for (size_t i = 0; i < snake_body.size(); ++i) { // Ajuste para não verificar a cabeça
        if (next_pos.get_x() == snake_body[i].get_x() && next_pos.get_y() == snake_body[i].get_y()) {
            return false;
        }
    }
    //Case dont colide:
    return true; 

}

//Getters
std::deque<Position>& Player::get_nextpositions(){return this->nextpositions;}
std::deque<Direction>& Player::get_nextdirection(){ return this->nextdirection; }

//==============PlayerRandom funct================
Direction PlayerRandom::next_move(){
    Direction lalala;
    return lalala;
}

//==============PlayerBacktrack funct================
std::vector<Direction> PlayerBacktrack::find_solution(){
    std::vector<Direction> lalala;
    return lalala;
}

bool PlayerBacktrack::found_solution(){
    return true;
}

Direction PlayerBacktrack::next_move(){
    Direction lalala;
    return lalala;
}