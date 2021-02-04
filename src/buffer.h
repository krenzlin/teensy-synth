#include <stddef.h>
#include <array>


template<typename T, size_t N>
struct Buffer {
    size_t read_ix {0};
    size_t write_ix {0};
    std::array<T, N+1> values {};
    T default_value {};

    inline bool empty() {
        return write_ix == read_ix;
    }

    inline bool full() {
        return advance(write_ix) == read_ix;
    }

    inline size_t capacity() {
        return N;
    }

    inline size_t advance(const size_t ix) {
        return (ix + 1) % (capacity() + 1);
    }

    bool write(const T value) {
        if (full()) {
            return false;
        }

        values[write_ix] = value;
        write_ix = advance(write_ix);
        return true;
    }

    T read() {
        if (empty()) {
            return default_value;
        }

        T value = values[read_ix];
        read_ix = advance(read_ix);
        return value;
    }
};
