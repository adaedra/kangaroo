#pragma once

namespace kg {
    template<typename Parent>
    class child {
    public:
        child(Parent & parent) : _parent { parent } {}

    protected:
        Parent & _parent;
    };
}
