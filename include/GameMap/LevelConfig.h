#pragma once
#include <deque>
#include <list>
#include <map>
#include <string>
#include <Other/Struct.h>

class LevelConfig {
public:
    std::string level_id;
    int stamina_restored_per_turn;
    int width;
    int height;
    std::map<char, CellConfig> cell_types;
    std::deque<std::string> layout;
    std::map<std::string, RobotTemplateConfig> robots_templates;
    std::list<RobotConfig> robots;
    std::list<FactoryConfig> factories;

    LevelConfig(
        std::string level_id,
        int stamina_restored_per_turn,
        int width,
        int height,
        std::map<char, CellConfig> cell_types,
        std::deque<std::string> layout,
        std::map<std::string, RobotTemplateConfig> robots_templates,
        std::list<RobotConfig> robots,
        std::list<FactoryConfig> factories
    );
};
