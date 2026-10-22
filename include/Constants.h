#pragma once
constexpr int WINDOW_HEIGHT = 768;
constexpr int WINDOW_WIDTH = 1366;
constexpr int FPS = 30;
constexpr int CEIL_SIZE = 45;
constexpr int FACTORY_X = 2;
constexpr int FACTORY_Y = 2;
constexpr int BOARD_HEIGHT = 10;
constexpr int BOARD_WIDTH = 10;

constexpr int ROBOT_RADIUS = 10;
constexpr int VISIBILITY_DISTANCE = 7;

constexpr float OFFSET_X = (WINDOW_WIDTH - CEIL_SIZE * (BOARD_WIDTH + 2)) / 2.f;
constexpr float OFFSET_Y = (WINDOW_HEIGHT - CEIL_SIZE * (BOARD_HEIGHT + 2)) / 2.f;

constexpr int MAX_COUNT_CELL_HEIGH = WINDOW_HEIGHT / CEIL_SIZE - 2;
constexpr int MAX_COUNT_CELL_WIDTH = WINDOW_WIDTH / CEIL_SIZE - 2;

constexpr int HP_UP_FOR_RANK = 70;
constexpr int MAX_HP_UP_FOR_RANK = 100;
constexpr int DAMAGE_UP_FOR_RANK = 30;
constexpr int STAMINA_UP_FOR_RANK = 5;
constexpr int MAX_STAMINA_UP_FOR_RANK = 5;
constexpr int XP_NEED_FOR_NEXT_RANK = 5;
constexpr int VISIBILITY_DISTANCE_UP_FOR_RANK = 1;

constexpr int STAMINA_FOR_EASY_CELL = 5;
constexpr int STAMINA_FOR_MEDIUM_CELL = 10;
constexpr int STAMINA_FOR_HARD_CELL = 15;
constexpr int MAX_STAMINA = 10;
constexpr int STAMINA_RESTORED_PER_TURN = 15;
constexpr int HEAL = 30;
constexpr int XP_FOR_KILL = 30;
constexpr int MAX_HP = 100;
constexpr int DAMAGE = 50;

