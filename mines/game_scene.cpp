//
// Created by nbollom on 12/02/24.
//

#include "game_scene.hpp"
#include <format>

using namespace ndg::mines;

GameScene::GameScene() = default;

void GameScene::Draw(NVGcontext *context, float x, float y, float width, float height, double time) {
    if (game) {
        game->Draw(context, x + 10, y + 10, width - 20, height - 20);
    }
}

void GameScene::NewGame(State &state) {
    delete game;
    game = Game::New(state);
}

void GameScene::HandleKeyEvent(int key, int scancode, int action, int mods) {

}

void GameScene::HandleMouseClick(int button, int action, int mods, float x, float y) {
    if (game) {
        game->HandleMouseClick(button, action, mods, x, y);
    }
}

std::string GameScene::GetGameState() {
    switch(game->GetGameState()) {
        case InProgress:
            return "Playing";
        case Won:
            return "Game Won";
        case Lost:
            return "Game Lost";
    }
    return "";
}

std::string GameScene::GetMinesCount() {
    return std::format("Found {} of {} mines", game->GetFlaggedCount(), game->GetMineCount());
}