//
// Created by nbollom on 13/02/24.
//

#include "cell.hpp"
#include <string>

using namespace ndg::mines;

void Cell::Draw(NVGcontext *context, float x, float y, float width, float height, bool finished) {
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, width, height);
    if (is_revealed) {
        nvgFillColor(context, nvgRGB(255, 255, 255));
    }
    else {
        nvgFillColor(context, nvgRGB(180, 150, 150));
    }
    nvgFill(context);
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
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
                    color = nvgRGB(105, 105, 105);
                    break;
                case 2:
                    color = nvgRGB(0, 0, 255);
                    break;
                case 3:
                    color = nvgRGB(0, 100, 0);
                    break;
                case 4:
                    color = nvgRGB(255, 0, 0);
                    break;
                case 5:
                    color = nvgRGB(0, 0, 139);
                    break;
                case 6:
                    color = nvgRGB(139, 0, 0);
                    break;
                case 7:
                    color = nvgRGB(0, 128, 128);
                    break;
                case 8:
                    color = nvgRGB(0, 0, 0);
                    break;
                case 9:
                    color = nvgRGB(169, 169, 169);
                    break;
            }
            nvgFillColor(context, color);
            nvgText(context, width / 2 + x, height / 2 + y, number_str.c_str(), nullptr);
        }
        else if (is_mine) {
            if (finished && is_flagged) {
                nvgFillColor(context, nvgRGB(0, 100, 0));
                nvgText(context, width / 2 + x, height / 2 + y, "\xe2\x9a\x91", nullptr);
            }
            else {
                nvgFillColor(context, nvgRGB(0, 0, 0));
                nvgText(context, width / 2 + x, height / 2 + y, "\xE2\x98\xA0", nullptr);
            }
        }
    }
    else {
        if (is_flagged) {
            if (finished) {
                if (is_mine) {
                    nvgFillColor(context, nvgRGB(0, 100, 0));
                }
                else {
                    nvgFillColor(context, nvgRGB(200, 0, 0));
                }
            }
            else {
                nvgFillColor(context, nvgRGB(255, 255, 0));
            }
            nvgText(context, width / 2 + x, height / 2 + y, "\xe2\x9a\x91", nullptr);
        }
    }

    nvgRestore(context);

    last_pos = std::make_tuple(x, x + height, y, y + width);
}