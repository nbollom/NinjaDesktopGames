//
// Created by nbollom on 13/02/24.
//

#include "cell.hpp"
#include <string>
#include <colour.hpp>

using namespace ndg::mines;
using namespace ndg::common;

void Cell::Draw(NVGcontext *context, float x, float y, float width, float height, bool finished, State &state) {
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, width, height);
    if (is_revealed) {
        nvgFillColor(context, state.cell_bg_colour.ToNVGColor());
    }
    else {
        nvgFillColor(context, state.cell_fg_colour.ToNVGColor());
    }
    nvgFill(context);
    nvgStrokeColor(context, state.cell_border_colour.ToNVGColor());
    nvgStrokeWidth(context, 1);
    nvgStroke(context);

    nvgBeginPath(context);
    nvgTextAlign(context, NVG_ALIGN_MIDDLE | NVG_ALIGN_CENTER);
    nvgFontSize(context, width * 0.8f);

    if (is_revealed) {
        if (number != 0) {
            auto number_str = std::to_string(number);
            NVGcolor color;
            switch (number) {
                case 1:
                    color = state.cell_1_colour.ToNVGColor();
                    break;
                case 2:
                    color = state.cell_2_colour.ToNVGColor();
                    break;
                case 3:
                    color = state.cell_3_colour.ToNVGColor();
                    break;
                case 4:
                    color = state.cell_4_colour.ToNVGColor();
                    break;
                case 5:
                    color = state.cell_5_colour.ToNVGColor();
                    break;
                case 6:
                    color = state.cell_6_colour.ToNVGColor();
                    break;
                case 7:
                    color = state.cell_7_colour.ToNVGColor();
                    break;
                case 8:
                    color = state.cell_8_colour.ToNVGColor();
                    break;
            }
            nvgFillColor(context, color);
            nvgText(context, width / 2 + x, height / 2 + y, number_str.c_str(), nullptr);
        }
        else if (is_mine) {
            if (is_exploded) {
                nvgFillColor(context, state.mine_exploded_color.ToNVGColor());
            }
            else {
                nvgFillColor(context, state.mine_colour.ToNVGColor());
            }
            nvgText(context, width / 2 + x, height / 2 + y, "\xE2\x98\xA0", nullptr);
        }
    }
    else {
        if (is_flagged) {
            if (finished) {
                if (is_mine) {
                    nvgFillColor(context, state.flag_good_colour.ToNVGColor());
                }
                else {
                    nvgFillColor(context, state.flag_bad_colour.ToNVGColor());
                }
            }
            else {
                nvgFillColor(context, state.flag_unknown_colour.ToNVGColor());
            }
            nvgText(context, width / 2 + x, height / 2 + y, "\xe2\x9a\x91", nullptr);
        }
    }

    nvgRestore(context);

    last_pos = std::make_tuple(x, x + height, y, y + width);
}