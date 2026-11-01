#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <optional>

class Input {
public:
    enum class Action {
        Close, Confirm, Cancel, EndTurn, ChangeDisplayMode,
        MoveLeft, MoveRight, MoveUp, MoveDown,
        Restart, UseAreaDamage, UseFairDamage, UseHeal, UseTeleports,
        Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0
    };

    std::optional<Action> read(sf::RenderWindow &window) const;

    std::optional<Action> translate(const sf::Event &event) const;
};
