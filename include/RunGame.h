#pragma once
#include "Player.h"
#include "FullMap.h"
#include "GameState.h"
#include "GenerateBoard.h"
#include "Input.h"
#include "Moved.h"
#include "EndGame.h"
#include "FactoryRobot.h"

class RunGame {
protected:
	GameState current_state = GameState::WaitingForPlayerInput;
	int turn_number = 0;

	void handle_action(Input::Action action, Board &board, RobotPlayer &player,
		FullMap &map, Moved &moved, sf::RenderWindow &window,
		const std::vector<Robot> &enemies, EndGame &endgame);
	bool check_game_over(const RobotPlayer &player,
		const std::vector<Robot> &enemies, EndGame &endgame);
	void update_turn(Board &board, RobotPlayer &player, FullMap &map,
		std::vector<Robot> &allies, std::vector<Robot> &enemies,
		std::vector<RobotFactory> &factories, EndGame &endgame);

public:
	void launch_window();
	void end_turn(Board &board, RobotPlayer &player, FullMap &map,
		std::vector<Robot> &allies, std::vector<Robot> &enemies);
	void next_turn(RobotPlayer &player, std::vector<Robot> &allies,
		std::vector<Robot> &enemies);
};
