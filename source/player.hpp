#ifndef PLAYER
#define PLAYER
#include "simulation.hpp"
#include <string>
#include <vector>

class PlayerType{
    private:
    std::string m_player_type;

    public:
    std::string get_type();
    void set_type(std::string);
};

class PlayerRandom{
    private:

    public:
    Direction next_move();
};

class PlayerBacktrack{
    private:

    public:
    std::vector<Direction> find_smart_solution();
    bool found_solution();
    Direction next_move();
};


#endif