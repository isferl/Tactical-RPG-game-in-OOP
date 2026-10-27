#include <GameMap/IncludeJson.h>
#include <GameMap/LevelConfig.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


LevelConfig IncludeJson::load(const std::string filename) const {
    std::ifstream input_file("../../map/" + filename);
    nlohmann::json loaded_json;
    input_file >> loaded_json;
    std::string level_id = loaded_json["level_id"];
    int stamina_restored_per_turn = loaded_json["rules"]["stamina_restored_per_turn"];
    int width = loaded_json["board"]["width"];
    int height = loaded_json["board"]["height"];
    std::map<char, CellConfig> cell_types;
    for (auto &item: loaded_json["board"]["cell_types"].items()) {
        CellConfig cell_config;
        cell_config.impassable = item.value()["impassable"];
        if (!cell_config.impassable)
            cell_config.move_cost = item.value()["move_cost"];
        else
            cell_config.move_cost = 0;
        cell_types[item.key()[0]] = cell_config;
    }
    std::deque<std::string> layout;
    for (auto &item: loaded_json["board"]["layout"]) {
        layout.push_back(item);
    }
    std::map<std::string, RobotTemplateConfig> robots_templates;
    for (auto &item: loaded_json["board"]["robot_templates"].items()) {
        RobotTemplateConfig config;
        config.damage = item.value()["stats"]["damage"];
        config.heal = item.value()["stats"]["heal"];
        config.max_hp = item.value()["stats"]["max_hp"];
        config.max_stamina = item.value()["stats"]["max_stamina"];
        config.visibility_distance = item.value()["stats"]["visibility_distance"];
        config.xp_for_kill = item.value()["stats"]["xp_for_kill"];
        robots_templates[item.key()] = config;
    }
    std::list<RobotConfig> robots;
    for (auto &item: loaded_json["board"]["robots"].items()) {
        RobotConfig config;
        std::pair<int, int> position;
        position.first = item.value()["position"]["x"];
        position.second = item.value()["position"]["y"];
        config.position = position;
        config.rank = item.value()["rank"];
        config.templates = item.value()["template"];
        config.xp = item.value()["xp"];
        robots.push_back(config);
    }
    std::list<FactoryConfig> factories;
    for (auto &item: loaded_json["board"]["factories"].items()) {
        FactoryConfig config;
        std::string spawn_template;
        std::pair<int, int> position;
        position.first = item.value()["position"]["x"];
        position.second = item.value()["position"]["y"];
        config.position = position;
        std::pair<int, int> size;
        size.first = item.value()["size"]["width"];
        size.second = item.value()["size"]["height"];
        config.size = size;
        config.spawn_interval_turns = item.value()["spawn_interval_turns"];
        config.spawn_limit = item.value()["spawn_limit"];
        config.spawn_rank = item.value()["spawn_rank"];
        factories.push_back(config);
    }
    return LevelConfig(
        level_id,
        stamina_restored_per_turn,
        width,
        height,
        cell_types,
        layout,
        robots_templates,
        robots,
        factories
    );
}
