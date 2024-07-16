#include "main_window.hpp"
using namespace ndg::mines;

int main() {
    MainWindow window;

    while (!window.IsClosed()) {
        window.PollEvents();
        window.Draw();
    }

    return 0;
}
