#pragma once

enum class GameState {
    WaitingForPlayerInput = 0,
    PlayerMoving = 1,
    EnemiesMoving = 2,
    TurnComplete = 3,
    GameOver = 4
};