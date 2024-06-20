//
// Created by nbollom on 25/02/24.
//

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop

namespace ndg::common {

    class Drawable {

    protected:
        float _width = 0;
        float _height = 0;

    public:
        virtual ~Drawable() = default;

        [[nodiscard]] virtual float Width() const {
            return _width;
        }

        virtual void Width(float value) {
            _width = value;
        }

        [[nodiscard]] virtual float Height() const {
            return _height;
        }

        virtual void Height(float value) {
            _height = value;
        }

        virtual void Draw(NVGcontext *context, float x, float y) = 0;


    };

}
