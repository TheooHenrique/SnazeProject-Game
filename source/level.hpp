#ifndef LEVEL
#define LEVEL
#include <cstddef>
#include <string>
#include <vector>
#include "positiondirection.hpp"

/**
 * @file level.hpp
 * @brief Defines the Level class, which represents a single game maze.
 */

/**
 * @class Level
 * @brief Represents a single game level, including its layout, dimensions, and game elements.
 *
 * This class stores the maze grid, the locations of the snake's spawn point and food,
 * and manages level-specific properties like the amount of food to be eaten.
 */
class Level{
    private:
    
    /// @brief The width of the level grid (number of columns).
    size_t m_width;
    /// @brief The height of the level grid (number of rows).
    size_t m_length;
    /// @brief A vector of strings representing the 2D layout of the maze.
    std::vector<std::string> m_level_maze;
    
    /// @brief The total number of food pellets to be eaten in this level.
    size_t food_amount = 10;
    /// @brief The snake's starting position for this level.
    Position m_spawnpoint;
    /// @brief The current coordinates of the food pellet.
    Position m_food_coords;

    public:
    /// Default constructor
    Level(){ }

    /**
     * @brief Constructs a Level with specified parameters.
     * @param x The width of the level.
     * @param y The height of the level.
     * @param spawn The spawn point for the snake.
     * @param maze A string representation of the maze (not currently used in this constructor).
     */
    Level(size_t x, size_t y, Position spawn, std::string maze){
        this->m_length = y;
        this->m_width = x;
        this->m_spawnpoint = spawn;
    }

    public:
    // Methods
    /**
     * @brief Prints the raw level layout to the console (legacy render method).
     * @param lvl The Level object to print.
     */
    void print_level(Level);

    /**
     * @brief Places the food character 'f' at a specified position in the maze data.
     * @param pos The position where the food should be placed.
     */
    void place_food_in_maze(Position&);

    /**
     * @brief Finds a valid random empty position and sets it as the new food coordinate.
     */
    void generate_food();

    /**
     * @brief Checks if there is a food character 'f' anywhere in the maze.
     * @return True if food is present, false otherwise.
     */
    bool there_is_food_at_maze();

    // Setters
    /**
     * @brief Sets the width of the level.
     * @param width The new width.
     */
    void set_width(size_t width);

    /**
     * @brief Sets the height (length) of the level.
     * @param len The new height.
     */
    void set_length(size_t len);

    /**
     * @brief Sets the maze layout.
     * @param maze A vector of strings representing the new maze.
     */
    void set_maze(std::vector<std::string> maze);

    /**
     * @brief Sets the total amount of food to be eaten in the level.
     * @param amount The new food amount.
     */
    void set_food_amount(size_t amount);

    /**
     * @brief Sets the snake's spawn point.
     * @param spawn The new spawn position.
     */
    void set_spawnpoint(Position spawn);

    /**
     * @brief Sets a character at a specific position in the maze grid.
     * @param pos The position to modify.
     * @param c The character to place.
     */
    void set_position(Position pos, char c);


    /**
     * @brief Gets the total amount of food to be eaten.
     * @return A reference to the food amount.
     */
    size_t& get_food_amount();

    /**
     * @brief Gets the character at a specific position in a given layout.
     * @param layout The maze layout to check.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The character at the specified position.
     */
    char get_item_pos(std::vector<std::string> layout, size_t x, size_t y);

    /**
     * @brief Gets the maze layout.
     * @return A reference to the vector of strings representing the maze.
     */
    std::vector<std::string>& get_maze();

    /**
     * @brief Gets the snake's spawn point.
     * @return The spawn position.
     */
    Position get_spawnpoint();

    /**
     * @brief Gets the current coordinates of the food.
     * @return A reference to the food position.
     */
    Position& get_food_cords();
    
};

#endif
