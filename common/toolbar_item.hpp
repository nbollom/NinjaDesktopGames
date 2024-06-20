//
// Created by nbollom on 27/02/24.
//

#pragma once
#include "drawable.hpp"

namespace ndg::common {

    class ToolbarItem: public Drawable {

    public:
        virtual bool Clickable() = 0;

    };

}
