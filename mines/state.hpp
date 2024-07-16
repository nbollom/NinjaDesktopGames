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

        Colour bg_colour = {0.0f, 0.39f, 0.0f, 1.0f};
        Colour cell_bg_colour = Colours::White;
        Colour cell_fg_colour = Colours::Silver;
        Colour cell_border_colour = Colours::Black;
        Colour cell_1_colour = Colours::Gray;
        Colour cell_2_colour = Colours::Blue;
        Colour cell_3_colour = Colours::Green;
        Colour cell_4_colour = Colours::Red;
        Colour cell_5_colour = Colours::Navy;
        Colour cell_6_colour = Colours::Magenta;
        Colour cell_7_colour = Colours::Teal;
        Colour cell_8_colour = Colours::Maroon;
        Colour flag_unknown_colour = Colours::Yellow;
        Colour flag_bad_colour = Colours::Red;
        Colour flag_good_colour = Colours::Green;
        Colour mine_colour = Colours::Black;
        Colour mine_exploded_color = Colours::Red;

        // Non persistent state
        bool show_custom_config = false;
        Window *window = nullptr;
        Game *game = nullptr;

        void LoadState();
        void SaveState();

    };

}
