#include <Graphics/DrawCard.h>
#include <Robot/Player.h>
#include <GameProcess/GenerateCard.h>
#include <Other/Constants.h>

DrawCard::DrawCard(sf::RenderWindow &window)
    : DrawBase(window), DrawAbility(window) {
    load_texture(card_background, "Other/card_background.png");
    load_texture(new_badge, "Other/new_badge.png");
    load_texture(level_up_badge, "Other/level_up_badge.png");
}

void DrawCard::draw_cards(RobotPlayer &player, GenerateCard &cards) const {
    sf::RectangleShape blackout({(float) WINDOW_WIDTH, (float) WINDOW_HEIGHT});
    blackout.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(blackout);

    int count = cards.get_size();
    if (count == 0)
        return;

    float width = count * CARD_WIDTH + (count - 1) * CARD_OFFSET;
    float x = (WINDOW_WIDTH - width) / 2.f;
    float y = (WINDOW_HEIGHT - CARD_HEIGHT) / 2.f;
    for (int i = 0; i < count; ++i) {
        AbilityType type = cards.get_to_index(i);
        draw_card(*player.get_ability().at(type), {x + i * (CARD_WIDTH + CARD_OFFSET), y}, i + 1);
    }
}

void DrawCard::draw_card(Ability &ability, sf::Vector2f position, int number) const {
    const sf::Texture *picture = nullptr;
    std::string name, description, effect_name;
    switch (ability.get_name()) {
        case AbilityType::AreaDamage:
            picture = &ability_area_damage;
            name = "УДАР ВОКРУГ";
            effect_name = "Радиус: ";
            description = "Урон вокруг робота.\nНакладывает\nперегрузку.";
            break;
        case AbilityType::FairDamage:
            picture = &ability_fair_damage;
            name = "ДАЛЬНИЙ УДАР";
            effect_name = "Урон: ";
            description = "Урон выбранной цели.\nНакладывает горение.";
            break;
        case AbilityType::Heal:
            picture = &ability_heal;
            name = "ЛЕЧЕНИЕ";
            effect_name = "Лечение: ";
            description = "Восстановление HP.\nИзлишек лечения\nпревращается в щит.";
            break;
        case AbilityType::Teleports:
            picture = &ability_teleport;
            name = "ТЕЛЕПОРТ";
            description = "Перемещение на\nвыбранную свободную\nклетку.";
            break;
    }
    if (picture == nullptr)
        return;

    std::unique_ptr<Ability> upgraded = ability.clone();
    upgraded->add_xp(XP_FOR_RANK_UP);
    name += " УР. " + std::to_string(ability.get_level()) + " -> " + std::to_string(upgraded->get_level());

    sf::RectangleShape background({CARD_WIDTH, CARD_HEIGHT});
    background.setTexture(&card_background);
    background.setPosition(position);
    window.draw(background);

    sf::RectangleShape icon({120.f, 120.f});
    icon.setTexture(picture);
    icon.setPosition(position + sf::Vector2f{52.f, 46.f});
    window.draw(icon);

    float text_width = CARD_WIDTH - 36.f;
    draw_card_text(name, position + sf::Vector2f{18.f, 21.f}, 15, text_width);
    draw_card_text(description, position + sf::Vector2f{18.f, 180.f}, 13, text_width);
    if (!effect_name.empty()) {
        std::string value = ability.get_level() == 0
                                ? std::to_string(upgraded->get_upgrade_value())
                                : get_card_change(ability.get_upgrade_value(), upgraded->get_upgrade_value());
        if (ability.get_name() == AbilityType::FairDamage)
            value += "%";
        draw_card_text(effect_name + value, position + sf::Vector2f{18.f, 231.f}, 12, text_width);
    }
    draw_card_text("Энергия: " + get_card_change(ability.get_energy_cost(), upgraded->get_energy_cost()),
                   position + sf::Vector2f{18.f, 262.f}, 12, text_width);
    draw_card_text("Перезарядка: " + get_card_change(ability.get_cooldown(), upgraded->get_cooldown()),
                   position + sf::Vector2f{18.f, 280.f}, 12, text_width);
    std::string xp = std::to_string(ability.get_xp()) + "/" + std::to_string(ability.get_xp_to_next_level());
    std::string next_xp = std::to_string(upgraded->get_xp()) + "/" + std::to_string(upgraded->get_xp_to_next_level());
    if (xp != next_xp)
        xp += " -> " + next_xp;
    draw_card_text("Опыт: " + xp, position + sf::Vector2f{18.f, 303.f}, 12, text_width);

    sf::RectangleShape badge({CARD_WIDTH, 75.f});
    badge.setTexture(ability.get_level() == 0 ? &new_badge : &level_up_badge);
    badge.setPosition(position + sf::Vector2f{0.f, -75.f});
    window.draw(badge);

    sf::Text key(card_font);
    key.setString(std::to_string(number));
    key.setCharacterSize(30);
    key.setFillColor(sf::Color::White);
    key.setPosition(position + sf::Vector2f{105.f, 352.f});
    window.draw(key);
}

void DrawCard::draw_card_text(const std::string &str, sf::Vector2f position, unsigned int size,
                                float max_width) const {
    sf::Text text(card_font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    while (max_width > 0.f && text.getLocalBounds().size.x > max_width && text.getCharacterSize() > 6)
        text.setCharacterSize(text.getCharacterSize() - 1);
    window.draw(text);
}

std::string DrawCard::get_card_change(int current, int next) const {
    std::string str = std::to_string(current);
    if (current != next)
        str += " -> " + std::to_string(next);
    return str;
}

