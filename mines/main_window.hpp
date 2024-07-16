//
// Created by nbollom on 16/07/24.
//

#pragma once
#include <window.hpp>
#include <toolbar_button.hpp>
#include "game_scene.hpp"

using namespace ndg::common;

namespace ndg::mines {

    class MainWindow : public Window {

    private:
        State _state;
        GameScene _scene;
        Menu _difficulty_menu;

        void NewGame(Difficulty difficulty);
        bool IsDifficulty(Difficulty difficulty);

    public:
        MainWindow();
        ~MainWindow() override;


    };

}
