#include "level.hpp"
#include <iostream>
#include <random>
#include <ctime>

//Methods
void Level::generate_food(){
    // Initializes the time-based random number generator
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    size_t rows = m_level_maze.size();
    size_t cols = m_width;

    //vector of valid positions to spawn the food
    std::vector<Position> valid_positions;

    for (size_t y{0}; y < rows; ++y) {
        for (size_t x{0}; x < cols; ++x) {
            char cell = get_item_pos(m_level_maze, x, y);

            // Check if the cell is an empty space (not a wall, not an invisible wall)
            if (cell == ' ') {
                // add to the valid positions list
                valid_positions.push_back(Position{x, y});
            }
        }
    }

    // If there are no valid positions, return an invalid position
    if (valid_positions.empty()) {
        std::cerr << "The maze cannot generate any food!";
    }

    std::uniform_int_distribution<size_t> dist(0, valid_positions.size() - 1);
    m_food_coords = valid_positions[dist(rng)];
}

void Level::place_food_in_maze(Position& m_food_cords_for_this_function) {
    size_t x = m_food_cords_for_this_function.get_x();
    size_t y = m_food_cords_for_this_function.get_y();

    if (y < m_level_maze.size() && x < m_level_maze[y].size()) {
        m_level_maze[y][x] = 'f'; //f is for food
    }
}

//renderiza imprimindo todo o labirinto. se funcionar, 'f' estará no local indicado
void Level::print_level(Level lvl){ for (int j{0}; j < lvl.get_maze().size(); ++j){ std::cout << lvl.get_maze()[j] << std::endl; } }


//Setters
void Level::set_width(size_t width){ this->m_width = width; }
void Level::set_length(size_t len){ this->m_length = len; }
void Level::set_food_amount(size_t amount){ this->food_amount = amount; }
void Level::set_spawnpoint(Position spawn){ this->m_spawnpoint = spawn; }


//Getters
std::vector<std::string>& Level::get_maze(){ return this->m_level_maze; }
Position Level::get_spawnpoint(){ return m_spawnpoint; }
char Level::get_item_pos(std::vector<std::string> layout, size_t x, size_t y){ return layout[y][x]; }
Position &Level::get_food_cords(){ return this->m_food_coords; }