#ifndef SNAKE
#define SNAKE
#include "positiondirection.hpp"
#include <cstddef>
#include <vector>
class Snake{
    private:
    Direction m_current_dir;
    size_t m_current_size;
    size_t m_eaten_food;
    size_t m_lives;
    size_t m_current_score;
    std::vector<Position> m_snake_body;
    //Constructor:
    Snake(){
        m_current_size = 1;
    }

    public:
    static Snake& get_instance(){
        static Snake sn;
        return sn;
    }
    size_t get_dir();
    size_t get_size();
    size_t get_eated();
    size_t get_lives();
    size_t get_score();
    size_t get_body();
    void set_dir(Direction);
    void set_size(size_t);
    void set_eated(size_t);
    void set_lives(size_t);
    void set_score(size_t);
};
#endif