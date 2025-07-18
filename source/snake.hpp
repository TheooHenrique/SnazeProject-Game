#ifndef SNAKE
#define SNAKE

#include "level.hpp"
#include "positiondirection.hpp"
#include <cstddef>
#include <deque>

/**
 * @file snake.hpp
 * @brief Defines the Snake class, which represents the player's snake.
 */

/**
 * @class Snake
 * @brief Represents the snake in the game. It is implemented as a singleton.
 *
 * This class manages all state related to the snake, including its position,
 * size, direction, body segments, lives, and score.
 */
class Snake{
    private:
        /// @brief The snake's current direction of movement.
        Direction m_current_dir;
        /// @brief The current size (length) of the snake.
        size_t m_current_size{1};
        /// @brief The number of food pellets eaten so far.
        size_t m_eaten_food{0};
        /// @brief The number of lives remaining.
        size_t m_lives{5};
        /// @brief The number of lives the snake started with.
        size_t m_initial_lives{5};
        /// @brief The player's current score.
        size_t m_current_score;
        /// @brief A deque of positions representing the snake's body segments.
        std::deque<Position> m_snake_body;
        /// @brief The current position of the snake's head.
        Position m_current_pos;
        /// @brief An auxiliary position variable (purpose to be defined).
        Position m_current_pos2;

        /**
         * @brief Private constructor to enforce the singleton pattern.
         */
        Snake(){
            m_current_score = 0;
            m_eaten_food = 0;
        }

    public:
        /**
         * @brief Provides access to the single instance of the Snake class.
         * @return A reference to the singleton Snake object.
         */
        static Snake& get_instance(){
            static Snake sn;
            return sn;
        }

        // Methods
        /**
         * @brief Adds a new segment to the front of the snake's body.
         * @param pos The position of the new segment.
         */
        void add_segment(const Position& pos);

        /**
         * @brief Removes the last segment from the snake's body.
         */
        void remove_last_segment();

        /**
         * @brief Resets the snake's body, usually for a new level or respawn.
         * @param head_pos The new position of the snake's head.
         */
        void initialize_body(const Position& head_pos);

        // Getters
        Position get_current_pos();
        Position get_current_pos2();
        Direction& get_dir();
        size_t get_size();
        size_t get_eated();
        size_t get_lives();
        size_t get_initial_lives();
        size_t get_score();
        std::deque<Position>& get_body();

        // Setters
        void set_body(std::deque<Position>);
        void set_current_pos(Position);
        void set_current_pos2(Position);
        void set_dir(size_t);
        void set_size(size_t);
        void set_eated(size_t);
        void set_lives(size_t);
        void set_initial_lives(size_t);
        void set_score(size_t);
        void set_position(Level&, char, Position);
};
#endif
