#pragma once

namespace wx {
    template <typename T> class ptr {
    public:
        ptr(T * inner) : _inner { inner } {}
        ptr(ptr const & other) : _inner { other._inner } {}

        template <typename... Args>
        explicit ptr(Args... args) : _inner { new T(args...) } {}

        T const & operator*() const { return *_inner; }
        T & operator*() { return *_inner; }
        T const * operator->() const { return _inner; }
        T * operator->() { return _inner; }

        template <typename U> operator U() const {
            return static_cast<U>(_inner);
        }

    private:
        T * _inner;
    };
}
