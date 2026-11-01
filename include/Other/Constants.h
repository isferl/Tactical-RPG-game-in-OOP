#pragma once
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 950;
constexpr int FPS = 30;
constexpr int CEIL_SIZE = 40;
constexpr int FACTORY_X = 2;
constexpr int FACTORY_Y = 2;
constexpr int BOARD_HEIGHT = 10;
constexpr int BOARD_WIDTH = 10;

constexpr int ROBOT_RADIUS = 10;
constexpr int VISIBILITY_DISTANCE = 7;
constexpr int ENTITIES_VISIBILITY_DISTANCE = 7;

constexpr float OFFSET_X = (WINDOW_WIDTH - CEIL_SIZE * (BOARD_WIDTH + 2)) / 2.f;
constexpr float OFFSET_Y = (WINDOW_HEIGHT - CEIL_SIZE * (BOARD_HEIGHT + 2)) / 2.f;

constexpr int MAX_COUNT_CELL_HEIGH = WINDOW_HEIGHT / CEIL_SIZE - 2;
constexpr int MAX_COUNT_CELL_WIDTH = WINDOW_WIDTH / CEIL_SIZE - 2;

constexpr int MAX_HP_UP_FOR_RANK = 10;
constexpr int HP_UP_FOR_RANK = 10;
constexpr int DAMAGE_UP_FOR_RANK = 3;
constexpr int STAMINA_UP_FOR_RANK = 0;
constexpr int MAX_STAMINA_UP_FOR_RANK = 0;
constexpr int XP_NEED_FOR_NEXT_RANK = 30;
constexpr int VISIBILITY_DISTANCE_UP_FOR_RANK = 1;

constexpr int STAMINA_FOR_EASY_CELL = 5;
constexpr int STAMINA_FOR_MEDIUM_CELL = 10;
constexpr int STAMINA_FOR_HARD_CELL = 15;
constexpr int MAX_STAMINA = 10;
constexpr int HEAL = 30;
constexpr int XP_FOR_KILL = 30;
constexpr int MAX_HP = 100;
constexpr int DAMAGE = 50;
constexpr int COUNT_TO_SPAWN = 5;
inline int STAMINA_RESTORED_PER_TURN = 15;


constexpr int BURNING_DAMAGE = 5;
constexpr int SHIELD_BlOCK = 5;

constexpr int COUNT_STATUS_FOR_TURN = 2;
constexpr int COUNT_ITEMS_FOR_TURN = 1;

constexpr int XP_TO_NEXT_LEVEL_ABILITY = 5;
constexpr int ENERGY_COST_AREA_ABILITY = 15;
constexpr int ENERGY_COST_FAIR_ABILITY = 15;
constexpr int ENERGY_COST_HEAL_ABILITY = 15;
constexpr int HEAL_TO_LEVEL = 15;
constexpr int ENERGY_COST_TELEPORT_ABILITY = 15;

constexpr int XP_FOR_RANK_UP = 10;

constexpr int CARD_IN_GAME = 4;
constexpr float CARD_WIDTH = 225.f;
constexpr float CARD_HEIGHT = 338.f;
constexpr float CARD_OFFSET = 24.f;
constexpr float INVENTORY_SLOT_SIZE = 50.f;
constexpr float INVENTORY_ITEM_SIZE = 40.f;
constexpr float INVENTORY_BOTTOM_OFFSET = 25.f;
constexpr float PLAYER_ICON_SIZE = 80.f;
constexpr float PLAYER_ICON_OFFSET = 24.f;
constexpr float PLAYER_PANEL_OFFSET = 25.f;
constexpr unsigned int PLAYER_INFORMATION_TEXT_SIZE = 28;
constexpr float PLAYER_INFORMATION_WIDTH = 300.f;
constexpr float PLAYER_INFORMATION_LINE_OFFSET = 42.f;
constexpr float PLAYER_LABEL_HEIGHT = 44.f;

constexpr int MEAT_HEALING = 30;
constexpr int ENERGY_DRINK_RESTORE = 30;
constexpr int STRENGTH_POTION = 30;
constexpr int STRENGTH_POTION_TIME = 5;

constexpr int BACKPACK_CAPACITY = 10;
constexpr int TELEPORT_RADIUS =5;

