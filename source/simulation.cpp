#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include "dictionarys.hpp"
#include "player.hpp"
#include "positiondirection.hpp"
#include "simulation.hpp"

//====================Simulation Func========================

void SnazeSimulation::usage(){
    std::cout << "Usage: snaze [<options>] <input_level_file>\n";
    std::cout << "Game simulation options:\n";
    std::cout << "--help Print this help text.\n";
    std::cout << "--fps <num> Number of frames (board) presented per second.\n";
    std::cout << "--lives <num> Number of lives the snake shall have. Default = 5.\n";
    std::cout << "--food <num> Number of food pellets for the entire simulation. Default = 10.\n";
    std::cout << "--playertype <type> Type of snake intelligence: random, backtracking. Default = backtracking\n";
}

void SnazeSimulation::initialize(int argc, char* argv[]){
    size_t aux = -1;
    size_t count{0};
    for (size_t ct{1}; ct < argc ; ++ct){
        //Capturing the level file.
        std::string extension = std::filesystem::path(argv[ct]).extension().string();
        if (extension == ".dat"){
            if (count == 0){
                std::ifstream config_file;
                config_file.open(std::filesystem::path(argv[ct]));
                if (!config_file.is_open()) {std::cerr << "Error: Cannot open the config file!: " << argv[ct] << std::endl;} //Possib error
                this->m_levels = read.parse_cfg(config_file);
                config_file.close();
                count++;

                //Setting configuration based on current_level:
                
                if (this->m_levels.size() > 0){ this->m_current_lvl = m_levels[0]; }
                else{std::cerr << "Error! Your inputed level file has no valid level!\n"; break;}
            } else{ std::cerr << "Error! You inputed two or more .dat files!\n"; break;}
        }
        
        //Capturing the configurations
        auto it{items_with_their_keys.find(argv[ct])};
        my_player = new Player();
        if (it != items_with_their_keys.end()){
            interface selected_option {it->second};
            if (selected_option == HELP){usage(); exit(0);}
            if (ct + 1 < argc){
                if (selected_option == FPS){try{set_fps(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at fps option!\n"; }}
                if (selected_option == FOOD){try{m_current_lvl.set_food_amount(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at food option!\n";}}
                if (selected_option == LIVES){try{aux = std::stoi(argv[ct + 1]);} catch(const std::runtime_error& e){std::cerr << "Error: You inserted a invalid type at lives option!\n";}}
                if (selected_option == PLAYERTYPE){try{
                        if (strcmp(argv[ct+1], "backtracking") == 0){
                            if (aux != -1){ this->get_snake().set_lives(aux);} //Tem que alterar isso aqui. Tem que setar o player como backtrack player
                            my_player = new Player();
                        }
                        else if(strcmp(argv[ct+1], "random") == 0){
                            if (aux != -1){ this->get_snake().set_lives(aux) ;} //Tem que alterar isso aqui. Tem que setar o player como random player
                            my_player = new Player();
                        } else{
                            std::cout << "WARNING: You inserted a invalid type at player type option! Starting with backtracking player by default.\n";
                            if (aux != -1){ this->get_snake().set_lives(aux);}
                            my_player = new Player();
                        }
                } catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at player type option!\n";}}
            }
            else {std::cerr << "Error: You don't inserted some of the config parameters!\n";}
        }
    }
}

void SnazeSimulation::startdirection(){ 
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<size_t> vec = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    std::shuffle(vec.begin(), vec.end(), g);
    size_t choosen_value = vec[0];
    sn.set_dir(choosen_value);
    
 }

void SnazeSimulation::process_events(){
    if (m_current_state == READING_INPUT){
        m_current_lvl = m_levels[0];
        sn.set_eated(0);
        //Defining first direction of snake head
        startdirection();

        //Finding SpawnPoint
        size_t ct{0};
        for (size_t i{0}; i < m_current_lvl.get_maze().size(); ++i){
            if ( m_current_lvl.get_maze()[i].find('&') != std::string::npos){
                m_current_lvl.set_spawnpoint(Position(m_current_lvl.get_maze()[i].find('&'), i));
                sn.set_current_pos(m_current_lvl.get_spawnpoint());
                sn.initialize_body(sn.get_current_pos()); 
                if (sn.get_dir().m_current_dir == 0){ get_snake().set_position(get_current_level(), '^', get_current_level().get_spawnpoint()); m_head = '^'; }
                else if (sn.get_dir().m_current_dir == 1){ get_snake().set_position(get_current_level(), 'v', get_current_level().get_spawnpoint()); m_head = 'v'; }
                else if (sn.get_dir().m_current_dir == 2){ get_snake().set_position(get_current_level(), '<', get_current_level().get_spawnpoint()); m_head = '<'; }
                else if (sn.get_dir().m_current_dir == 3){ get_snake().set_position(get_current_level(), '>', get_current_level().get_spawnpoint()); m_head = '>'; }
                ++ct;
                break;
            } if (ct == m_levels.size()){ std::cerr << "Error! Your loaded level do not show any spawnpoint!"; break; }
        }
        m_levels.pop_front();
    }
    else if (m_current_state == WAITING_START){  }
    //==================================================================================================================================
    else if (m_current_state == RANDOM_SEARCH){
        m_current_lvl.generate_food();
        m_current_lvl.place_food_in_maze(m_current_lvl.get_food_cords());

        Position current_pos_for_search = sn.get_current_pos();
        Direction current_dir_for_search = sn.get_dir();

        size_t max_search_iterations = 100000; 
        size_t current_iteration = 0;

        while(current_pos_for_search != m_current_lvl.get_food_cords() && current_iteration < max_search_iterations){
            ++current_iteration;

            if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, current_dir_for_search)){
                Position next_step_pos = current_pos_for_search;
                Direction next_step_dir = current_dir_for_search;
                if (current_dir_for_search.m_current_dir == Direction::UP) {
                    next_step_pos.set_y(next_step_pos.get_y() - 1);
                    if (next_step_pos == m_current_lvl.get_food_cords()){  }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
                else if (current_dir_for_search.m_current_dir == Direction::DOWN) {
                    next_step_pos.set_y(next_step_pos.get_y() + 1);
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
                else if (current_dir_for_search.m_current_dir == Direction::LEFT) {
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                else if (current_dir_for_search.m_current_dir == Direction::RIGHT) {
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }

                current_pos_for_search = next_step_pos;
            } else { my_player->change_direction(current_dir_for_search); }
        }
    }//==================================================================================================================================
    else if (m_current_state == WALKING){
        {std::cout << "\nTAMANHO DO VETOR DE DECISOES: " << my_player->get_nextdirection().size() << std::endl;}
        if (!my_player->get_nextdirection().empty()) {
            Position prev_head = sn.get_current_pos();

            // Clear the current position
            sn.set_position(m_current_lvl, ' ', sn.get_current_pos());

            // Get the next direction
            Direction next_dir = my_player->get_nextdirection().front();
            my_player->get_nextdirection().pop_front();
            sn.set_dir(next_dir.m_current_dir);

            // Change the previous position of the snake to the new position
            Position new_pos = sn.get_current_pos();
            switch(next_dir.m_current_dir) {
                case Direction::UP:    new_pos.set_y(new_pos.get_y() - 1); break;
                case Direction::DOWN:  new_pos.set_y(new_pos.get_y() + 1); break;
                case Direction::LEFT:  new_pos.set_x(new_pos.get_x() - 1); break;
                case Direction::RIGHT: new_pos.set_x(new_pos.get_x() + 1); break;
            }
            
            // Change the head char before print
            char head_char;
            switch(next_dir.m_current_dir) {
                case Direction::UP:    head_char = '^'; break;
                case Direction::DOWN:  head_char = 'v'; break;
                case Direction::LEFT:  head_char = '<'; break;
                case Direction::RIGHT: head_char = '>'; break;
            }
            
            // Finally moves the snake
            sn.set_position(m_current_lvl, head_char, new_pos);
            sn.set_current_pos(new_pos);
            m_head = head_char;
            
            // Delay TEM QUE COLOCAR PRA O PLAYER DECIDIR DEPOIS. DEFAULT VAI SER 500MS
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }//==================================================================================================================================
    else if (m_current_state == FOUND){
        sn.set_eated(sn.get_eated() + 1);
        //sn.get_body().push_back();
        
    }
}

void SnazeSimulation::update(){
    if (m_current_state == START){ m_current_state = READING_INPUT; }
    else if (m_current_state == READING_INPUT){ m_current_state = WAITING_START; }
    else if (m_current_state == WAITING_START){if (std::cin.get() == '\n') {m_current_state = RANDOM_SEARCH;}}//TEMPORÁRIO! Depois tem que fazer o backtracking!
    else if (m_current_state == RANDOM_SEARCH){m_current_state = WALKING; }
    else if (m_current_state == WALKING){
            if (my_player->get_nextdirection().empty() || sn.get_current_pos() == m_current_lvl.get_food_cords()) { m_current_state = FOUND; }
            //else if (bateu) {m_current_state = DEAD}
        }
    else if (m_current_state == FOUND){
        if (sn.get_eated() == m_current_lvl.get_food_amount()){
            if (m_levels.empty()){ m_current_state = WON_GAME; }
            else{ m_current_state = READING_INPUT; }
        }
        else { m_current_state = RANDOM_SEARCH; }
    }
    else if (m_current_state == WON_GAME){ m_current_state = END; }
    else if (m_current_state == END){ this->is_over = true; }
}

void SnazeSimulation::render(){
    if (m_current_state == WAITING_START){
        m_current_lvl.print_level(m_current_lvl);
        std::cout << "\nPress enter to start the game!\n";
    }
    else if (m_current_state == RANDOM_SEARCH){ std::cout << "\nThinking...\n"; }
    else if (m_current_state == WALKING){
        std::cout << "Eaten Food: " << sn.get_eated() << std::endl;
        m_current_lvl.print_level(m_current_lvl);
    }
    else if (m_current_state == WON_GAME){ std::cout << "\n==============================================\nCONGRATS!!!!!!!!!!!!!!!!!!!!\nYOU WON!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n==============================================\n";}
} //Alterar essa coisa horrorosa aqui em cima depois.

//==================Setters===================
void SnazeSimulation::set_fps(size_t value){ this->m_fps = value; }
void SnazeSimulation::set_levels(std::deque<Level> lvl){ this->m_levels = lvl;}

//==================Getters===================
std::deque<Level> SnazeSimulation::get_levels(){ return this->m_levels; }
Player SnazeSimulation::get_player(){ return *this->my_player; }
Level& SnazeSimulation::get_current_level() { return m_current_lvl; }
Snake SnazeSimulation::get_snake(){return this->sn;}