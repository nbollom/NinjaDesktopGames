//
// Created by nbollom on 12/02/24.
//

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop

namespace ndg::common {

    class Scene {
        /*
         * A Scene is used for nanovg drawing stuff
         */

    public:
        virtual ~Scene() = default;

        virtual void Draw(NVGcontext *context, float x, float y, float width, float height, double time) = 0;
        virtual void HandleKeyEvent(int key, int scancode, int action, int mods) = 0;
        virtual void HandleMouseClick(int button, int action, int mods, float x, float y) = 0;
    };

}