#ifndef DICT
#define DICT

#include <string>
#include <unordered_map>

enum interface : size_t{
    HELP,
    FPS,
    FOOD,
    LIVES,
    PLAYERTYPE
};

std::unordered_map<std::string, size_t> items_with_their_keys{
    {"--help", HELP},
    {"--fps", FPS},
    {"--lives", LIVES},
    {"--food", FOOD},
    {"--playertype", PLAYERTYPE}
};

#endif