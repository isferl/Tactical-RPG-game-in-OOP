#pragma once
#include <vector>
#include <Robot/Entities.h>
#include <GameMap/GameWorld.h>

class IntelligenceRobots {
public:
    IntelligenceRobots(Entities &robot, GameWorld &world);

    bool main_intelligence();

    bool is_turn_finished() const;

private:
    Entities &robot;
    GameWorld &world;
    bool ability_blocked = false;
    bool turn_finished = false;

    std::vector<std::pair<int, int> > find_entities();

    std::vector<std::pair<int, int> > filter_to_need_entities(std::vector<std::pair<int, int> > entities, bool is_friendly);

    std::pair<int, int> find_healing(std::vector<std::pair<int, int>> entities);

    std::pair<int, int> find_to_attack(std::vector<std::pair<int, int> > entities);

    std::pair<int, int> find_enemy(std::vector<std::pair<int, int> > entities);

    std::pair<int, int> find_way_to_cell(std::pair<int, int> dot, int &cost);

    std::pair<int, int> find_teleport_cell(std::pair<int, int> dot);

    bool move_to_cell(std::pair<int, int> dot, bool use_teleport = true);

    bool try_use_ability(AbilityType type, std::pair<int, int> dot);

    bool can_pass_cell(std::pair<int, int> next, std::pair<int, int> dot);

    bool can_make_first_step(std::pair<int, int> next, std::pair<int, int> dot);

    bool can_teleport_to_cell(std::pair<int, int> dot);

    std::pair<int, int> find_cell_to_safe(std::vector<std::pair<int, int> > entities);

    std::pair<int, int> random_way();

    bool moved(std::pair<int, int>);

};
