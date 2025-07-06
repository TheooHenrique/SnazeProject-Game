#include "player.hpp"
#include "positiondirection.hpp"
#include <vector>
//==============Player funct================
Snake Player::get_snake(){return this->sn;}
Direction Player::next_move(){
    Direction lalala;
    return lalala;
};

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