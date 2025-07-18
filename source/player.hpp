#ifndef PLAYER
#define PLAYER
#include "positiondirection.hpp"
#include "level.hpp"
#include <deque>
#include <vector>

/**
 * @file player.hpp
 * @brief Defines the base Player class and its derived AI strategy classes.
 */

/**
 * @class Player
 * @brief An abstract base class representing the snake's AI.
 *
 * This class provides a common interface for different AI implementations (e.g., random, backtracking).
 * It also contains utility methods for collision detection and movement validation.
 */
class Player{
    private:
    /// @brief A queue of positions for a pre-calculated path.
    std::deque<Position> nextpositions;
    /// @brief A queue of directions for a pre-calculated path.
    std::deque<Direction> nextdirection;

    public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Player() = default;

    /**
     * @brief A virtual method to determine the snake's next move.
     * @return The next Direction for the snake to take.
     */
    virtual Direction next_move();

    /**
     * @brief Checks if the next step in a given direction is a valid move.
     * A move is valid if it is not a wall or part of the snake's body.
     * @param lvl The current game level.
     * @param pos The snake's current position.
     * @param dir The direction to check.
     * @param snake_body A deque representing the snake's body segments.
     * @return True if the move is playable, false otherwise.
     */
    bool check_if_next_is_playable(Level lvl, Position pos, Direction dir, std::deque<Position>& snake_body);

    /**
     * @brief Checks if the snake is trapped (no valid moves available).
     * This occurs if all three forward-facing adjacent cells are obstacles.
     * @param lvl The current game level.
     * @param pos The snake's current position.
     * @param dir The snake's current direction.
     * @param snake_body A deque representing the snake's body segments.
     * @return True if the snake is trapped, false otherwise.
     */
    bool check_if_snake_is_prision(Level lvl, Position pos, Direction dir, std::deque<Position>& snake_body);

    /**
     * @brief Checks if a given position is occupied by the snake's body.
     * @param check_pos The position to check.
     * @param snake_body A deque representing the snake's body segments.
     * @return True if the position is part of the snake's body, false otherwise.
     */
    bool is_snake_body( Position& check_pos,  std::deque<Position>& snake_body);

    /**
     * @brief Randomly changes the snake's direction to a perpendicular one.
     * @param dir A reference to the direction to be changed.
     */
    void change_direction(Direction& dir);

    // Getters
    /**
     * @brief Gets the queue of upcoming positions.
     * @return A reference to the deque of positions.
     */
    std::deque<Position>& get_nextpositions();

    /**
     * @brief Gets the queue of upcoming directions.
     * @return A reference to the deque of directions.
     */
    std::deque<Direction>& get_nextdirection();

};

/**
 * @class PlayerRandom
 * @brief A Player AI that moves randomly.
 *
 * This class inherits from Player but its specific logic is not yet implemented.
 */
class PlayerRandom : public Player{
    public:
    /**
     * @brief Default constructor for the Random Player.
     */
    PlayerRandom(){ }

    /**
     * @brief Determines the snake's next move based on a random policy.
     * @return The next Direction.
     */
    Direction next_move() override;
};

/**
 * @class PlayerBacktrack
 * @brief A Player AI that uses a backtracking algorithm to find food.
 *
 * This class inherits from Player but its specific logic is not implemented.
 */
class PlayerBacktrack : public Player{
    public:
    /**
     * @brief Default constructor for the Backtracking Player.
     */
    PlayerBacktrack(){ }

    /**
     * @brief Finds a sequence of directions to the food using backtracking.
     * @return A vector of Directions representing the solution path.
     */
    std::vector<Direction> find_solution();

    /**
     * @brief Checks if a solution path has been found.
     * @return True if a solution exists, false otherwise.
     */
    bool found_solution();

    /**
     * @brief Returns the next move from the pre-calculated solution path.
     * @return The next Direction.
     */
    Direction next_move() override;
};


#endif
