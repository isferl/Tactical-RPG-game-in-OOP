#include <GameMap/LevelConfig.h>


LevelConfig::LevelConfig(std::string level_id, int stamina_restored_per_turn, int width, int height,
                         std::map<char, CellConfig> cell_types, std::deque<std::string> layout,
                         std::map<std::string, RobotTemplateConfig> robots_templates, std::list<RobotConfig> robots,
                         std::list<FactoryConfig> factories) {
    this->level_id = level_id;
    this->stamina_restored_per_turn = stamina_restored_per_turn;
    this->width = width;
    this->height = height;
    this->cell_types = cell_types;
    this->layout = layout;
    this->robots_templates = robots_templates;
    this->robots = robots;
    this->factories = factories;
}
