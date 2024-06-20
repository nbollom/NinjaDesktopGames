//
// Created by nbollom on 20/06/24.
//

#include "menu.hpp"
#include <GLFW/glfw3.h>

#include <utility>

using namespace ndg::common;

const float padding = 10;
const float item_size = 50;

const float selection_size = 10;

MenuItem::MenuItem(std::string text, std::function<void()> callback) : _text(std::move(text)), _callback(std::move(callback)) {

}

float MenuItem::PreCalculateIdealWidth(NVGcontext *context) {
    return nvgTextBounds(context, 0, 0, _text.c_str(), nullptr, nullptr) + padding * 2;
}

void MenuItem::Draw(NVGcontext *context, float x, float y) {
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

void MenuItem::Click() {
    _callback();
}

SelectableMenuItem::SelectableMenuItem(std::string text, std::function<void()> callback, std::function<bool()> is_selected) : MenuItem(std::move(text), std::move(callback)), _is_selected(std::move(is_selected)) {

}

float SelectableMenuItem::PreCalculateIdealWidth(NVGcontext *context) {
    return nvgTextBounds(context, 0, 0, _text.c_str(), nullptr, nullptr) + padding * 3 + selection_size;
}

void SelectableMenuItem::Draw(NVGcontext *context, float x, float y) {
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
    nvgCircle(context, x + padding + selection_size / 2, _height / 2 + y, selection_size);
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
    nvgStroke(context);
    if (_is_selected()) {
        nvgFillColor(context, nvgRGB(0, 0, 0));
        nvgFill(context);
    }
    else if (_mouse_down) {
        nvgFillColor(context, nvgRGB(60, 60, 60));
        nvgFill(context);
    }

    nvgBeginPath(context);
    nvgFillColor(context, nvgRGB(0, 0, 0));
    nvgTextAlign(context, NVG_ALIGN_MIDDLE);
    nvgText(context, x + padding * 2 + 10, _height / 2 + y, _text.c_str(), nullptr);

    nvgRestore(context);
}

void Menu::Draw(NVGcontext *context, float x, float y) {
    if (Width() == 0) {
        float max_width = 0;
        for (auto &item: _items) {
            max_width = std::max(max_width, item->PreCalculateIdealWidth(context));
        }
        Width(max_width);
    }
    nvgSave(context);
    nvgBeginPath(context);
    nvgRect(context, x, y, _width, _height);
    nvgFillColor(context, nvgRGB(180, 150, 150));
    nvgFill(context);
    nvgStrokeColor(context, nvgRGB(0, 0, 0));
    nvgStrokeWidth(context, 2);
    nvgStroke(context);
    nvgRestore(context);

    float pos = y;
    for (auto& item: _items) {
        item->Height(item_size);
        item->Width(_width);
        item->Draw(context, x, pos);
        pos+= item_size;
    }
}

void Menu::HandleMouseClick(int button, int action, int mods, float x, float y) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        bool down = (action == GLFW_PRESS);
        float pos = 0;
        for (auto &item: _items) {
            if (y >= pos && y <= pos + item->Height()) {
                if (!down && item->IsMouseDown()) {
                    item->Click();
                }
                item->MouseDown(down);
                break;
            }
            pos += item->Height();
        }
    }
}

void Menu::AddItem(ndg::common::MenuItem *item) {
    _items.push_back(item);
    Height(static_cast<float>(_items.size()) * item_size);
    Width(0);
}
