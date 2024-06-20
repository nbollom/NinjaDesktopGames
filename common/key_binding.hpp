//
// Created by nbollom on 20/06/24.
//

#pragma once
#include <functional>
#include <utility>

namespace ndg::common {

    struct KeyBinding {
        int key;
        int action;
        int mods;
        std::function<void()> callback;

        explicit KeyBinding(int key, int action, int mods, std::function<void()> callback) : key(key), action(action), mods(mods), callback(std::move(callback)) {

        }
    };

}