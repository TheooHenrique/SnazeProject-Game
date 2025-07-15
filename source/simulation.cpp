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
    Dictios dicts;
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
        dicts.initialize_table();
        auto it{dicts.items_with_their_keys.find(argv[ct])};
        my_player = new Player();
        if (it != dicts.items_with_their_keys.end()){
            Dictios::interface selected_option {it->second};
            if (selected_option == dicts.HELP){usage(); exit(0);}
            if (ct + 1 < argc){
                if (selected_option == dicts.FPS){try{set_fps(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at fps option!\n"; }}
                if (selected_option == dicts.FOOD){try{m_current_lvl.set_food_amount(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at food option!\n";}}
                if (selected_option == dicts.LIVES){try{aux = std::stoi(argv[ct + 1]);} catch(const std::runtime_error& e){std::cerr << "Error: You inserted a invalid type at lives option!\n";}}
                if (selected_option == dicts.PLAYERTYPE){try{
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
        dead = false;
        m_current_lvl = m_levels[0];
        sn.set_eated(0);
        sn.set_size(1);
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
        if (dead) { return; }
        m_current_lvl.generate_food();
        m_current_lvl.place_food_in_maze(m_current_lvl.get_food_cords());

        //Cobra "VIRTUAL" para simular que ta andando
        Position current_pos_for_search = sn.get_current_pos();
        Direction current_dir_for_search = sn.get_dir();
        std::deque<Position> simulated_body = sn.get_body();
        size_t simulated_snake_size = sn.get_size();


        //Clear the previous deque of decisions
        my_player->get_nextdirection().clear(); 

        std::random_device rd;
        std::mt19937 g(rd());
        std::vector<Direction> possib_dir;

        size_t max_search_iterations = 100000; 
        size_t current_iteration = 0;

        while(current_pos_for_search != m_current_lvl.get_food_cords() && current_iteration < max_search_iterations){
            ++current_iteration;
            Position next_step_pos = current_pos_for_search;

            //ALTERAÇÃO RADICAL NA MUDANÇA DE MOVIMENTO DA COBRA BURRA:
            //-------------------------------------------------------- CASO A COBRA ESTEJA VIRADA PARA CIMA -------------------------------------------------------- 
            if (current_dir_for_search == Direction::UP){
                
                possib_dir.clear();
                //VERIFICA QUAIS POSIÇÕES ESTÃO LIVRES E ARMAZENA EM POSSIB_DIR (VECTOR)
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::UP);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){
                    possib_dir.push_back(Direction::LEFT);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){
                    possib_dir.push_back(Direction::RIGHT);
                }

                //VERIFICA SE A COBRA NÃO ESTÁ SEM SAÍDA
                if (possib_dir.empty()){break;} //<----------------------------------------- ADICIONEI A VERIFICACAO DE MORTE
                //RANDOMIZA A ESCOLHA DA COBRA BURRA
                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                //CASO ELA ESCOLHA SE MANTER INDO UP, ANDE
                if (possib_dir[0] == Direction::UP){
                    next_step_pos.set_y(next_step_pos.get_y() - 1); //MOVE THE SNAKE WHILE THINKING
                    if (simulated_snake_size > 1) { //REFRESH THE SNAKE BODY: TALVEZ TENHA QUE ALTERAR PQ GET_BODY RETORNA O CORPO REAL DA COBRA <----------------------
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::UP);//FEED THE SOLUTION DEQUE
                }
                //CASO ELA ESCOLHA IR PARA A ESQUERDA, VIRE PARA A ESQUERDA E ANDE
                else if (possib_dir[0] == Direction::LEFT){
                    current_dir_for_search = Direction::LEFT;
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                //CASO ELA ESCOLHA IR PARA A ESQUERDA, VIRE PARA A DIREITA E ANDE
                else if (possib_dir[0] == Direction::RIGHT){
                    current_dir_for_search = Direction::RIGHT;
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
            }
            //-------------------------------------------------------- CASO A COBRA ESTEJA VIRADA PARA BAIXO -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::DOWN){
                                
                possib_dir.clear();
                //VERIFICA QUAIS POSIÇÕES ESTÃO LIVRES E ARMAZENA EM POSSIB_DIR (VECTOR)
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::DOWN);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){
                    possib_dir.push_back(Direction::LEFT);
                }if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){
                    possib_dir.push_back(Direction::RIGHT);
                }

                //VERIFICA SE A COBRA NÃO ESTÁ SEM SAÍDA
                if (possib_dir.empty()){break;} //<----------------------------------------- ADICIONEI A VERIFICACAO DE MORTE

                //RANDOMIZA A ESCOLHA DA COBRA BURRA
                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                //CASO ELA ESCOLHA SE MANTER INDO DOWN, ANDE
                if (possib_dir[0] == Direction::DOWN){
                    next_step_pos.set_y(next_step_pos.get_y() + 1); //MOVE THE SNAKE WHILE THINKING
                    if (simulated_snake_size > 1) { //REFRESH THE SNAKE BODY: TALVEZ TENHA QUE ALTERAR PQ GET_BODY RETORNA O CORPO REAL DA COBRA <----------------------
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::DOWN);//FEED THE SOLUTION DEQUE
                }
                //CASO ELA ESCOLHA IR PARA A ESQUERDA, VIRE PARA A ESQUERDA E ANDE
                else if (possib_dir[0] == Direction::LEFT){
                    current_dir_for_search = Direction::LEFT;
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                //CASO ELA ESCOLHA IR PARA A ESQUERDA, VIRE PARA A DIREITA E ANDE
                else if (possib_dir[0] == Direction::RIGHT){
                    current_dir_for_search = Direction::RIGHT;
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
            }
            //-------------------------------------------------------- CASO A COBRA ESTEJA VIRADA PARA A ESQUERDA -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::LEFT){

                possib_dir.clear();
                //VERIFICA QUAIS POSIÇÕES ESTÃO LIVRES E ARMAZENA EM POSSIB_DIR (VECTOR)
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::LEFT, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::LEFT);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){
                    possib_dir.push_back(Direction::UP);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){
                    possib_dir.push_back(Direction::DOWN);
                }

                //VERIFICA SE A COBRA NÃO ESTÁ SEM SAÍDA
                if (possib_dir.empty()){break;} //<----------------------------------------- ADICIONEI A VERIFICACAO DE MORTE

                //RANDOMIZA A ESCOLHA DA COBRA BURRA
                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                //CASO ELA ESCOLHA SE MANTER INDO LEFT, ANDE
                if (possib_dir[0] == Direction::LEFT){
                    next_step_pos.set_x(next_step_pos.get_x() - 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::LEFT);
                }
                //CASO ELA ESCOLHA IR PARA CIMA, VIRE PARA CIMA E ANDE
                else if (possib_dir[0] == Direction::UP){
                    current_dir_for_search = Direction::UP;
                    next_step_pos.set_y(next_step_pos.get_y() - 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
                //CASO ELA ESCOLHA IR PARA BAIXO, VIRE PARA BAIXO E ANDE
                else if (possib_dir[0] == Direction::DOWN){
                    current_dir_for_search = Direction::DOWN;
                    next_step_pos.set_y(next_step_pos.get_y() + 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
            }
            //-------------------------------------------------------- CASO A COBRA ESTEJA VIRADA PARA A DIREITA -------------------------------------------------------- 
            else if (current_dir_for_search == Direction::RIGHT){

                possib_dir.clear();
                //VERIFICA QUAIS POSIÇÕES ESTÃO LIVRES E ARMAZENA EM POSSIB_DIR (VECTOR)
                if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::RIGHT, simulated_body)){//TALVEZ O GETBODY ESTEJA ERRADO PORQUE RETORNA O CORPO REAL DA COBRA
                    possib_dir.push_back(Direction::RIGHT);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::UP, simulated_body)){
                    possib_dir.push_back(Direction::UP);
                } if (my_player->check_if_next_is_playable(m_current_lvl, current_pos_for_search, Direction::DOWN, simulated_body)){
                    possib_dir.push_back(Direction::DOWN);
                }

                //VERIFICA SE A COBRA NÃO ESTÁ SEM SAÍDA
                if (possib_dir.empty()){break;} //<----------------------------------------- ADICIONEI A VERIFICACAO DE MORTE

                //RANDOMIZA A ESCOLHA DA COBRA BURRA
                std::shuffle(possib_dir.begin(), possib_dir.end(), g);

                //CASO ELA ESCOLHA SE MANTER INDO RIGHT, ANDE
                if (possib_dir[0] == Direction::RIGHT){
                    next_step_pos.set_x(next_step_pos.get_x() + 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::RIGHT);
                }
                //CASO ELA ESCOLHA IR PARA CIMA, VIRE PARA CIMA E ANDE
                else if (possib_dir[0] == Direction::UP){
                    current_dir_for_search = Direction::UP;
                    next_step_pos.set_y(next_step_pos.get_y() - 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::UP);
                }
                //CASO ELA ESCOLHA IR PARA BAIXO, VIRE PARA BAIXO E ANDE
                else if (possib_dir[0] == Direction::DOWN){
                    current_dir_for_search = Direction::DOWN;
                    next_step_pos.set_y(next_step_pos.get_y() + 1);
                    if (simulated_snake_size > 1) {
                        simulated_body.push_front(current_pos_for_search);
                        if (simulated_body.size() > simulated_snake_size) {
                            simulated_body.pop_back(); } }
                    my_player->get_nextdirection().push_back(Direction::DOWN);
                }
            }
            //Refresh the current position of the snake
            current_pos_for_search = next_step_pos;

        }

    }//==================================================================================================================================
    else if (m_current_state == WALKING){
        {std::cout << "\nTAMANHO DO VETOR DE DECISOES: " << my_player->get_nextdirection().size() << std::endl;}

        if (my_player->get_nextdirection().empty()) {
                // Verifica se a cobra está encurralada
                if (my_player->check_if_snake_is_prision(m_current_lvl, sn.get_current_pos(), sn.get_dir(), sn.get_body())) {
                    sn.set_position(m_current_lvl, 'X', sn.get_current_pos());
                    dead = true;
                    std::cout << "\nBATEU! A cobra não tem para onde ir!\n";
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

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

    }//==================================================================================================================================
}

void SnazeSimulation::update(){
    if (m_current_state == START){ m_current_state = READING_INPUT; }
    else if (m_current_state == READING_INPUT){ m_current_state = WAITING_START; }
    else if (m_current_state == WAITING_START){if (std::cin.get() == '\n') {m_current_state = RANDOM_SEARCH;}}//TEMPORÁRIO! Depois tem que fazer o backtracking!
    else if (m_current_state == RANDOM_SEARCH){
        if (dead){ m_current_state = DEAD; }
        else {m_current_state = WALKING; }
    }
    else if (m_current_state == WALKING){
        if (dead){
            m_current_state = DEAD;
        }
        else if (my_player->get_nextdirection().empty()) { m_current_state = FOUND; }

        }
    else if (m_current_state == FOUND){
        if (sn.get_eated() == m_current_lvl.get_food_amount()){
            if (m_levels.empty()){ m_current_state = WON_GAME; }
            else{ m_current_state = READING_INPUT; } // Prepara próximo nível
        }
        else { m_current_state = RANDOM_SEARCH; } // Procura próxima comida
    }
    else if (m_current_state == WON_GAME){ m_current_state = END; }
    else if (m_current_state == DEAD) { m_current_state = END; } //PROVISOTIO
    else if (m_current_state == END){ this->is_over = true; }
}

void SnazeSimulation::render(){
    if (m_current_state == WAITING_START){
        m_current_lvl.print_level(m_current_lvl);
        std::cout << "\nPress enter to start the game!\n";
    }
    else if (m_current_state == RANDOM_SEARCH){ std::cout << "\nThinking...\n"; }
    else if (m_current_state == WALKING){
        std::cout << "Eaten Food: " << sn.get_eated() << ", Current Size: " << sn.get_size() << std::endl;
        m_current_lvl.print_level(m_current_lvl);
    }
    else if (m_current_state == WON_GAME){ std::cout << "\n==============================================\nCONGRATS!!!!!!!!!!!!!!!!!!!!\nYOU WON!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n==============================================\n";}
    else if (m_current_state == DEAD){
        m_current_lvl.print_level(m_current_lvl);
        std::cout << "\n================================\n";
        std::cout << "BATEU! A cobra não tem saída!\n";
        std::cout << "================================\n";
    }
}

//Alterar essa coisa horrorosa aqui em cima depois.

//==================Setters===================
void SnazeSimulation::set_fps(size_t value){ this->m_fps = value; }
void SnazeSimulation::set_levels(std::deque<Level> lvl){ this->m_levels = lvl;}

//==================Getters===================
std::deque<Level> SnazeSimulation::get_levels(){ return this->m_levels; }
Player SnazeSimulation::get_player(){ return *this->my_player; }
Level& SnazeSimulation::get_current_level() { return m_current_lvl; }
Snake SnazeSimulation::get_snake(){return this->sn;}