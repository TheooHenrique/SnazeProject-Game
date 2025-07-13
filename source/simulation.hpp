#ifndef SIMULATION
#define SIMULATION


#include "level.hpp"
#include "player.hpp"
#include "reader.hpp"
#include <cstddef>
#include <cstdint>

#include "snake.hpp"

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
    std::deque<Level> m_levels;
    Reader read;
    char m_head;
    bool dead;


    public:
    
    //Methods:
    void usage();
    void initialize(int, char*[]);
    bool is_over;
    void startdirection();
    void process_events();
    void update();
    void render();

    //Setters
    void set_fps(size_t);
    void set_levels(std::deque<Level>);

    //Getters
    Snake get_snake();
    Player get_player();
    Level& get_current_level ();
    std::deque<Level> get_levels();

    //Singleton Pattern Implementation
    Snake &sn = Snake::get_instance();
    static SnazeSimulation& get_instance(){
        static SnazeSimulation sg;
        return sg;
    }

};
    

#endif