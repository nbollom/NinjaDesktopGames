//
// Created by nbollom on 12/02/24.
//

#pragma once

#include <scene.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop
#include "game.hpp"
#include "state.hpp"

using namespace ndg::common;

namespace ndg::mines {

    class GameScene : public Scene {

    private:
        Game *game = nullptr;

    public:
        GameScene();
        void Draw(NVGcontext *context, float x, float y, float width, float height, double time) override;

        void NewGame(State &state);

        void HandleKeyEvent(int key, int scancode, int action, int mods) override;
        void HandleMouseClick(int button, int action, int mods, float x, float y) override;

    };

}
