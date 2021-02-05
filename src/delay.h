#include <stddef.h>
#include <array>

template<size_t N>
inline size_t advance(const size_t ix) {
    return (ix + 1) % (N);
}

template<typename T, size_t N>
struct Delay {
    size_t ix {0};
    std::array<T, N> values {};

    inline size_t length() {
        return N;
    }

    T read() {
        return values[ix];
    }

    void write(const T value) {
        values[ix] = value;
        ix = advance<N>(ix);
    }

    T update(const T value) {
        T out = read();
        write(value);
        return out;
    }

    T update() {
        return update(0);
    }
};
