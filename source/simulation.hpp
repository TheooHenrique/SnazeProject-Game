#ifndef SIMULATION
#define SIMULATION

#include "level.hpp"
#include "player.hpp"
#include "positiondirection.hpp"
#include "reader.hpp"
#include <cstddef>
#include <cstdint>
#include "snake.hpp"

/**
 * @file simulation.hpp
 * @brief Defines the SnazeSimulation class, the main engine for the game.
 */

/**
 * @class SnazeSimulation
 * @brief Manages the entire game flow, state, and entities.
 *
 * This class is a singleton that contains the main game loop. It handles
 * everything from parsing command-line arguments to processing game events,
 * updating game state, and rendering the output to the console.
 */
class SnazeSimulation{
    private:
        /**
         * @brief Private constructor to enforce the singleton pattern.
         */
        SnazeSimulation(){
            m_current_state = START;
        }

        /**
         * @enum m_possible_states
         * @brief Defines the possible states of the game's state machine.
         */
        enum m_possible_states : uint8_t{
            START,              //!< Initial state before anything happens.
            READING_INPUT,      //!< State for reading and parsing level files.
            INVALID_INPUT,      //!< State for handling invalid input.
            WAITING_START,      //!< Paused state, waiting for user input to begin/continue.
            BACKTRACK_SEARCH,   //!< State for the backtracking AI to find a path.
            RANDOM_SEARCH,      //!< State for the random AI to find a path.
            WALKING,            //!< Active gameplay state where the snake moves.
            FOUND,              //!< State after the snake has eaten a food pellet.
            DEAD,               //!< State when the snake has lost all its lives.
            WON_ROUND,          //!< State after completing a single level.
            WON_GAME,           //!< State after completing all levels.
            LOST,               //!< General game over state.
            END                 //!< Final state before the program exits.
        };

        /// @brief A reference to the singleton Snake object.
        Snake &sn = Snake::get_instance();
        /// @brief The current state of the game's finite state machine.
        size_t m_current_state;
        /// @brief Frame rate delay in milliseconds.
        size_t m_fps{100};
        /// @brief The currently active Level object.
        Level m_current_lvl;
        /// @brief A pointer to the current Player (AI) object.
        Player* my_player;
        /// @brief A deque containing all levels loaded from the input file.
        std::deque<Level> m_levels;
        /// @brief An instance of the Reader class for parsing files.
        Reader read;
        /// @brief The character representing the snake's head (e.g., '^', 'v', '<', '>').
        char m_head;
        /// @brief A flag indicating if the snake has crashed in the current turn.
        bool dead;
        /// @brief Temporary storage for the food count from command-line arguments.
        size_t aux_food;
        /// @brief Temporary storage for the FPS from command-line arguments.
        size_t aux_fps;
        /// @brief Temporary storage for the lives count from command-line arguments.
        size_t aux_lives;
        /// @brief A flag used by the AI to indicate if a path to the food was not found.
        bool no_path;
        /// @brief A temporary position used by the AI during pathfinding.
        Position current_pos_for_search;

    public:
        /// @brief A flag that controls the main game loop. Set to true to exit.
        bool is_over = false;

        // Methods:
        /**
         * @brief Prints the command-line usage instructions to the console.
         */
        void usage();

        /**
         * @brief Initializes the simulation by parsing command-line arguments and loading levels.
         * @param argc The argument count from main().
         * @param argv The argument vector from main().
         */
        void initialize(int argc, char*[]);

        /**
         * @brief Sets a random initial direction for the snake.
         */
        void startdirection();

        /**
         * @brief Processes all game logic for the current state.
         * This includes AI pathfinding, snake movement, collision detection, and state resets.
         */
        void process_events();

        /**
         * @brief Updates the game state by transitioning from the current state to the next.
         * This function acts as the controller for the finite state machine.
         */
        void update();

        /**
         * @brief Renders the current state of the game to the console.
         */
        void render();

        // Setters
        void set_fps(size_t);
        void set_levels(std::deque<Level>);

        // Getters
        Snake get_snake();
        Player get_player();
        Level& get_current_level();
        std::deque<Level> get_levels();

        /**
         * @brief Provides access to the single instance of the SnazeSimulation class.
         * @return A reference to the singleton SnazeSimulation object.
         */
        static SnazeSimulation& get_instance(){
            static SnazeSimulation sg;
            return sg;
        }
};

#endif
