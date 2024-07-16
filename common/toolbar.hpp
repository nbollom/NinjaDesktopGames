//
// Created by nbollom on 12/02/24.
//

#pragma once

#include <vector>
#include <concepts>
#include <memory>
#include "drawable.hpp"
#include "toolbar_item.hpp"

namespace ndg::common {

    class Toolbar: public Drawable{

    private:
        bool _visible = true;
        std::vector<std::unique_ptr<ToolbarItem>> _items;

    public:
        Toolbar();

        [[nodiscard]] bool Visible() const;
        void Visible(bool value);

        void AddItem(std::unique_ptr<ToolbarItem> item);

        void HandleMouseClick(int button, int action, int mods, float x, float y);

        void Draw(NVGcontext *context, float x, float y) override;

    };

}