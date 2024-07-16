//
// Created by nbollom on 12/02/24.
//

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanovg.h>
#pragma GCC diagnostic pop

namespace ndg::common {

    class Colour {

    private:
        float _data[4];

    public:
        Colour(float red, float green, float blue, float alpha);

        [[nodiscard]] float Red() const;
        [[nodiscard]] float Green() const;
        [[nodiscard]] float Blue() const;
        [[nodiscard]] float Alpha() const;

        [[nodiscard]] float* GetDataRef();
        [[nodiscard]] NVGcolor ToNVGColor() const;

        void Red(float value);
        void Green(float value);
        void Blue(float value);
        void Alpha(float value);

    };

    namespace Colours {

        const Colour Black {0.0f, 0.0f, 0.0f, 1.0f};
        const Colour White {1.0f, 1.0f, 1.0f, 1.0f};
        const Colour Red {1.0f, 0.0f, 0.0f, 1.0f};
        const Colour Lime {0.0f, 1.0f, 0.0f, 1.0f};
        const Colour Blue {0.0f, 0.0f, 1.0f, 1.0f};
        const Colour Yellow {1.0f, 1.0f, 0.0f, 1.0f};
        const Colour Cyan {0.0f, 1.0f, 1.0f, 1.0f};
        const Colour Aqua = Cyan;
        const Colour Magenta {1.0f, 0.0f, 1.0f, 1.0f};
        const Colour Fuchsia = Magenta;
        const Colour Silver {0.75f, 0.75f, 0.75f, 1.0f};
        const Colour Gray {0.5f, 0.5f, 0.5f, 1.0f};
        const Colour Maroon {0.5f, 0.0f, 0.0f, 1.0f};
        const Colour Olive {0.5f, 0.5f, 0.0f, 1.0f};
        const Colour Green {0.0f, 0.5f, 0.0f, 1.0f};
        const Colour Purple {0.5f, 0.0f, 0.5f, 1.0f};
        const Colour Teal {0.0f, 0.5f, 0.5f, 1.0f};
        const Colour Navy {0.0f, 0.0f, 0.5f, 1.0f};
    }
}