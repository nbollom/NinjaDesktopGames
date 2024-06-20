//
// Created by nbollom on 13/02/24.
//

#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop
#include <tuple>

namespace ndg::mines {

    struct Cell {

        bool is_mine = false;
        bool is_revealed = false;
        bool is_flagged = false;
        int number = 0;

        std::tuple<float, float, float, float> last_pos;

        void Draw(NVGcontext *context, float x, float y, float width, float height, bool finished);

    };

}
