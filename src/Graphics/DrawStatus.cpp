#include <Graphics/DrawStatus.h>
#include <GameMap/GameWorld.h>
#include <Other/Constants.h>

DrawStatus::DrawStatus(sf::RenderWindow &window)
    : DrawBase(window) {
    load_texture(status_burning, "Status/status_burning.png");
    load_texture(status_overload, "Status/status_overload.png");
    load_texture(status_shield, "Status/status_shield.png");
    load_texture(status_slowdown, "Status/status_slowdown.png");
}

void DrawStatus::draw_status_in_cell(GameWorld &world) const {
    int x_map = world.get_board().get_width() + 2;
    int y_map = world.get_board().get_height() + 2;
    for (int x = 0; x < x_map; ++x) {
        for (int y = 0; y < y_map; ++y) {
            std::list<StatusType> &statuses = world.get_board().get_square(x, y).get_statuses();
            if (statuses.size() == 0)
                continue;
            if (statuses.size() == 1)
                draw_rectangle({x, y}, 0, CEIL_SIZE, get_color_for_status(*statuses.begin()));
            if (statuses.size() == 2) {
                draw_rectangle({x, y}, 0, CEIL_SIZE / 2.0, get_color_for_status(*(statuses.begin()++)));
                draw_rectangle({x, y}, CEIL_SIZE / 2.0, CEIL_SIZE / 2.0, get_color_for_status(*statuses.begin()));
            }
        }
    }
}

sf::Color DrawStatus::get_color_for_status(StatusType type) const {
    switch (type) {
        case StatusType::Burning:
            return sf::Color{255, 0, 0, 90};
        case StatusType::Overload:
            return sf::Color{255, 255, 0, 90};
        case StatusType::Shield:
            return sf::Color{0, 100, 255, 90};
        case StatusType::Slowdown:
            return sf::Color{160, 70, 220, 90};
    }
    return {0, 0, 0, 0};
}

void DrawStatus::draw_player_statuses(RobotPlayer &player) const {
    float x = PLAYER_PANEL_OFFSET;
    float y = WINDOW_HEIGHT - INVENTORY_BOTTOM_OFFSET - PLAYER_ICON_SIZE - PLAYER_LABEL_HEIGHT;
    for (const auto &[type, status]: player.get_statues()) {
        if (!status || status->is_finished())
            continue;
        const sf::Texture *texture = nullptr;
        switch (type) {
            case StatusType::Burning:
                texture = &status_burning;
                break;
            case StatusType::Overload:
                texture = &status_overload;
                break;
            case StatusType::Shield:
                texture = &status_shield;
                break;
            case StatusType::Slowdown:
                texture = &status_slowdown;
                break;
        }
        if (!texture)
            continue;
        sf::RectangleShape icon({PLAYER_ICON_SIZE, PLAYER_ICON_SIZE});
        icon.setTexture(texture);
        icon.setPosition({x, y});
        window.draw(icon);
        draw_player_text("АКТИВЕН", {x, y + PLAYER_ICON_SIZE});
        if (type != StatusType::Overload)
            draw_player_text("ХОДЫ " + std::to_string(status->get_turns()),
                             {x, y + PLAYER_ICON_SIZE + PLAYER_LABEL_HEIGHT / 2.f});
        x += PLAYER_ICON_SIZE + PLAYER_ICON_OFFSET;
    }
}

