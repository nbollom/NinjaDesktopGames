//
// Created by nbollom on 12/02/24.
//

#pragma once

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

        void Red(float value);
        void Green(float value);
        void Blue(float value);
        void Alpha(float value);

    };

}