//
// Created by nbollom on 13/02/24.
//

#pragma once
#include <vector>
#include "cell.hpp"
#include "state.hpp"

namespace ndg::mines {

    typedef enum {
        InProgress,
        Won,
        Lost
    } GameState;

    class Game {

    private:
        std::vector<Cell> _cells;
        int _width;
        int _height;
        int _mines;
        GameState _game_state;
        State &_state;
        bool _generated = false;
        int _flagged = 0;

    public:

        Game(int width, int height, int mines, State &state);
        void Draw(NVGcontext *context, float x, float y, float width, float height);
        void HandleMouseClick(int button, int action, int mods, float x, float y);

        static Game* New(State &state);

        GameState GetGameState();
        int GetMineCount();
        int GetFlaggedCount();

    private:
        void GenerateGrid(int clicked_index);
        int CountFlaggedNeighbours(int x, int y);
        void RevealCells(int x, int y);
        void CheckWin();
        void RevealMines();

    };

}
