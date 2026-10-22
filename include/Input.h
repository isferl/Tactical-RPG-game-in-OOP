#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <optional>

class Input {
public:
    enum class Action {
        Close, Confirm, Cancel, EndTurn,
        MoveLeft, MoveRight, MoveUp, MoveDown
    };

    std::optional<Action> read(sf::RenderWindow &window) const;

    std::optional<Action> translate(const sf::Event &event) const;
};
