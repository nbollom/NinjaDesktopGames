//
// Created by nbollom on 6/07/24.
//

#include "status_bar.hpp"

#include <utility>

using namespace ndg::common;

const float padding = 10;

StatusBarItem::StatusBarItem(std::function<std::string()> get_label_callback) : _get_label_callback(std::move(get_label_callback)) {

}

void StatusBarItem::Draw(NVGcontext *context, float x, float y) {
    auto text = _get_label_callback();
    _width = nvgTextBounds(context, 0, 0, text.c_str(), nullptr, nullptr) + padding * 2;
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, _width, _height);
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
    nvgStrokeWidth(context, 1);
    nvgStroke(context);

    nvgBeginPath(context);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgTextAlign(context, NVG_ALIGN_MIDDLE);
    nvgText(context, x + padding, _height / 2 + y, text.c_str(), nullptr);

    nvgRestore(context);
}

StatusBar::StatusBar() {
    _height = 25;
}

void StatusBar::Draw(NVGcontext *context, float x, float y) {
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, _width, _height);
    nvgFillColor(context, nvgRGB(180, 150, 150));
    nvgFill(context);
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
    nvgStrokeWidth(context, 2);
    nvgStroke(context);
    nvgRestore(context);

    float pos = x;
    for (auto& item: _items) {
        item->Height(_height);
        item->Draw(context, pos, y);
        pos+= item->Width();
    }
}

void StatusBar::AddItem(std::unique_ptr<StatusBarItem> item) {
    _items.push_back(std::move(item));
}

bool StatusBar::HasItems() {
    return !_items.empty();
}
