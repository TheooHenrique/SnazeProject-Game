#ifndef LEVEL
#define LEVEL
#include <cstddef>
#include "simulation.cpp"

class Level{
    private:
    size_t m_width;
    size_t m_length;
    Position m_spawnpoint;
    Position m_food_coords;

    public:
    void set_width(size_t);
    void set_length(size_t);
    size_t get_spawnpoint();
    Position generate_food();
};



#endif