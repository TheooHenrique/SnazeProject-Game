#ifndef PLAYER
#define PLAYER
#include "positiondirection.hpp"
#include "level.hpp"
#include <deque>
#include <vector>

class Player{
    private:
    std::deque<Position> nextpositions;
    public:
    //Methods
    virtual ~Player() = default;
    virtual Direction next_move();
    bool check_if_next_is_playable(Level, Position, Direction);
    void change_direction(Direction&);

    //Getters
    std::deque<Position>& get_nextpositions();

    //Setters
};

class PlayerRandom : public Player{
    public:
    //Random Constructor 
    PlayerRandom(){ }

    //Methods
    Direction next_move() override;
};



class PlayerBacktrack : public Player{
    public:
    //Backtrack Constructor 
    PlayerBacktrack(){ }

    //Methods
    std::vector<Direction> find_solution();
    bool found_solution();
    Direction next_move() override;
};


#endif