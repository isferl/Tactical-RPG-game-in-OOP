#include <Other/Input.h>

std::optional<Input::Action> Input::read(sf::RenderWindow &window) const {
    while (const auto event = window.pollEvent()) {
        if (const auto action = translate(*event))
            return action;
    }
    return std::nullopt;
}

std::optional<Input::Action> Input::translate(const sf::Event &event) const {
    if (event.is<sf::Event::Closed>())
        return Action::Close;
    const auto *key = event.getIf<sf::Event::KeyPressed>();
    if (!key)
        return std::nullopt;
    switch (key->code) {
        case sf::Keyboard::Key::Num1: return Action::UseAreaDamage;
        case sf::Keyboard::Key::Enter: return Action::Confirm;
        case sf::Keyboard::Key::Escape: return Action::Cancel;
        case sf::Keyboard::Key::Space: return Action::EndTurn;
        case sf::Keyboard::Key::A:
        case sf::Keyboard::Key::Left: return Action::MoveLeft;
        case sf::Keyboard::Key::D:
        case sf::Keyboard::Key::Right: return Action::MoveRight;
        case sf::Keyboard::Key::W:
        case sf::Keyboard::Key::Up: return Action::MoveUp;
        case sf::Keyboard::Key::S:
        case sf::Keyboard::Key::Down: return Action::MoveDown;
        case sf::Keyboard::Key::R: return Action::Restart;
        default: return std::nullopt;
    }
}
