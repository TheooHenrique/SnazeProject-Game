#ifndef SIMULATION
#define SIMULATION


#include "level.cpp"
#include "player.cpp"
#include <cstddef>
#include <cstdint>

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
    Level lvl;
    Player* my_player;


    public:
    
    void usage();
    void initialize(int, char*[]);
    bool is_over();
    void process_events();
    void update();
    void render();
    void set_fps(size_t);
    static SnazeSimulation& get_instance(){
        static SnazeSimulation sg;
        return sg;
    }

};
    

#endif