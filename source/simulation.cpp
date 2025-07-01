#include "dictionarys.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include "simulation.hpp"
#include "level.hpp"
//====================Simulation Func========================
void SnazeSimulation::initialize(int argc, char* argv[]){
    for (size_t ct{1}; ct < argc ; ++ct){
        auto it{items_with_their_keys.find(argv[ct])};
        if (it != items_with_their_keys.end()){
            interface selected_option {it->second};
            if (selected_option == HELP){
                //config para mostrar help e encerrar o programa
            }
            //NESSES CASOS, FALTA TRATAR ERRO DE CT + 1 DAR SEGFAULT
            else if(selected_option == FPS){try{set_fps(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at fps option!\n"; }}
            else if (selected_option == FOOD){try{lvl.set_food_amount(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at food option!\n";}}
            else if (selected_option == LIVES){try{lvl.get_snake().set_lives(std::stoi(argv[ct + 1]));} catch(const std::runtime_error& e){std::cerr << "Error: You inserted a invalid type at lives option!\n";}}
            else if (selected_option == PLAYERTYPE){try{} catch(const std::runtime_error& e){ std::cerr << "Error: You inserted a invalid type at player type option!\n";}}
        }
    }
}

bool SnazeSimulation::is_over(){
    return true; //temporary
}

void process_events(){

}

void update(){

}

void render(){

}

