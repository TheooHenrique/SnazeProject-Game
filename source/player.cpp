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

    // 1. Verificar colisão com paredes ou paredes invisíveis
    char item_at_next_pos = lvl.get_item_pos(lvl.get_maze(), next_pos.get_x(), next_pos.get_y());
    if (item_at_next_pos == '#' || item_at_next_pos == '.') {
        return false; // Colidiu com parede ou parede invisível
    }

    // 2. Verificar colisão com o próprio corpo da cobra
    // Começamos a partir do segundo elemento para evitar a cabeça da cobra
    // já que a cabeça estará na `next_pos` após o movimento.
    for (size_t i = 0; i < snake_body.size(); ++i) { // Ajuste para não verificar a cabeça
        if (next_pos.get_x() == snake_body[i].get_x() && next_pos.get_y() == snake_body[i].get_y()) {
            return false; // Colidiu com o corpo da cobra
        }
    }
    
    return true; // A próxima posição é jogável









    /*
    //Checking up
    if ((dir.m_current_dir == 0) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() - 1) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() - 1) == '.' )){ return false; }
    //Checking down
    else if (((dir.m_current_dir == 1)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() + 1) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x(), pos.get_y() + 1) == '.')){ return false; }
    //Checking left
    else if (((dir.m_current_dir == 2)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x() - 1, pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x() - 1, pos.get_y()) == '.')){ return false; }
    //Checking right
    else if (((dir.m_current_dir == 3)) && (lvl.get_item_pos(lvl.get_maze(), pos.get_x() + 1, pos.get_y()) == '#' || lvl.get_item_pos(lvl.get_maze(), pos.get_x() + 1, pos.get_y()) == '.')){ return false; }
    return true;
    */
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