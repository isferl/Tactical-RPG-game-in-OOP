#pragma once
#include <Graphics/DrawBoard.h>
#include <Graphics/DrawRobots.h>
#include <Graphics/DrawStatus.h>
#include <Graphics/DrawCard.h>
#include <Graphics/DrawInventory.h>
#include <Graphics/DrawInformation.h>
#include <Graphics/DrawHighlight.h>
#include <Graphics/DrawSelection.h>
#include <GameProcess/GameState.h>

class HandleAction;
class EndGame;

class RenderGame : private DrawBoard, private DrawRobots, private DrawStatus, private DrawCard,
                   private DrawInventory, private DrawInformation, private DrawHighlight, private DrawSelection {
public:
    RenderGame(sf::RenderWindow &window);

    using DrawHighlight::change_display_mode;

    virtual void draw_all(GameWorld &world, GameState current_state, const HandleAction &actions,
                          EndGame &endgame, GenerateCard &card);
};
