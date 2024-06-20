//
// Created by nbollom on 9/04/24.
//

#include "clickable.hpp"

using namespace ndg::common;

static Clickable *currently_clicked = nullptr;

void SetCurrentlyClicked(Clickable *item) {
    currently_clicked = item;
}

void ndg::common::ClearMouseDown() {
    if (currently_clicked != nullptr) {
        currently_clicked->MouseDown(false);
        currently_clicked = nullptr;
    }
}

void Clickable::MouseDown(bool value) {
    _mouse_down = value;
    if (value) {
        SetCurrentlyClicked(this);
    }
}
