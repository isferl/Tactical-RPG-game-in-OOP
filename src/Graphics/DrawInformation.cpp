#include <Graphics/DrawInformation.h>
#include <Robot/Player.h>
#include <Other/Constants.h>

DrawInformation::DrawInformation(sf::RenderWindow &window)
    : DrawBase(window) {
}

void DrawInformation::draw_player_information(RobotPlayer &player) const {
    float x = WINDOW_WIDTH - PLAYER_INFORMATION_WIDTH - PLAYER_PANEL_OFFSET;
    float y = PLAYER_PANEL_OFFSET;
    draw_player_text("HP: " + std::to_string(player.get_hp()) + "/" + std::to_string(player.get_max_hp()), {x, y},
                     PLAYER_INFORMATION_TEXT_SIZE);
    y += PLAYER_INFORMATION_LINE_OFFSET;
    draw_player_text("Энергия: " + std::to_string(player.get_stamina()) + "/" +
                     std::to_string(player.get_max_stamina()), {x, y}, PLAYER_INFORMATION_TEXT_SIZE);
    y += PLAYER_INFORMATION_LINE_OFFSET;
    int base_damage = player.Robot::get_damage();
    int boost_damage = player.get_damage() - base_damage;
    std::string damage = "Урон: " + std::to_string(base_damage);
    if (boost_damage > 0)
        damage += " + " + std::to_string(boost_damage);
    draw_player_text(damage, {x, y}, PLAYER_INFORMATION_TEXT_SIZE);
    y += PLAYER_INFORMATION_LINE_OFFSET;
    draw_player_text("Ранг: " + std::to_string(player.get_rank()), {x, y}, PLAYER_INFORMATION_TEXT_SIZE);
    y += PLAYER_INFORMATION_LINE_OFFSET;
    draw_player_text("Опыт: " + std::to_string(player.get_xp()) + "/" +
                     std::to_string(player.get_xp_to_next_rank()), {x, y}, PLAYER_INFORMATION_TEXT_SIZE);
    y += PLAYER_INFORMATION_LINE_OFFSET;
    draw_player_text("Щит: " + std::to_string(player.get_shield().get_turns() * SHIELD_BlOCK), {x, y},
                     PLAYER_INFORMATION_TEXT_SIZE);
}

