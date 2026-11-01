#pragma once
#include <string>
#include <GameMap/LevelConfig.h>

class IncludeJson {
protected:

public:
    static LevelConfig load(std::string filename);
};
