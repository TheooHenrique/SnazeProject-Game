#include "dictionaries.hpp"

/**
 * @file dictionaries.cpp
 * @brief Implements the initialization for the command-line argument dictionary.
 */

/**
 * @brief Populates the `items_with_their_keys` map.
 *
 * This method maps the string representation of command-line arguments
 * (e.g., "--help") to their corresponding `interface` enum values. This table
 * is used by the simulation's `initialize` method to parse user input.
 */
void Dictios::initialize_table(){
    items_with_their_keys ["--help"] = HELP; 
    items_with_their_keys ["--fps"] = FPS; 
    items_with_their_keys ["--lives"] = LIVES; 
    items_with_their_keys ["--food"] = FOOD; 
    items_with_their_keys ["--playertype"] = PLAYERTYPE; 

}
