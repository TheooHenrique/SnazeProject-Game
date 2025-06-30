#ifndef SIMULATION
#define SIMULATION

#include <cstddef>
#include <cstdint>
#include <string>

class SnazeSimulation{

    private:
    SnazeSimulation(){
        m_current_state = START;
    }

    enum m_possible_states : uint8_t{
        START,
    };
    size_t m_current_state;
    size_t m_fps;

    public:
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
class Position{
    private:
    size_t m_x;
    size_t m_y;

    public:
    size_t get_x();
    size_t get_y();
    void set_y(size_t);
    void set_x(size_t);
};

class Direction{
    private:
    std::string m_current_dir;

    public:
    void set_dir(std::string);
    std::string get_dir();
};


    

#endif