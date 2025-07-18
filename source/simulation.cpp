#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include "dictionaries.hpp"
#include "player.hpp"
#include "positiondirection.hpp"
#include "simulation.hpp"

/**
 * @file simulation.cpp
 * @brief Implements the main game logic for the SnazeSimulation class.
 */

/**
 * @brief Prints command-line usage instructions.
 */
void SnazeSimulation::usage(){
    std::cout << "Usage: snaze [<options>] <input_level_file>\n";
    std::cout << "Game simulation options:\n";
    std::cout << "--help Print this help text.\n";
    std::cout << "--fps <num> Number of frames (board) presented per second. Default = 10\n";
    std::cout << "--lives <num> Number of lives the snake shall have. Default = 5.\n";
    std::cout << "--food <num> Number of food pellets for the entire simulation. Default = 10.\n";
    std::cout << "--playertype <type> Type of snake intelligence: random, backtracking. Default = Random (This Project do not implemented the Backtrack player)\n";
}

/**
 * @brief Initializes the game by parsing command-line arguments and loading the level file.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void SnazeSimulation::initialize(int argc, char* argv[]){
    Dictios dicts;
    size_t aux = -1;
    size_t count{0};
    for (size_t ct{1}; ct < argc ; ++ct){
        //Capturing the level file.
        std::string extension = std::filesystem::path(argv[ct]).extension().string();
        if (extension == ".dat"){
            ++count;
            if (count == 1){
                std::ifstream config_file;
                config_file.open(std::filesystem::path(argv[ct]));
                if (!config_file.is_open()) {std::cerr << "Error: Cannot open the config file!: " << argv[ct] << std::endl;} //Possib error
                this->m_levels = read.parse_cfg(config_file);
                config_file.close();

                //Setting configuration based on current_level:
                
                if (this->m_levels.size() > 0){ this->m_current_lvl = m_levels[0]; }
                else{throw std::runtime_error ("Error! Your inputed level file has no valid level!");}
            }
            else{ throw std::runtime_error ("Error! You inputed two or more .dat files!"); }
            
        }
        
        //Capturing the configurations
        dicts.initialize_table();
        auto it{dicts.items_with_their_keys.find(argv[ct])};
        my_player = new Player();
        if (it != dicts.items_with_their_keys.end()){
            Dictios::interface selected_option {it->second};
            if (selected_option == dicts.HELP){usage(); exit(0);}
            if (ct + 1 < argc){
                if (selected_option == dicts.FPS){try{ if (std::stoi(argv[ct + 1]) != 0){set_fps(std::stoi(argv[ct + 1]));};} catch(const std::invalid_argument){
                    std::cout << "=============================================================\n";
                    std::cout << "WARNING: You inserted a invalid type at fps option!\n"; 
                    std::cout << "Please insert a number!\n";
                    std::cout << "Starting with default value (10)\n"; 
                    std::cout << "=============================================================\n\n";
                }}
                if (selected_option == dicts.FOOD){try{aux_food = std::stoi(argv[ct + 1]);} catch(const std::invalid_argument){
                    std::cout << "=============================================================\n";
                    std::cout << "WARNING: You inserted a invalid type at food option!\n";
                    std::cout << "Please insert a number!\n";
                    std::cout << "Starting with default value (10)\n";
                    std::cout << "=============================================================\n\n";
                }}
                if (selected_option == dicts.LIVES){try{ if (std::stoi(argv[ct + 1]) != 0) {sn.set_initial_lives(std::stoi(argv[ct + 1]));} ;} catch(const std::invalid_argument){
                    std::cout << "=============================================================\n";
                    std::cout << "WARNING: You inserted a invalid type at lives option!\n";
                    std::cout << "Please insert a number!\n";
                    std::cout << "Starting with default value (5)\n";
                    std::cout << "=============================================================\n\n";
                }}
                    
                if (selected_option == dicts.PLAYERTYPE){
                    if (strcmp(argv[ct+1], "backtracking") == 0){ std::cout << "- WARNING: I am so sorry but this program do not implemented the backtracking player! :(\n- Starting with Random by default\n\n"; }
                    else if(strcmp(argv[ct+1], "random") == 0){ std::cout << "\nStarting with random Player!\n";}
                    else{ std::cout << "WARNING: You inserted a invalid type at player type option! But this project has not implemented the backtracking player :( \nStarting with random player by default.\n\n"; }
                }
            }
            else {
                std::cout << "=============================================================\n";
                std::cout << "WARNING: You don't inserted some of the config parameters!\n";
                std::cout << "Starting with default! \n";
                std::cout << "=============================================================\n\n";
            }
        }
    }
    if (count == 0){ throw std::runtime_error ("Error! Please input at least one .dat file!");}
}

/**
 * @brief Sets a random starting direction for the snake.
 */
void SnazeSimulation::startdirection(){ 
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<size_t> vec = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    std::shuffle(vec.begin(), vec.end(), g);
    size_t choosen_value = vec[0];
    sn.set_dir(choosen_value);
    
}

/**
 * @brief Handles the core logic for the current game state.
 *
 * This function is the heart of the gameplay. It uses a state machine to determine
 * what actions to perform, such as resetting the level, finding a path for the snake,
 * moving the snake, or handling a crash.
 */
void SnazeSimulation::process_events(){
    if (m_current_state == READING_INPUT){
        //Reset the dead state of the snake
        dead = false;

        //Treating the initializer config for each level
        m_current_lvl = m_levels[0];
        if (aux_food != 0){m_current_lvl.set_food_amount(aux_food);}
        sn.set_eated(0);
        sn.set_size(1);
        sn.set_score(0);

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
    else if (m_current_state == WAITING_START){
        dead = false;
        m_current_lvl.set_position(sn.get_current_pos(), ' ');
        sn.set_current_pos(m_current_lvl.get_spawnpoint());
        
    }
    //==================================================================================================================================
    else if (m_current_state == RANDOM_SEARCH){
        if (dead) { return; }
        no_path = false;

        if (!m_current_lvl.there_is_food_at_maze()){
            m_current_lvl.generate_food();
            m_current_lvl.place_food_in_maze(m_current_lvl.get_food_cords());
        }

        //virtual snake to simulate its walking
        current_pos_for_search = sn.get_current_pos();
        Direction current_dir_for_search = sn.get_dir();
        std::deque<Position> simulated_body = sn.get_body();
        size_t simulated_snake_size = sn.get_size();


        //Clear the previous deque of decisions
        my_player->get_nextdirection().clear(); 

        std::random_device rd;
        std::mt19937 g(rd());
        std::vector<Direction> possib_dir;

        while(current_pos_for_search != m_current_lvl.get_food_cords()){

            Position next_step_pos = current_pos_for_search;

            //-------------------------------------------------------- IF SNAKE IS TURNED UP -------------------------------------------------------- 
            if (current_dir_for_search == Direction::UP){
                
                possib_dir.clear();
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::UP);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){
                    possib_dir.push_back(Direction::LEFT);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){
                    possib_dir.push_back(Direction::RIGHT);
                }

                if (possib_dir.empty()){ no_path = true; break;}
                std::shuffle(possib_dir.begin(), possib_dir.end(), g);
                if (possib_dir[0] == Direction::UP){
                    next_step_pos.set_y(next_step_pos.get_y() - 1); //MOVE THE SNAKE WHILE THINKING
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++;
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
                else if (possib_dir[0] == Direction::LEFT){
                    current_dir_for_search = Direction::LEFT;
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++;
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                else if (possib_dir[0] == Direction::RIGHT){
                    current_dir_for_search = Direction::RIGHT;
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; // CRESCE
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
            }
            //-------------------------------------------------------- IF SNAKE IS TURNED DOWN -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::DOWN){
                                
                possib_dir.clear();
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::DOWN);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){
                    possib_dir.push_back(Direction::LEFT);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){
                    possib_dir.push_back(Direction::RIGHT);
                }

                
                if (possib_dir.empty()){no_path = true; break;}

                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                if (possib_dir[0] == Direction::DOWN){
                    next_step_pos.set_y(next_step_pos.get_y() + 1); //MOVE THE SNAKE WHILE THINKING
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++;
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
                
                else if (possib_dir[0] == Direction::LEFT){
                    current_dir_for_search = Direction::LEFT;
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        // se NÃO comeu, remove
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                
                else if (possib_dir[0] == Direction::RIGHT){
                    current_dir_for_search = Direction::RIGHT;
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++;
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
            }
            //-------------------------------------------------------- IF THE SNAKE IF TURNED LEFT -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::LEFT){

                possib_dir.clear();
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::LEFT);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){
                    possib_dir.push_back(Direction::UP);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){
                    possib_dir.push_back(Direction::DOWN);
                }

                if (possib_dir.empty()){no_path = true; break;}

                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                if (possib_dir[0] == Direction::LEFT){
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                    
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                else if (possib_dir[0] == Direction::UP){
                    current_dir_for_search = Direction::UP;
                    next_step_pos.set_y(next_step_pos.get_y() - 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);

                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
                
                else if (possib_dir[0] == Direction::DOWN){
                    current_dir_for_search = Direction::DOWN;
                    next_step_pos.set_y(next_step_pos.get_y() + 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
            }
            //-------------------------------------------------------- IF SNAKE IS TURNED RIGHT -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::RIGHT){

                possib_dir.clear();
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){
                    possib_dir.push_back(Direction::RIGHT);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){
                    possib_dir.push_back(Direction::UP);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){
                    possib_dir.push_back(Direction::DOWN);
                }

                if (possib_dir.empty()){no_path = true; break;}

                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                if (possib_dir[0] == Direction::RIGHT){
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++;
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
                else if (possib_dir[0] == Direction::UP){
                    current_dir_for_search = Direction::UP;
                    next_step_pos.set_y(next_step_pos.get_y() - 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
               
                else if (possib_dir[0] == Direction::DOWN){
                    current_dir_for_search = Direction::DOWN;
                    next_step_pos.set_y(next_step_pos.get_y() + 1);
                    bool simulated_ate_food = (next_step_pos == m_current_lvl.get_food_cords());
                    if (simulated_ate_food) {
                        simulated_snake_size++; 
                    }
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                       
                        if (!simulated_ate_food && simulated_body.size() >= simulated_snake_size) {
                            simulated_body.pop_back();
                        }
                    }
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
            }
            
            current_pos_for_search = next_step_pos;
        }

    }//==================================================================================================================================
    else if (m_current_state == WALKING){
        //{std::cout << "\nTAMANHO DO VETOR DE DECISOES: " << my_player->get_nextdirection().size() << std::endl;}

        if (my_player->get_nextdirection().empty()) {
                
                if (my_player->check_if_snake_is_prision(m_current_lvl, sn.get_current_pos(), sn.get_dir(), sn.get_body())) {
                    sn.set_position(m_current_lvl, 'X', sn.get_current_pos());
                    dead = true;
                    sn.set_lives(sn.get_lives() - 1);

                    size_t current_score {sn.get_score()};
                    if (current_score >= 10) {
                        sn.set_score(current_score - 10);
                    } else {
                        sn.set_score(0);
                    }

                    if (sn.get_lives() == 0) {
                        std::cout << "=============================================================\n";
                        std::cout << "CRASHED!\n";
                        std::cout << "And your lives are over!\n";
                        std::cout << "Hope you get well! Good luck next time babe!\n";
                        std::cout << "=============================================================\n\n";
                    } else {
                        std::cout << "=============================================================\n";
                        std::cout << "CRASHED!\n";
                        std::cout << "But you still have "<< sn.get_lives() << " lives!\n";
                        std::cout << "You can Restart the game!\n";
                        std::cout << "=============================================================\n\n";
                    }
                    
                }
            }

        if (!my_player->get_nextdirection().empty()) {
                Position prev_head = sn.get_current_pos();
                Position old_tail;
                bool has_body_to_remove = false;
                
                if (!sn.get_body().empty()) {
                    old_tail = sn.get_body().back();
                    has_body_to_remove = true;
                }

                // Clear the current head position
                sn.set_position(m_current_lvl, ' ', prev_head);

                // Get next direction and calculate new position
                Direction next_dir = my_player->get_nextdirection().front();
                my_player->get_nextdirection().pop_front();
                sn.set_dir(next_dir.m_current_dir);

                Position new_pos = prev_head;
                switch(next_dir.m_current_dir) {
                    case Direction::UP:    new_pos.set_y(new_pos.get_y() - 1); break;
                    case Direction::DOWN:  new_pos.set_y(new_pos.get_y() + 1); break;
                    case Direction::LEFT:  new_pos.set_x(new_pos.get_x() - 1); break;
                    case Direction::RIGHT: new_pos.set_x(new_pos.get_x() + 1); break;
                }

                bool ate_comida = (new_pos == m_current_lvl.get_food_cords());

                // Handle food eating
                if (ate_comida) {
                    m_current_lvl.set_position(new_pos, ' ');
                    sn.set_eated(sn.get_eated() + 1);
                    sn.set_score(sn.get_score() + 100);
                    // We'll grow by keeping the tail in place next move
                }

                // Update body before moving head
                std::deque<Position>& body = sn.get_body();
                if (sn.get_size() > 1) {
                    body.push_front(prev_head);
                    
                    // If didn't eat, remove tail
                    if (!ate_comida && body.size() > sn.get_size() - 1) {
                        sn.set_position(m_current_lvl, ' ', old_tail);
                        body.pop_back();
                    }
                } else if (ate_comida) {
                    // Special case: first body segment when size was 1
                    body.push_front(prev_head);
                }

                // Update snake size if ate food
                if (ate_comida) {
                    sn.set_size(sn.get_size() + 1);
                }

                // Set new head position
                char head_char;
                switch(next_dir.m_current_dir) {
                    case Direction::UP:    head_char = '^'; break;
                    case Direction::DOWN:  head_char = 'v'; break;
                    case Direction::LEFT:  head_char = '<'; break;
                    case Direction::RIGHT: head_char = '>'; break;
                }
                
                sn.set_position(m_current_lvl, head_char, new_pos);
                sn.set_current_pos(new_pos);
                m_head = head_char;

                // Draw body segments
                for (const auto& seg : body) {
                    sn.set_position(m_current_lvl, 'o', seg);
                }
                //Delay
                std::this_thread::sleep_for(std::chrono::milliseconds(m_fps));
            }

    }//==================================================================================================================================
}

/**
 * @brief Transitions the game from the current state to the next.
 *
 * This function acts as the transition logic for the finite state machine.
 * For example, it transitions from RANDOM_SEARCH to WALKING, or from WALKING to DEAD.
 */
void SnazeSimulation::update(){
    if (m_current_state == START){ m_current_state = READING_INPUT; }
    else if (m_current_state == READING_INPUT){ m_current_state = WAITING_START; }
    else if (m_current_state == WAITING_START){if (std::cin.get() == '\n') {m_current_state = RANDOM_SEARCH;}}
    else if (m_current_state == RANDOM_SEARCH){ m_current_state = WALKING; }
    else if (m_current_state == WALKING){
        if (dead){
            if (sn.get_lives() == 0){m_current_state = DEAD;}
            else{ m_current_state = WAITING_START; }
        }
        else if (my_player->get_nextdirection().empty() && !dead) { m_current_state = FOUND; }

        }
    else if (m_current_state == FOUND){
        if (sn.get_eated() == m_current_lvl.get_food_amount()){ 
            if (m_levels.empty()){ m_current_state = WON_GAME; }
            else{ m_current_state = READING_INPUT; } 
        }
        else if (dead) { m_current_state = WAITING_START; } 
        else{ m_current_state = RANDOM_SEARCH; }
    }
    else if (m_current_state == WON_GAME){ m_current_state = END; }
    else if (m_current_state == DEAD) { m_current_state = END; }
    else if (m_current_state == END){ this->is_over = true; }
}

/**
 * @brief Renders the visual representation of the current game state to the console.
 *
 * This includes drawing the header (lives, score), the maze with the snake and food,
 * and any relevant messages for the player.
 */
void SnazeSimulation::render(){
    auto print_header = [&]() {
        std::cout << "Lives: ";
        for (size_t i{0}; i < sn.get_lives(); ++i) {
            std::cout << "❤️ ";
        }
        for (size_t i{0}; i < (sn.get_initial_lives() - sn.get_lives()); ++i) {
            std::cout << "💔";
        }

        std::cout << "| Score: " << sn.get_score();
        std::cout << " | Food eaten: " << sn.get_eated() << " of " << m_current_lvl.get_food_amount();
        std::cout << std::endl;

        for(size_t i{0}; i < m_current_lvl.get_maze()[0].length() + 5; ++i) {
            std::cout << "-";
        }
        std::cout << std::endl;
    };

    auto render_maze = [&](){
        const auto& maze = m_current_lvl.get_maze();
        for (size_t y = 0; y < maze.size(); ++y) {
            for (size_t x = 0; x < maze[y].size(); ++x) {
                char current_char = maze[y][x];

                if (current_char == '#') {
                    std::cout << "█";
                } else if (current_char == '.') {
                    std::cout << " ";
                } else if (current_char == 'f') {
                    std::cout << "𓆣";
                } else if (current_char == 'o') {
                    std::cout << "●";
                } else {
                    std::cout << current_char;
                }
            }
            std::cout << std::endl;
        }
    };

    if (m_current_state == WAITING_START){
        //std::cout << "\033[2J\033[H";
        print_header();
        render_maze();
        //m_current_lvl.print_level(m_current_lvl);
        std::cout << "\n>>> Press <ENTER> to start the level!\n";
    }
    else if (m_current_state == RANDOM_SEARCH){
        //std::cout << "\033[2J\033[H";
        print_header();
        render_maze();
        //m_current_lvl.print_level(m_current_lvl);
        std::cout << "\n>>> Thinking...\n";
    }
    else if (m_current_state == WALKING || m_current_state == FOUND){
        //std::cout << "\033[2J\033[H";
        print_header();
        render_maze();
        //m_current_lvl.print_level(m_current_lvl);
    }
    else if (m_current_state == WON_GAME){
        std::cout << "========================================\n";
        std::cout << "       🎉 CONGRATULATIONS! 🎉          \n";
        std::cout << "            YOU WON THE GAME!           \n";
        std::cout << "========================================\n";
    }
    else if (m_current_state == DEAD){
        print_header();
        //m_current_lvl.print_level(m_current_lvl);
        std::cout << "\n========================================\n";
        std::cout << "            GAME OVER! 😥             \n";
        std::cout << "      You lost all your lives!        \n";
        std::cout << "========================================\n";
    }
}



void SnazeSimulation::set_fps(size_t value){ this->m_fps = 1000/value; }
void SnazeSimulation::set_levels(std::deque<Level> lvl){ this->m_levels = lvl;}



std::deque<Level> SnazeSimulation::get_levels(){ return this->m_levels; }
Player SnazeSimulation::get_player(){ return *this->my_player; }
Level& SnazeSimulation::get_current_level() { return m_current_lvl; }
Snake SnazeSimulation::get_snake(){return this->sn;}
