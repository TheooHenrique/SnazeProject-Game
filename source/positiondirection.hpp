#ifndef posdic
#define posdic

#include <cstddef>

/**
 * @file positiondirection.hpp
 * @brief Defines the Position class and Direction struct for 2D coordinates and movement.
 */

/**
 * @class Position
 * @brief Represents a 2D coordinate point (x, y) on the game board.
 */
class Position{
    private:
    /// @brief The x-coordinate (column).
    size_t m_x;
    /// @brief The y-coordinate (row).
    size_t m_y;

    public:
    /**
     * @brief Default constructor. Initializes position to (0, 0) implicitly.
     */
    Position(){ }

    /**
     * @brief Constructor to initialize a Position with specific coordinates.
     * @param x The initial x-coordinate.
     * @param y The initial y-coordinate.
     */
    Position(size_t x, size_t y){ m_x = x; m_y = y; }

    /**
     * @brief Equality comparison operator.
     * @param other The Position to compare against.
     * @return True if both x and y coordinates are the same, false otherwise.
     */
    bool operator==(const Position& other) const {
        return m_x == other.m_x && m_y == other.m_y;
    }

    /**
     * @brief Inequality comparison operator.
     * @param other The Position to compare against.
     * @return True if either x or y coordinates are different, false otherwise.
     */
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    // Setters
    /**
     * @brief Sets the y-coordinate.
     * @param y The new y-coordinate.
     */
    void set_y(size_t y);

    /**
     * @brief Sets the x-coordinate.
     * @param x The new x-coordinate.
     */
    void set_x(size_t x);

    // Getters
    /**
     * @brief Gets the x-coordinate.
     * @return The current x-coordinate.
     */
    size_t get_x();

    /**
     * @brief Gets the y-coordinate.
     * @return The current y-coordinate.
     */
    size_t get_y();
    
};

/**
 * @struct Direction
 * @brief Represents a movement direction.
 */
struct Direction{
    public:

    /**
     * @brief Default constructor.
     */
    Direction(){};

    /**
     * @brief Constructor to initialize with a specific direction value.
     * @param x The numeric value of the direction (from the enum).
     */
    Direction(size_t x){m_current_dir = x;};

    /// @brief The current direction, represented as an index from the `directions` enum.
    size_t m_current_dir;

    /**
     * @enum directions
     * @brief Enumerates the possible movement directions.
     */
    enum directions : size_t{
        UP = 0, //!< Represents the up direction.
        DOWN,   //!< Represents the down direction.
        LEFT,   //!< Represents the left direction.
        RIGHT   //!< Represents the right direction.
    };

    public:
    /**
     * @brief Equality comparison operator.
     * @param other The Direction to compare against.
     * @return True if the direction values are the same, false otherwise.
     */
    bool operator==(const Direction& other){ return (this->m_current_dir == other.m_current_dir); }

    // Setters
    /**
     * @brief Sets the current direction.
     * @param dir The new direction value.
     */
    void set_dir(size_t dir);

    // Getters
    /**
     * @brief Gets the current direction.
     * @return The current direction value.
     */
    size_t get_dir();
};

#endif
