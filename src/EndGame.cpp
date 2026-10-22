#include "../include/EndGame.h"
#include "../include/Constants.h"

EndGame::EndGame(int count_enemy, const std::string &font_path)
    : count_enemy(count_enemy), font(font_path), text(font) {
    text.setCharacterSize(48);
    text.setPosition({CEIL_SIZE, WINDOW_HEIGHT / 2.f});
}

int EndGame::get_count_enemy() const {
    return count_enemy;
}
void EndGame::set_count_enemy(int value) {
    count_enemy = value;
}

bool EndGame::is_win() const {
    return player_alive && count_enemy <= 0;
}

void EndGame::draw(sf::RenderWindow &window) {
    text.setString(is_win() ? "You win!" : "You lose!");
    text.setFillColor(is_win() ? sf::Color::Green : sf::Color::Red);
    window.draw(text);
}

void EndGame::set_player_alive(bool value) {
	player_alive = value;
}
