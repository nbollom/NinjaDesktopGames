//
// Created by nbollom on 6/07/24.
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "drawable.hpp"

namespace ndg::common {

    class StatusBarItem : public Drawable {
    private:
        std::function<std::string()> _get_label_callback;

    public:
        explicit StatusBarItem(std::function<std::string()> get_label_callback);
        void Draw(NVGcontext *context, float x, float y) override;

    };

    class StatusBar : public Drawable{

    private:
        std::vector<std::unique_ptr<StatusBarItem>> _items;

    public:
        StatusBar();
        void Draw(NVGcontext *context, float x, float y) override;
        void AddItem(std::unique_ptr<StatusBarItem> item);
        bool HasItems();

    };

}
