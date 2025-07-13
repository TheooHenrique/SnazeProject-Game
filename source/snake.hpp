#ifndef SNAKE
#define SNAKE
#include "level.hpp"
#include "positiondirection.hpp"
#include <cstddef>
#include <deque>
class Snake{
    private:
    Direction m_current_dir;
    size_t m_current_size{1};
    size_t m_eaten_food{0};
    size_t m_lives;
    size_t m_current_score;
    std::deque<Position> m_snake_body;
    Position m_current_pos;
    Position m_current_pos2;

    //Constructor:
    Snake(){
        m_current_score = 0;
        m_eaten_food = 0;
    }
    
    public:
    static Snake& get_instance(){
        static Snake sn;
        return sn;
    }

    //Methods
    void add_segment(const Position& pos);
    void remove_last_segment();
    void initialize_body(const Position& head_pos);


    //Getters
    Position get_current_pos();
    Position get_current_pos2();
    Direction& get_dir();
    size_t get_size();
    size_t get_eated();
    size_t get_lives();
    size_t get_score();
    std::deque<Position>& get_body();

    //Setters
    
    void set_body(std::deque<Position>);
    void set_current_pos(Position);
    void set_current_pos2(Position);
    void set_dir(size_t);
    void set_size(size_t);
    void set_eated(size_t);
    void set_lives(size_t);
    void set_score(size_t);
    void set_position(Level&, char, Position);
};
#endif