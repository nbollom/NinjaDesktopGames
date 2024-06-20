//
// Created by nbollom on 12/02/24.
//

#include <iostream>
#include <GL/gl3w.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
#pragma GCC diagnostic pop
#include "window.hpp"
#include "common.hpp"
#include "clickable.hpp"

using namespace ndg::common;

Window::Window(const char* name, int width, int height) : _width(width), _height(height) {
    initialise_glfw();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    if (_width == -1) {
        _width = mode->width;
    }

    if (_height == -1) {
        _height = mode->height;
    }

    _window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if (!_window) {
        std::cout << "ERROR: Failed to open GLFW window\n";
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow* w, int new_width, int new_height){
        static_cast<Window*>(glfwGetWindowUserPointer(w))->Resize(new_width, new_height);
    });
    glfwSetKeyCallback(_window, [](GLFWwindow* w, int key, int scancode, int action, int mods){
        static_cast<Window*>(glfwGetWindowUserPointer(w))->HandleKeyEvent(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(_window, [](GLFWwindow* w, int button, int action, int mods){
        static_cast<Window*>(glfwGetWindowUserPointer(w))->HandleMouseClick(button, action, mods);
    });

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    initialise_gl3w();

    _context = nvgCreateGL3(NVG_STENCIL_STROKES);
    nvgCreateFont(_context, "sans", "/usr/share/fonts/TTF/DejaVuSans.ttf");

    Resize(_width, _height);
}

Window::~Window() {
    if (_window) {
        glfwDestroyWindow(_window);
    }
}

void Window::AddToolbarItem(ToolbarItem *item)  {
    _toolbar.AddItem(item);
}

bool Window::IsClosed() const {
    return glfwWindowShouldClose(_window);
}

void Window::Close() const {
    glfwSetWindowShouldClose(_window, true);
}

void Window::Resize(int new_width, int new_height) {
    _width = new_width;
    _height = new_height;
    glViewport(0, 0, new_width, new_height);

    _toolbar.Width(static_cast<float>(_width));

    std::cout << "Resized window: (" << new_width << "," << new_height << ")\n";
}

void Window::HandleKeyEvent(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F4 && mods == GLFW_MOD_ALT && action == GLFW_PRESS) {
        Close();
    }
    for (auto& key_binding: _key_bindings) {
        if (key == key_binding.key && action == key_binding.action && mods == key_binding.mods) {
            key_binding.callback();
        }
    }
}

void Window::HandleMouseClick(int button, int action, int mods) {
    auto [x, y] = GetMousePos();
    if (_popup_menu && x >= _popup_menu_pos_x && x <= _popup_menu_pos_x + _popup_menu->Width() && y >= _popup_menu_pos_y && y <= _popup_menu_pos_y + _popup_menu->Height()){
        _popup_menu->HandleMouseClick(button, action, mods, x - _popup_menu_pos_x, y - _popup_menu_pos_y);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
            _popup_menu = nullptr;
        }
    }
    else {
        _popup_menu = nullptr;
        if (y <= _toolbar.Height()) {
            _toolbar.HandleMouseClick(button, action, mods, x, y);
        }
        else {
            _scene->HandleMouseClick(button, action, mods, x, y);
        }
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        ClearMouseDown();
    }
}

std::pair<float, float> Window::GetMousePos() {
    double x;
    double y;
    glfwGetCursorPos(_window, &x, &y);
    return {x, y};
}

void Window::SetBackgroundColor(const Colour& colour) {
    glClearColor(colour.Red(), colour.Green(), colour.Blue(), colour.Alpha());
}

void Window::SetScene(ndg::common::Scene *scene) {
    _scene = scene;
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    auto w = static_cast<float>(_width);
    auto h = static_cast<float>(_height);

    nvgBeginFrame(_context, w, h, 1);

    if (_scene != nullptr) {
        auto time = glfwGetTime();
        float top = 0;
        if (_toolbar.Visible()) {
            top = _toolbar.Height();
            h -= top;
        }
        _scene->Draw(_context, 0, top, w, h, time);
    }

    if (_toolbar.Visible()) {
        _toolbar.Draw(_context, 0, 0);
    }

    if (_popup_menu) {
        _popup_menu->Draw(_context, _popup_menu_pos_x, _popup_menu_pos_y);
    }

    nvgEndFrame(_context);

    glfwSwapBuffers(_window);
}

void Window::ShowPopupMenu(ndg::common::Menu *menu, float x, float y) {
    _popup_menu = menu;
    _popup_menu_pos_x = x;
    _popup_menu_pos_y = y;
}

void Window::AddKeyBinding(int key, int action, int mods, const std::function<void()>& callback) {
    _key_bindings.emplace_back(key, action, mods, callback);
}