//
// Created by nbollom on 12/02/24.
//

#pragma once

#include <vector>
#include <concepts>
#include "drawable.hpp"
#include "toolbar_item.hpp"

namespace ndg::common {

    template<class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    class Toolbar: public Drawable{

    private:
        bool _visible = true;
        std::vector<ToolbarItem*> _items;

    public:
        Toolbar();
        ~Toolbar() override = default;

        [[nodiscard]] bool Visible() const;
        void Visible(bool value);

        void AddItem(ToolbarItem *item);

        void HandleMouseClick(int button, int action, int mods, float x, float y);

        void Draw(NVGcontext *context, float x, float y) override;

    };

}