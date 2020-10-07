#pragma once

namespace kg {
    template <typename Parent> class bridge {
    public:
        bridge(Parent & parent) : _parent { parent } {}

    protected:
        Parent & _parent;
    };
}
