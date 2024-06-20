//
// Created by nbollom on 13/02/24.
//

#include "game.hpp"
#include <random>
#include <ranges>
#include <iostream>

using namespace ndg::mines;

Game::Game(int width, int height, int mines) : _width(width), _height(height), _mines(mines), _state(InProgress) {
    auto cell_count = width * height;

    // Populate cells with blank values
    _cells.resize(cell_count);

    // Assign mines
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(0, cell_count);
    int mine_count = 0;
    while (mine_count < mines) {
        auto val = dist(gen);
        if (!_cells[val].is_mine) {
            _cells[val].is_mine = true;
            mine_count++;
        }
    }

    // Calculate numbers of neighbouring mines
    for (auto [index, cell]: std::ranges::views::enumerate(_cells)) {
        // Ignore mines
        if (cell.is_mine) {
            continue;
        }

        auto row = index / width;
        auto col = index % width;

        // Top left
        if (row > 0 && col > 0 && _cells[index - width - 1].is_mine) {
            cell.number++;
        }

        // Top
        if (row > 0 && _cells[index - width].is_mine) {
            cell.number++;
        }

        // Top right
        if (row > 0 && col < width - 1 && _cells[index - width + 1].is_mine) {
            cell.number++;
        }

        // Left
        if (col > 0 && _cells[index - 1].is_mine) {
            cell.number++;
        }

        // Right
        if (col < width - 1 && _cells[index + 1].is_mine) {
            cell.number++;
        }

        // Bottom Left
        if (row < height - 1 && col > 0 && _cells[index + width - 1].is_mine) {
            cell.number++;
        }

        // Bottom
        if (row < height - 1 && _cells[index + width].is_mine) {
            cell.number++;
        }

        // Bottom Right
        if (row < height - 1 && col < width - 1 && _cells[index + width + 1].is_mine) {
            cell.number++;
        }
    }
}

void Game::Draw(NVGcontext *context, float x, float y, float width, float height) {
    float cell_size = std::min(width / _width, height / _height);
    float grid_width = cell_size * _width;
    float grid_height = cell_size * _height;
    float start_x = (width - grid_width) / 2 + x;
    float start_y = (height - grid_height) / 2 + y;

    for (int cell_y = 0; cell_y < _height; ++cell_y) {
        for (int cell_x = 0; cell_x < _width; ++cell_x) {
            _cells[cell_y * _width + cell_x].Draw(context, start_x + cell_x * cell_size, start_y + cell_y * cell_size, cell_size, cell_size, _state != InProgress);
        }
    }
}

Game *Game::New(State &state) {
    switch (state.difficulty) {
        case Easy:
            return new Game(10, 10, 10);
        case Medium:
            return new Game(20, 10, 30);
        case Hard:
            return new Game(30, 18, 100);
        case Impossible:
            return new Game(60, 36, 540);
        case Custom:
            return new Game(state.custom_width, state.custom_height, state.custom_mines);
    }
    return nullptr;
}

void Game::HandleMouseClick(int button, int action, int mods, float x, float y) {
    if (action != GLFW_RELEASE || _state != InProgress) {
        return;
    }
    for (auto [index, cell]: std::ranges::views::enumerate(_cells)) {
        auto [x1, x2, y1, y2] = cell.last_pos;
        if (x1 <= x && x2 >= x && y1 <= y && y2 >= y) {
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                if (!cell.is_revealed && !cell.is_flagged) {
                    cell.is_revealed = true;
                    if (cell.is_mine) {
                        _state = Lost;
                        RevealMines();
                    }
                    else {
                        if (cell.number == 0) {
                            auto [cell_y, cell_x] = std::div(static_cast<int>(index), static_cast<int>(_width));
                            RevealCells(cell_x, cell_y);
                        }

                        CheckWin();
                    }
                }
                else if (cell.is_revealed){
                    auto [cell_y, cell_x] = std::div(static_cast<int>(index), static_cast<int>(_width));
                    RevealCells(cell_x, cell_y);

                    CheckWin();
                }
            }
            else if (button == GLFW_MOUSE_BUTTON_RIGHT && !cell.is_revealed) {
                cell.is_flagged = !cell.is_flagged;
            }

            break;
        }
    }
}

int Game::CountFlaggedNeighbours(int x, int y) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i >= 0 && i < _height && j >= 0 && j < _width && _cells[i * _width + j].is_flagged) {
                count++;
            }
        }
    }
    return count;
}

void Game::RevealCells(int x, int y) {
    auto &cell = _cells[y * _width + x];
    if (cell.is_mine) {
        return;
    }
    else if (cell.number == 0 || cell.number == CountFlaggedNeighbours(x, y)) {
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i < 0 || i >= _height || j < 0 || j >= _width) {
                    continue;
                }

                auto &c = _cells[i * _width + j];
                if (c.is_revealed || c.is_flagged) {
                    continue;
                }

                c.is_revealed = true;

                if (c.is_mine) {
                    _state = Lost;
                    RevealMines();
                }

                RevealCells(j, i);
            }
        }
    }
}

void Game::CheckWin() {
    int count = 0;
    for (auto &c: _cells) {
        if (c.is_revealed || c.is_mine) {
            count++;
        }
    }
    if (count == _width * _height) {
        _state = Won;
        for (auto &c: _cells) {
            if (c.is_mine) {
                c.is_flagged = true;
            }
        }
    }
}

void Game::RevealMines() {
    for (auto &c: _cells) {
        if (c.is_mine && !c.is_flagged) {
            c.is_revealed = true;
        }
    }
}