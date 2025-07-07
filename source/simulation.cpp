#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "dictionarys.hpp"
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
                if (this->m_levels.size() > 0){this->m_current_lvl = m_levels[0];}
                else{std::cerr << "Error! Your inputed level file has no valid level!\n"; break;}
            } else{ std::cerr << "Error! You inputed two or more .dat files!\n"; break;}
        }
        
        //Capturing the configurations
        auto it{items_with_their_keys.find(argv[ct])};
        if (it != items_with_their_keys.end()){
            interface selected_option {it->second};
            if (selected_option == HELP){usage(); exit(0);}
            if (ct + 1 < argc){
                if (selected_option == FPS){try{set_fps(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at fps option!\n"; }}
                if (selected_option == FOOD){try{m_current_lvl.set_food_amount(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at food option!\n";}}
                if (selected_option == LIVES){try{aux = std::stoi(argv[ct + 1]);} catch(const std::runtime_error& e){std::cerr << "Error: You inserted a invalid type at lives option!\n";}}
                if (selected_option == PLAYERTYPE){try{
                        if (strcmp(argv[ct+1], "backtracking") == 0){
                            if (aux != -1){ my_player->get_snake().set_lives(aux);} //Tem que alterar isso aqui. Tem que setar o player como backtrack player
                        }
                        else if(strcmp(argv[ct+1], "random") == 0){
                            if (aux != -1){ my_player->get_snake().set_lives(aux) ;} //Tem que alterar isso aqui. Tem que setar o player como random player
                        } else{
                            std::cout << "WARNING: You inserted a invalid type at player type option! Starting with backtracking player by default.\n";
                            if (aux != -1){ my_player->get_snake().set_lives(aux);}
                        }
                } catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at player type option!\n";}}
            }
            else {std::cerr << "Error: You don't inserted some of the config parameters!\n";}
        }
    }
}

void SnazeSimulation::process_events(){
    if (m_current_state == RANDOM_SEARCH){
        this->my_player->get_snake().set_position(m_current_lvl, 'c', );
    }
}

void SnazeSimulation::update(){
    if (m_current_state == START){ m_current_state = WAITING_START; }
    else if (m_current_state == WAITING_START){if (std::cin.get() == '\n') {m_current_state = RANDOM_SEARCH;}}//TEMPORÁRIO! Depois tem que fazer o backtracking!
    else if (m_current_state == RANDOM_SEARCH){}
}

void SnazeSimulation::render(){
    if (m_current_state == WAITING_START){
        m_current_lvl.print_level(m_current_lvl);
        std::cout << "\nPress enter to start the game!\n";
    }
}

bool SnazeSimulation::is_over(){return true; /*temporary*/}
void SnazeSimulation::set_fps(size_t value){ this->m_fps = value; }
void SnazeSimulation::set_levels(std::vector<Level> lvl){ this->m_levels = lvl;}
std::vector<Level> SnazeSimulation::get_levels(){ return this->m_levels; }
