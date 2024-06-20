//
// Created by nbollom on 9/04/24.
//

#pragma once

namespace ndg::common {

    class Clickable {

    protected:
        bool _mouse_down = false;

    public:
        virtual ~Clickable() = default;

        [[nodiscard]] bool IsMouseDown() const {
            return _mouse_down;
        }

        void MouseDown(bool value);

        virtual void Click() = 0;

    };

    void ClearMouseDown();

}
