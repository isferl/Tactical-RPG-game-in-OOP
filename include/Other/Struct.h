#pragma once
struct CellConfig {
    bool impassable;
    int move_cost;
};

struct RobotTemplateConfig {
    int max_hp;
    int damage;
    int heal;
    int max_stamina;
    int visibility_distance;
    int xp_for_kill;
};

struct RobotConfig {
    std::string templates;
    std::pair<int, int> position;
    int rank;
    int xp;
};

struct FactoryConfig {
    std::pair<int, int> position;
    std::pair<int, int> size;
    int spawn_interval_turns;
    int spawn_limit;
    int spawn_rank;
    std::string spawn_template;
};
