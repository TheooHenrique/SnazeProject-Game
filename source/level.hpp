#ifndef LEVEL
#define LEVEL
#include <cstddef>
#include "positiondirection.hpp"

class Level{
    private:
    
    size_t m_width;
    size_t m_length;
    size_t food_amount;
    Position m_spawnpoint;
    Position m_food_coords;
    

    public:
    Level(){

    }
    void set_width(size_t);
    void set_length(size_t);
    void set_food_amount(size_t);
    Position get_spawnpoint();
    Position generate_food();
};



#endif