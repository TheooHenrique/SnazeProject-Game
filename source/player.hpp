#ifndef PLAYER
#define PLAYER
#include "positiondirection.hpp"
#include "snake.hpp"
#include <vector>

class Player{
    private:
    Snake &sn = Snake::get_instance();

    public:
    Snake get_snake();
    virtual ~Player() = default;
    virtual Direction next_move();
};



class PlayerRandom : public Player{
    private:

    public:
    //Constructor Random
    PlayerRandom(){

    }
    Direction next_move() override;
};



class PlayerBacktrack : public Player{
    private:


    public:
    //Constructor Backtrack
    PlayerBacktrack(){

    }
    std::vector<Direction> find_solution();
    bool found_solution();
    Direction next_move() override;
};


#endif