#pragma once
#include <SFML/Graphics.hpp>

class EndGame {
protected:
    int count_enemy = 0;
	bool player_alive = true;
    sf::Font font;
    sf::Text text;

public:
    EndGame(int count_enemy, const std::string &font_path);

    int get_count_enemy() const;

    void set_count_enemy(int value);

    bool is_win() const;

	void set_player_alive(bool value);

    void draw(sf::RenderWindow &window);
};
