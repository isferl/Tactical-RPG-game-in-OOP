#include <Robot/FactoryRobot.h>
#include <Other/Constants.h>

RobotFactory::RobotFactory(int x, int y, int spawn_interval, int count_to_spawn) {
    position_x = x;
    position_y = y;
    this->spawn_interval = spawn_interval;
    this->count_to_spawn = count_to_spawn;
}

int RobotFactory::get_position_x() const {
    return position_x;
}

int RobotFactory::get_position_y() const {
    return position_y;
}

int RobotFactory::get_spawn_interval() const {
    return spawn_interval;
}

int RobotFactory::get_turns_counter() const {
    return turns_counter;
}

bool RobotFactory::get_statis_live() const {
    return is_alive;
}

bool RobotFactory::should_spawn() const {
    return is_alive && turns_counter > 0 && (turns_counter % spawn_interval == 0) && count_to_spawn;
}

void RobotFactory::tick() {
    ++turns_counter;
}

bool RobotFactory::try_spawn_enemy(Board &board, FullMap &map, std::list<Robot> &enemies) {
    std::list<std::pair<int, int> > candidates;

    for (int x = position_x; x < position_x + FACTORY_X; ++x)
        candidates.emplace_back(x, position_y - 1);
    for (int x = position_x; x < position_x + FACTORY_X; ++x)
        candidates.emplace_back(x, position_y + FACTORY_Y);
    for (int y = position_y; y < position_y + FACTORY_Y; ++y)
        candidates.emplace_back(position_x - 1, y);
    for (int y = position_y; y < position_y + FACTORY_Y; ++y)
        candidates.emplace_back(position_x + FACTORY_X, y);

    for (auto &[sx, sy]: candidates) {
        if (sx < 0 || sy < 0 ||
            sy >= (map.get_map().size()) ||
            sx >= (map.get_map()[sy].size()))
            continue;

        if (map.get_map_in_xy(sx, sy) == 0) {
            enemies.emplace_back(HEAL, 10, MAX_HP, DAMAGE, MAX_STAMINA, -2, sx, sy, false);
            --count_to_spawn;
            board.get_field()[sy][sx].set_type_cell(-2, map, sx, sy);
            board.get_field()[sy][sx].set_robot(&enemies.back());
            return true;
        }
    }
    return false;
}
