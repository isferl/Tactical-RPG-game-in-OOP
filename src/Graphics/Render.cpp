#include <Graphics/Render.h>
#include <GameProcess/HandleAction.h>
#include <GameProcess/EndGame.h>
#include <GameProcess/GenerateCard.h>
#include <GameMap/GameWorld.h>

RenderGame::RenderGame(sf::RenderWindow &window)
    : DrawBase(window), DrawBoard(window), DrawRobots(window), DrawStatus(window), DrawCard(window),
      DrawInventory(window), DrawInformation(window), DrawHighlight(window), DrawSelection(window) {
}

void RenderGame::draw_all(GameWorld &world, GameState current_state, const HandleAction &actions,
                          EndGame &endgame, GenerateCard &card) {
    window.clear();
    draw_board(world);
    draw_status_in_cell(world);
    draw_items(world);
    draw_factories(world);
    draw_player(world);
    draw_robots(world.get_enemies(), CellType::EnemyType);
    draw_robots(world.get_allies(), CellType::AllyType);
    draw_highlight(world);
    draw_invisible_cell(world);

    if (current_state == GameState::ChoosingCell) {
        auto ability_type = actions.get_selected_ability_type();
        if (ability_type)
            draw_selected_cell(actions.get_selection().get_selected(), world, *ability_type);
        draw_blackout(actions.get_selection().get_radius(), world);
    }

    if (current_state == GameState::GameOver)
        endgame.draw(window);

    draw_inventory(world.get_player());
    draw_player_statuses(world.get_player());
    draw_player_abilities(world.get_player());
    draw_player_information(world.get_player());
    draw_display_mode();
    if (current_state == GameState::ChoosingUpdateAbility)
        draw_cards(world.get_player(), card);
    window.display();
}
