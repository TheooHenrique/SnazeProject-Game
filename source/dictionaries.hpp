#ifndef DICT
#define DICT
#include <string>
#include <unordered_map>

/**
 * @file dictionaries.hpp
 * @brief Defines the Dictios struct used for command-line argument parsing.
 */

/**
 * @struct Dictios
 * @brief A utility structure to map command-line argument strings to enum values.
 *
 * This struct helps in converting string arguments like "--help" into a processable
 * enum type, simplifying the argument parsing logic in the main simulation.
 */
struct Dictios{

    /**
     * @enum interface
     * @brief Represents the possible command-line options.
     */
    enum interface : size_t{
        HELP,       //!< The --help option.
        FPS,        //!< The --fps option.
        FOOD,       //!< The --food option.
        LIVES,      //!< The --lives option.
        PLAYERTYPE  //!< The --playertype option.
    };

    /**
     * @brief Initializes the map to associate string arguments with their corresponding enum values.
     */
    void initialize_table();

    /// @brief An unordered map to store the command-line options and their enum keys.
    std::unordered_map<std::string, size_t> items_with_their_keys;
    
};



#endif
