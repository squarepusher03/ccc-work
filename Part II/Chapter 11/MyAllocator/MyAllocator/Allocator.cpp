#define CATCH_CONFIG_MAIN
#include <new>
#include "../../../lib/catch.hpp"

static size_t n_allocated, n_deallocated;

template <typename T>
struct Allocator {
    using value_type = T;
    Allocator() noexcept {}
    
    template <typename U>
    Allocator(const Allocator<U>&) noexcept {}

    T* allocate(size_t n) {
        auto p = operator new(sizeof(T) * n);
        ++n_allocated;
        return static_cast<T*>(p);
    }

    void deallocate(T*, size_t n) {
        operator delete(p);
        ++n_deallocated;
    }
};

template <typename T1, typename T2>
bool operator==(const Allocator<T1>&, const Allocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const Allocator<T1>&, const Allocator<T2>&) {
    return false;
}