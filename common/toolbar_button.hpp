//
// Created by nbollom on 27/02/24.
//

#pragma once

#include <string>
#include <string_view>
#include <functional>
#include "toolbar_item.hpp"
#include "clickable.hpp"

namespace ndg::common {

    class ToolbarButton: public ToolbarItem, public Clickable {

    private:
        std::string _text;
        std::function<void()> _callback;

    public:

        ToolbarButton(std::string_view text, std::function<void()> callback);

        bool Clickable() override;
        void Click() override;

        void Draw(NVGcontext *context, float x, float y) override;

    };

}
