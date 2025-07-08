#ifndef SIMULATION
#define SIMULATION


#include "level.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <vector>

class SnazeSimulation{

    private:
    SnazeSimulation(){
        m_current_state = START;
    }
    enum m_possible_states : uint8_t{
        START,
        READING_INPUT,
        INVALID_INPUT,
        WAITING_START,
        BACKTRACK_SEARCH,
        RANDOM_SEARCH,
        WALKING,
        FOUND,
        DEAD,
        WON_ROUND,
        WON_GAME,
        LOST,
        END
    };
    size_t m_current_state;
    size_t m_fps;
    Level m_current_lvl;
    Player* my_player;
    std::vector<Level> m_levels;
    Reader read;


    public:
    
    void usage();
    void initialize(int, char*[]);
    bool is_over();
    void process_events();
    void update();
    void render();
    void set_fps(size_t);

    Player get_player();
    Level get_current_level();
    
    std::vector<Level> get_levels();
    void set_levels(std::vector<Level>);
    static SnazeSimulation& get_instance(){
        static SnazeSimulation sg;
        return sg;
    }

};
    

#endif