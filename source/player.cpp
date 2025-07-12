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

std::deque<Position>& Player::get_nextpositions(){return this->nextpositions;}
std::deque<Direction>& Player::get_nextdirection(){ return this->nextdirection; }

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

//Getters
bool Player::check_if_next_is_playable(Level lvl, Position pos, Direction dir){
    //Checking up
    if ((dir.m_current_dir == 0) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() - 1) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() - 1) == '.')){ return false; }
    //Checking down
    else if (((dir.m_current_dir == 1)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() + 1) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() + 1) == '.')){ return false; }
    //Checking left
    else if (((dir.m_current_dir == 2)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x() - 1, pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x() - 1, pos.get_y()) == '.')){ return false; }
    //Checking right
    else if (((dir.m_current_dir == 3)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x() + 1, pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x() + 1, pos.get_y()) == '.')){ return false; }
    return true;
}

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