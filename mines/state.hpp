//
// Created by nbollom on 12/02/24.
//

#pragma once
#include <colour.hpp>
#include <window.hpp>

using namespace ndg::common;

namespace ndg::mines {

    class Game;  // Forward declare game to avoid circular reference

    typedef enum {
        Easy,
        Medium,
        Hard,
        Impossible,
        Custom
    } Difficulty;

    struct State {

        Difficulty difficulty = Easy;
        int custom_width = 10;
        int custom_height = 10;
        int custom_mines = 5;

        Colour bg_colour = {0.1f, 0.2f, 0.1f, 1.0f};

        // Non persistent state
        bool show_custom_config = false;
        Window *window = nullptr;
        Game *game = nullptr;

        void LoadState();
        void SaveState();

    };

}
