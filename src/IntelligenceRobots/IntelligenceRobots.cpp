#include <IntelligenceRobots/IntelligenceRobots.h>
#include <GameProcess/Moved.h>
#include <Other/NeedFunction.h>
#include <algorithm>

IntelligenceRobots::IntelligenceRobots(Entities &robot, GameWorld &world) : robot(robot), world(world) {
}

bool IntelligenceRobots::main_intelligence() {
    if (turn_finished || !robot.get_statis_live() || robot.get_stamina() <= 0)
        return false;

    std::vector<std::pair<int, int> > entities = find_entities();
    std::vector<std::pair<int, int> > enemies = filter_to_need_entities(entities, !robot.get_is_friend());
    if (robot.get_hp() <= robot.get_max_hp() * 4 / 10) {
        if (try_use_ability(AbilityType::Heal, {0, 0}))
            return true;

        std::pair<int, int> dot = find_healing(filter_to_need_entities(entities, robot.get_is_friend()));
        if (dot != std::pair<int, int>{0, 0} && move_to_cell(dot))
            return true;

        dot = find_cell_to_safe(enemies);
        if (dot != std::pair<int, int>{0, 0}) {
            std::pair<int, int> start = {robot.get_position_on_game_x(), robot.get_position_on_game_y()};
            if (try_use_ability(AbilityType::Teleports, dot)) {
                if (robot.get_position_on_game_x() != start.first || robot.get_position_on_game_y() != start.second)
                    turn_finished = true;
                return true;
            }
        }
    }

    std::pair<int, int> dot = find_to_attack(enemies);
    if (dot != std::pair<int, int>{0, 0} && moved(dot))
        return true;

    dot = find_enemy(enemies);
    if (dot != std::pair<int, int>{0, 0}) {
        int dist = NeedFunction::distance(robot.get_position_on_game_x(), robot.get_position_on_game_y(),
                                          dot.first, dot.second);
        if (move_to_cell(dot, dist >= (TELEPORT_RADIUS - 1)))
            return true;
    }

    dot = random_way();
    if (dot != std::pair<int, int>{0, 0} && moved(dot))
        return true;
    turn_finished = true;
    return false;
}

bool IntelligenceRobots::is_turn_finished() const {
    return turn_finished;
}

std::vector<std::pair<int, int> > IntelligenceRobots::find_entities() {
    std::vector<std::pair<int, int> > entities;
    int xr = robot.get_position_on_game_x(), yr = robot.get_position_on_game_y(), vision = robot.
            get_visibility_distance();
    for (int x = std::max(1, xr - vision); x <= std::min(world.get_board().get_width(), xr + vision); ++x)
        for (int y = std::max(1, yr - vision); y <= std::min(world.get_board().get_height(), yr + vision); ++y) {
            Robot *entity = world.get_board().get_square(x, y).get_robot();
            if (NeedFunction::distance(x, y, xr, yr) <= vision && entity != nullptr && entity != &robot &&
                entity->get_statis_live())
                entities.emplace_back(x, y);
        }
    return entities;
}

std::vector<std::pair<int, int> > IntelligenceRobots::filter_to_need_entities(
    std::vector<std::pair<int, int> > entities, bool is_friendly) {
    std::vector<std::pair<int, int> > requiring_entities;
    for (std::pair<int, int> el: entities) {
        Robot *entity = world.get_board().get_square(el.first, el.second).get_robot();
        if (entity != nullptr && entity->get_statis_live() && entity->get_is_friend() == is_friendly)
            requiring_entities.emplace_back(el);
    }
    return requiring_entities;
}

std::pair<int, int> IntelligenceRobots::find_healing(std::vector<std::pair<int, int> > entities) {
    std::vector<std::pair<int, int> > requiring_entities;
    for (std::pair<int, int> el: entities) {
        Robot *entity = world.get_board().get_square(el.first, el.second).get_robot();
        if (entity != nullptr && entity != &robot && entity->get_statis_live() &&
            entity->get_is_friend() == robot.get_is_friend() && entity->get_is_heal() && entity->get_heal() > 0)
            requiring_entities.emplace_back(el);
    }
    if (requiring_entities.size() == 0)
        return {0, 0};
    int min_dist = 100000;
    std::pair<int, int> requiring_dot = {0, 0};
    for (std::pair<int, int> el: requiring_entities) {
        int dist = NeedFunction::distance(robot.get_position_on_game_x(), robot.get_position_on_game_y(), el.first,
                                          el.second);
        if (dist < min_dist) {
            int cost;
            std::pair<int, int> next = find_way_to_cell(el, cost);
            if (next.first == 0 && next.second == 0) {
                std::pair<int, int> teleport = find_teleport_cell(el);
                if (teleport.first == 0 && teleport.second == 0)
                    continue;
            }
            min_dist = dist;
            requiring_dot = el;
        }
    }
    return requiring_dot;
}

std::pair<int, int> IntelligenceRobots::find_to_attack(std::vector<std::pair<int, int> > entities) {
    int xr = robot.get_position_on_game_x(), yr = robot.get_position_on_game_y();
    for (std::pair<int, int> el: entities)
        if (NeedFunction::distance(xr, yr, el.first, el.second) == 1 &&
            can_pass_cell(el, el) && can_make_first_step(el, el))
            return el;
    return {0, 0};
}

std::pair<int, int> IntelligenceRobots::find_enemy(std::vector<std::pair<int, int> > entities) {
    int xr = robot.get_position_on_game_x(), yr = robot.get_position_on_game_y();
    int min_dist = 1000000;
    std::pair<int, int> requiring_dot = {0, 0};
    for (std::pair<int, int> el: entities) {
        int dist = NeedFunction::distance(xr, yr, el.first, el.second);
        if (dist >= min_dist)
            continue;
        int cost;
        std::pair<int, int> next = find_way_to_cell(el, cost);
        if (next == std::pair<int, int>{0, 0}) {
            if (dist < 4 || find_teleport_cell(el) == std::pair<int, int>{0, 0})
                continue;
        }
        min_dist = dist;
        requiring_dot = el;
    }
    return requiring_dot;
}

std::pair<int, int> IntelligenceRobots::find_way_to_cell(std::pair<int, int> dot, int &cost) {
    int width = world.get_board().get_width(), height = world.get_board().get_height();
    std::pair<int, int> start = {robot.get_position_on_game_x(), robot.get_position_on_game_y()};
    cost = 1000000;
    if (dot == start || !can_pass_cell(dot, dot))
        return {0, 0};

    std::vector<std::vector<int> > energy(height + 2, std::vector<int>(width + 2, cost));
    std::vector<std::vector<std::pair<int, int> > > first_step(
        height + 2, std::vector<std::pair<int, int> >(width + 2, {0, 0}));
    std::vector<std::pair<int, int> > cells;
    cells.push_back(start);
    energy[start.second][start.first] = 0;
    first_step[start.second][start.first] = start;
    std::pair<int, int> directions[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!cells.empty()) {
        int min_index = 0;
        for (int i = 1; i < static_cast<int>(cells.size()); ++i)
            if (energy[cells[i].second][cells[i].first] < energy[cells[min_index].second][cells[min_index].first])
                min_index = i;
        std::pair<int, int> current = cells[min_index];
        cells.erase(cells.begin() + min_index);
        if (current == dot) {
            cost = energy[current.second][current.first];
            return first_step[current.second][current.first];
        }
        for (std::pair<int, int> direction: directions) {
            std::pair<int, int> next = {current.first + direction.first, current.second + direction.second};
            if (!can_pass_cell(next, dot) || (current == start && !can_make_first_step(next, dot)))
                continue;
            int next_cost = energy[current.second][current.first] + world.get_board().get_square(
                                next.first, next.second).get_cost_cell();
            if (next_cost >= energy[next.second][next.first])
                continue;
            energy[next.second][next.first] = next_cost;
            if (current == start)
                first_step[next.second][next.first] = next;
            else
                first_step[next.second][next.first] = first_step[current.second][current.first];
            cells.push_back(next);
        }
    }
    return {0, 0};
}

std::pair<int, int> IntelligenceRobots::find_teleport_cell(std::pair<int, int> dot) {
    if (ability_blocked || robot.get_ability_type() != AbilityType::Teleports || !robot.get_teleports().is_ready() || !
        can_pass_cell(dot, dot))
        return {0, 0};
    int interaction_cost = world.get_board().get_square(dot.first, dot.second).get_cost_cell();
    if (robot.get_stamina() < robot.get_teleports().get_energy_cost() + interaction_cost)
        return {0, 0};

    int xr = robot.get_position_on_game_x(), yr = robot.get_position_on_game_y();
    int min_dist = 100000;
    std::pair<int, int> requiring_dot = {0, 0};
    std::pair<int, int> directions[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (std::pair<int, int> direction: directions) {
        int x = dot.first + direction.first, y = dot.second + direction.second;
        if (!can_teleport_to_cell({x, y}))
            continue;
        int dist = NeedFunction::distance(xr, yr, x, y);
        if (dist < min_dist) {
            min_dist = dist;
            requiring_dot = {x, y};
        }
    }
    return requiring_dot;
}

bool IntelligenceRobots::move_to_cell(std::pair<int, int> dot, bool use_teleport) {
    int cost;
    std::pair<int, int> next = find_way_to_cell(dot, cost);
    std::pair<int, int> teleport = {0, 0};
    if (use_teleport)
        teleport = find_teleport_cell(dot);
    if (teleport.first != 0 || teleport.second != 0) {
        int teleport_cost = robot.get_teleports().get_energy_cost() + world.get_board().get_square(
                                dot.first, dot.second).get_cost_cell();
        if (teleport_cost < cost && try_use_ability(AbilityType::Teleports, teleport))
            return true;
    }
    if (next.first == 0 && next.second == 0)
        return false;
    return moved(next);
}

bool IntelligenceRobots::try_use_ability(AbilityType type, std::pair<int, int> dot) {
    if (ability_blocked || robot.get_ability_type() != type)
        return false;
    Ability &ability = *robot.get_ability().at(type);
    if (!ability.is_ready() || !robot.can_spend_stamina(ability.get_energy_cost()))
        return false;
    int stamina_before = robot.get_stamina();
    if (robot.get_overload().use_effect(robot, ability.get_energy_cost()))
        return ability.use_ability(robot, world, dot);
    ability_blocked = true;
    return robot.get_stamina() != stamina_before;
}

bool IntelligenceRobots::can_pass_cell(std::pair<int, int> next, std::pair<int, int> dot) {
    if (next.first < 1 || next.second < 1 || next.first > world.get_board().get_width() ||
        next.second > world.get_board().get_height())
        return false;
    Square &cell = world.get_board().get_square(next.first, next.second);
    if (cell.get_impassable() || cell.get_motionless() || (cell.get_type() != CellType::EmptyType && next != dot))
        return false;
    return cell.get_cost_cell() >= 0 && cell.get_cost_cell() <= robot.get_max_stamina();
}

bool IntelligenceRobots::can_make_first_step(std::pair<int, int> next, std::pair<int, int> dot) {
    if (!robot.can_spend_stamina(world.get_board().get_square(next.first, next.second).get_cost_cell()))
        return false;
    return next == dot || robot.get_slowdown().is_finished();
}

bool IntelligenceRobots::can_teleport_to_cell(std::pair<int, int> dot) {
    if (dot.first < 1 || dot.second < 1 || dot.first > world.get_board().get_width() ||
        dot.second > world.get_board().get_height())
        return false;
    Square &cell = world.get_board().get_square(dot.first, dot.second);
    if (cell.get_type() != CellType::EmptyType || cell.get_robot() != nullptr || cell.get_impassable() ||
        cell.get_motionless())
        return false;
    return NeedFunction::distance(robot.get_position_on_game_x(), robot.get_position_on_game_y(),
                                  dot.first, dot.second) <= robot.get_teleports().get_radius();
}

std::pair<int, int> IntelligenceRobots::find_cell_to_safe(std::vector<std::pair<int, int> > entities) {
    if (entities.empty() || ability_blocked || robot.get_ability_type() != AbilityType::Teleports ||
        !robot.get_teleports().is_ready() || !robot.can_spend_stamina(robot.get_teleports().get_energy_cost()))
        return {0, 0};
    int xr = robot.get_position_on_game_x(), yr = robot.get_position_on_game_y();
    int min_dist = 1000000;
    for (std::pair<int, int> el: entities)
        min_dist = std::min(min_dist, NeedFunction::distance(xr, yr, el.first, el.second));
    if (min_dist > 1)
        return {0, 0};

    int radius = robot.get_teleports().get_radius();
    std::pair<int, int> requiring_dot = {0, 0};
    for (int x = std::max(1, xr - radius); x <= std::min(world.get_board().get_width(), xr + radius); ++x)
        for (int y = std::max(1, yr - radius); y <= std::min(world.get_board().get_height(), yr + radius); ++y) {
            if (!can_teleport_to_cell({x, y}))
                continue;
            int dist = 1000000;
            for (std::pair<int, int> el: entities)
                dist = std::min(dist, NeedFunction::distance(x, y, el.first, el.second));
            if (dist > min_dist) {
                min_dist = dist;
                requiring_dot = {x, y};
            }
        }
    return requiring_dot;
}

std::pair<int, int> IntelligenceRobots::random_way() {
    std::pair<int, int> directions[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::pair<int, int> direction = directions[NeedFunction::get_random_number(0, 3)];
    std::pair<int, int> dot = {
        robot.get_position_on_game_x() + direction.first,
        robot.get_position_on_game_y() + direction.second
    };
    if (!can_pass_cell(dot, {0, 0}) || !can_make_first_step(dot, {0, 0}) ||
        world.get_board().get_square(dot.first, dot.second).get_robot() != nullptr)
        return {0, 0};
    return dot;
}

bool IntelligenceRobots::moved(std::pair<int, int> dot) {
    Moved moving;
    CellType robot_type = robot.get_is_friend() ? CellType::AllyType : CellType::EnemyType;
    return moving.entities_move(robot, world, dot, robot_type);
}
