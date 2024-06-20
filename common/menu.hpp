//
// Created by nbollom on 20/06/24.
//

#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop
#include <string>
#include <functional>
#include <vector>
#include "drawable.hpp"
#include "clickable.hpp"

namespace ndg::common {

    class MenuItem : public Drawable, public Clickable {
    protected:
        std::string _text;
        std::function<void()> _callback;

    public:
        MenuItem(std::string text, std::function<void()> callback);
        virtual float PreCalculateIdealWidth(NVGcontext *context);

        void Draw(NVGcontext *context, float x, float y) override;
        void Click() override;
    };

    class SelectableMenuItem : public MenuItem {
    private:
        std::function<bool()> _is_selected;

    public:
        SelectableMenuItem(std::string text, std::function<void()> callback, std::function<bool()> _is_selected);
        float PreCalculateIdealWidth(NVGcontext *context) override;

        void Draw(NVGcontext *context, float x, float y) override;
    };

    class Menu : public Drawable  {
    private:
        std::vector<MenuItem*> _items;

    public:
        void Draw(NVGcontext *context, float x, float y) override;
        void HandleMouseClick(int button, int action, int mods, float x, float y);

        void AddItem(MenuItem *item);
    };

}
