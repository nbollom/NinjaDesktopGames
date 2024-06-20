//
// Created by nbollom on 27/02/24.
//

#include "toolbar_button.hpp"

#include <utility>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop

using namespace ndg::common;

const float padding = 10;

ToolbarButton::ToolbarButton(std::string_view text, std::function<void()> callback): _text(text), _callback(std::move(callback)) {

}

bool ToolbarButton::Clickable() {
    return true;
}

void ToolbarButton::Click() {
    _callback();
}

void ToolbarButton::Draw(NVGcontext *context, float x, float y) {
    _width = nvgTextBounds(context, 0, 0, _text.c_str(), nullptr, nullptr) + padding * 2;
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, _width, _height);
    if (_mouse_down) {
        nvgFillColor(context, nvgRGB(120, 100, 100));
        nvgFill(context);
    }
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
    nvgStrokeWidth(context, 1);
    nvgStroke(context);

    nvgBeginPath(context);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgTextAlign(context, NVG_ALIGN_MIDDLE);
    nvgText(context, x + padding, _height / 2 + y, _text.c_str(), nullptr);

    nvgRestore(context);
}
