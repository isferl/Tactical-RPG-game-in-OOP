#pragma once
#include <string>
#include <GameMap/LevelConfig.h>

class IncludeJson {
protected:

public:
    LevelConfig load(const std::string filename) const;
};
