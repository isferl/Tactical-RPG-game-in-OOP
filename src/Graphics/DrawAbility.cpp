#include <Graphics/DrawAbility.h>
#include <Robot/Player.h>
#include <Other/Constants.h>

DrawAbility::DrawAbility(sf::RenderWindow &window)
    : DrawBase(window) {
    load_texture(ability_area_damage, "Ability/ability_area_damage.png");
    load_texture(ability_fair_damage, "Ability/ability_fair_damage.png");
    load_texture(ability_heal, "Ability/ability_heal.png");
    load_texture(ability_teleport, "Ability/ability_teleport.png");
}

void DrawAbility::draw_player_abilities(RobotPlayer &player) const {
    int count = 0;
    for (const auto &[type, ability]: player.get_ability())
        if (ability && ability->get_level() != 0)
            ++count;
    if (count == 0)
        return;

    float width = count * PLAYER_ICON_SIZE + (count - 1) * PLAYER_ICON_OFFSET;
    float x = WINDOW_WIDTH - PLAYER_PANEL_OFFSET - width;
    float y = WINDOW_HEIGHT - INVENTORY_BOTTOM_OFFSET - PLAYER_ICON_SIZE - PLAYER_LABEL_HEIGHT;
    for (const auto &[type, ability]: player.get_ability()) {
        if (!ability || ability->get_level() == 0)
            continue;
        const sf::Texture *texture = nullptr;
        std::string key;
        switch (type) {
            case AbilityType::AreaDamage: texture = &ability_area_damage;
                key = "Z";
                break;
            case AbilityType::FairDamage: texture = &ability_fair_damage;
                key = "X";
                break;
            case AbilityType::Heal: texture = &ability_heal;
                key = "C";
                break;
            case AbilityType::Teleports: texture = &ability_teleport;
                key = "V";
                break;
        }
        if (!texture)
            continue;
        sf::RectangleShape icon({PLAYER_ICON_SIZE, PLAYER_ICON_SIZE});
        icon.setTexture(texture);
        icon.setPosition({x, y});
        window.draw(icon);
        int remaining = ability->get_remaining_cooldown();
        if (remaining > 0 && ability->get_cooldown() > 0) {
            float height = PLAYER_ICON_SIZE * remaining / ability->get_cooldown();
            sf::RectangleShape blackout({PLAYER_ICON_SIZE, height});
            blackout.setPosition({x, y + PLAYER_ICON_SIZE - height});
            blackout.setFillColor(sf::Color(0, 0, 0, 180));
            window.draw(blackout);
        }
        draw_player_text(key, {x, y});
        draw_player_text("Lv. " + std::to_string(ability->get_level()), {x, y + PLAYER_ICON_SIZE});
        draw_player_text("CD " + std::to_string(remaining),
                         {x, y + PLAYER_ICON_SIZE + PLAYER_LABEL_HEIGHT / 2.f});
        x += PLAYER_ICON_SIZE + PLAYER_ICON_OFFSET;
    }
}

