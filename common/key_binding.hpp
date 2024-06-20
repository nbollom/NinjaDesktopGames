//
// Created by nbollom on 20/06/24.
//

#pragma once
#include <functional>

namespace ndg::common {

    struct KeyBinding {
        int key;
        int action;
        int mods;
        std::function<void()> callback;
    };

}