#include <window.hpp>
#include <toolbar_button.hpp>
#include <iostream>
#include "state.hpp"
#include "game_scene.hpp"
#include "game.hpp"
using namespace ndg::common;
using namespace ndg::mines;

int main() {
    State state;
    state.LoadState();

    if (state.game == nullptr) {
        state.game = Game::New(state);
    }

    Window window {"Mines", 800, 600};
    window.SetBackgroundColor(state.bg_colour);
    state.window = &window;

    GameScene scene;
    window.SetScene(&scene);

    Menu difficulty_menu;

    SelectableMenuItem difficulty_easy = {
            "Easy",
            [&state, &scene](){
                if (state.difficulty != Easy) {
                    state.difficulty = Easy;
                    scene.NewGame(state);
                }
            },
            [&state](){
                return state.difficulty == Easy;
            }
    };

    SelectableMenuItem difficulty_medium = {
            "Medium",
            [&state, &scene](){
                if (state.difficulty != Medium) {
                    state.difficulty = Medium;
                    scene.NewGame(state);
                }
            },
            [&state](){
                return state.difficulty == Medium;
            }
    };

    SelectableMenuItem difficulty_hard = {
            "Hard",
            [&state, &scene](){
                if (state.difficulty != Hard) {
                    state.difficulty = Hard;
                    scene.NewGame(state);
                }
            },
            [&state](){
                return state.difficulty == Hard;
            }
    };

    SelectableMenuItem difficulty_impossible = {
            "Impossible",
            [&state, &scene](){
                if (state.difficulty != Impossible) {
                    state.difficulty = Impossible;
                    scene.NewGame(state);
                }
            },
            [&state](){
                return state.difficulty == Impossible;
            }
    };

    SelectableMenuItem difficulty_custom = {
            "Custom",
            [&state, &scene](){
                // TODO: Show custom dialog
            },
            [&state](){
                return state.difficulty == Custom;
            }
    };

    difficulty_menu.AddItem(&difficulty_easy);
    difficulty_menu.AddItem(&difficulty_medium);
    difficulty_menu.AddItem(&difficulty_hard);
    difficulty_menu.AddItem(&difficulty_impossible);
    difficulty_menu.AddItem(&difficulty_custom);

    ToolbarButton new_game = {"New", [&scene, &state](){
        scene.NewGame(state);
    }};

    window.AddToolbarItem(&new_game);

    ToolbarButton change_difficulty = {"Difficulty", [&window, &difficulty_menu](){
        auto [x, y] = window.GetMousePos();
        window.ShowPopupMenu(&difficulty_menu, x, y);
    }};

    window.AddToolbarItem(&change_difficulty);

    window.AddKeyBinding(GLFW_KEY_N, GLFW_PRESS, GLFW_MOD_CONTROL, [&scene, &state](){
        scene.NewGame(state);
    });

    scene.NewGame(state);

    while (!window.IsClosed()) {
        window.PollEvents();
        window.Draw();
    }

    state.SaveState();

    return 0;
}
