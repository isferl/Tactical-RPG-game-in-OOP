#pragma once

enum class GameState {
    WaitingForPlayerInput,
    PlayerMoving,
    EnemiesMoving,
    TurnComplete,
    GameOver,
    ChoosingCell,
    ChoosingUpdateAbility
};