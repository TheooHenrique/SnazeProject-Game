#ifndef DICT
#define DICT
#include <string>
#include <unordered_map>

struct Dictios{

    enum interface : size_t{
        HELP,
        FPS,
        FOOD,
        LIVES,
        PLAYERTYPE
    };
    void initialize_table();
    std::unordered_map<std::string, size_t> items_with_their_keys;
    
};



#endif