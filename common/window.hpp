//
// Created by nbollom on 12/02/24.
//

#pragma once

#include <GLFW/glfw3.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop
#include "colour.hpp"
#include "toolbar.hpp"
#include "status_bar.hpp"
#include "scene.hpp"
#include "menu.hpp"
#include "key_binding.hpp"

namespace ndg::common {

    class Window {

    private:
        GLFWwindow *_window;
        NVGcontext *_context;
        int _width;
        int _height;
        Menu *_popup_menu = nullptr;
        float _popup_menu_pos_x;
        float _popup_menu_pos_y;
        Scene *_scene = nullptr;
        std::vector<KeyBinding> _key_bindings;

    protected:
        Toolbar _toolbar;
        StatusBar _status_bar;

    public:
        explicit Window(const char* name, int width, int height);
        virtual ~Window();

        [[nodiscard]] bool IsClosed() const;
        void Close() const;

        void Resize(int new_width, int new_height);
        void HandleKeyEvent(int key, int scancode, int action, int mods);
        void HandleMouseClick(int button, int action, int mods);
        std::pair<float, float> GetMousePos();

        void SetBackgroundColor(const Colour& colour);
        void SetScene(Scene *scene);

        void PollEvents();
        void Draw();

        void ShowPopupMenu(Menu *menu, float x, float y);
        void AddKeyBinding(int key, int action, int mods, const std::function<void()>& callback);

    };

}
