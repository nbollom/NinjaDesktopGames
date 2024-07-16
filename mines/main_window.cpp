//
// Created by nbollom on 16/07/24.
//

#include "main_window.hpp"

using namespace ndg::mines;

MainWindow::MainWindow() : Window("Mines", 1024, 768) {
    _state.LoadState();
    if (_state.game == nullptr) {
        _scene.NewGame(_state);
    }

    SetBackgroundColor(_state.bg_colour);
    _state.window = this;

    SetScene(&_scene);

    _difficulty_menu.AddItem(std::make_unique<SelectableMenuItem>("Easy", [this](){ NewGame(Easy); }, [this](){ return IsDifficulty(Easy); }));
    _difficulty_menu.AddItem(std::make_unique<SelectableMenuItem>("Medium", [this](){ NewGame(Medium); }, [this](){ return IsDifficulty(Medium); }));
    _difficulty_menu.AddItem(std::make_unique<SelectableMenuItem>("Hard", [this](){ NewGame(Hard); }, [this](){ return IsDifficulty(Hard); }));
    _difficulty_menu.AddItem(std::make_unique<SelectableMenuItem>("Impossible", [this](){ NewGame(Impossible); }, [this](){ return IsDifficulty(Impossible); }));
    _difficulty_menu.AddItem(std::make_unique<SelectableMenuItem>("Custom", [this](){ NewGame(Custom); }, [this](){ return IsDifficulty(Custom); }));

    _toolbar.AddItem(std::make_unique<ToolbarButton>("New", [this](){ _scene.NewGame(_state); }));
    _toolbar.AddItem(std::make_unique<ToolbarButton>("Difficulty", [this](){
        auto [x, y] = GetMousePos();
        ShowPopupMenu(&_difficulty_menu, x, y);
    }));

    _status_bar.AddItem(std::make_unique<StatusBarItem>([this](){ return _scene.GetGameState(); }));
    _status_bar.AddItem(std::make_unique<StatusBarItem>([this](){ return _scene.GetMinesCount(); }));

    AddKeyBinding(GLFW_KEY_N, GLFW_PRESS, GLFW_MOD_CONTROL, [this](){ _scene.NewGame(_state); });
}

MainWindow::~MainWindow() {
    _state.SaveState();
}

void MainWindow::NewGame(Difficulty difficulty) {
    if (_state.difficulty != difficulty || difficulty == Custom) {
        if (difficulty == Custom) {
            // TODO: Custom difficulty window
        }
        else {
            _state.difficulty = difficulty;
            _scene.NewGame(_state);
        }
    }
}

bool MainWindow::IsDifficulty(Difficulty difficulty) {
    return _state.difficulty == difficulty;
}
