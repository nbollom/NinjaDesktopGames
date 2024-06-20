//
// Created by nbollom on 25/02/24.
//

#include "toolbar.hpp"
#include "toolbar_button.hpp"
#include <GLFW/glfw3.h>

using namespace ndg::common;

Toolbar::Toolbar() {
    _height = 50;
}

bool Toolbar::Visible() const {
    return _visible;
}

void Toolbar::Visible(bool value) {
    _visible = value;
}

void Toolbar::AddItem(ToolbarItem *item) {
    _items.push_back(item);
}

void Toolbar::HandleMouseClick(int button, int action, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        bool down = (action == GLFW_PRESS);
        float pos = 0;
        for (auto &item: _items) {
            if (x >= pos && x <= pos + item->Width() && item->Clickable()) {
                auto *toolbar_button = dynamic_cast<ToolbarButton*>(item);
                if (!down && toolbar_button->IsMouseDown()) {
                    toolbar_button->Click();
                }
                toolbar_button->MouseDown(down);
                break;
            }
            pos += item->Width();
        }
    }
}

void Toolbar::Draw(NVGcontext *context, float x, float y) {
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, 0, 0, _width, 50);
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
