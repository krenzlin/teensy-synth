#include "doctest.h"
#include <stdint.h>
#include "buffer.h"

// following ZOMBIES method
// c.f. http://blog.wingman-sw.com/tdd-guided-by-zombies


TEST_CASE("buffer is empty and not full after creation") {
    Buffer<int32_t, 3> buffer;

    REQUIRE(buffer.empty());
    REQUIRE(!buffer.full());
}

TEST_CASE("buffer is not empty after write") {
    Buffer<int32_t, 3> buffer;

    buffer.write(1);

    REQUIRE(!buffer.empty());
}

TEST_CASE("buffer is empty after write and read") {
    Buffer<int32_t, 3> buffer;

    buffer.write(1);
    buffer.read();

    REQUIRE(buffer.empty());
}

TEST_CASE("buffer read equals write") {
    Buffer<int32_t, 3> buffer;

    buffer.write(1);
    REQUIRE(buffer.read() == 1);
}

TEST_CASE("buffer works as FIFO") {
    Buffer<int32_t, 3> buffer;

    buffer.write(41);
    buffer.write(42);
    buffer.write(43);

    REQUIRE(buffer.read() == 41);
    REQUIRE(buffer.read() == 42);
    REQUIRE(buffer.read() == 43);
}

TEST_CASE("buffer can have different capacities") {
    Buffer<int32_t, 1> buffer1;

    REQUIRE(buffer1.capacity() == 1);

    Buffer<int32_t, 10> buffer2;

    REQUIRE(buffer2.capacity() == 10);
}

TEST_CASE("buffer is full after writing capacity times") {
    Buffer<int32_t, 10> buffer;

    for (size_t i=0; i<buffer.capacity(); i++) {
        buffer.write(i);
    }

    REQUIRE(buffer.full());
}

TEST_CASE("buffer is not full after read from full buffer") {
    Buffer<int32_t, 10> buffer;

    for (size_t i=0; i<buffer.capacity(); i++) {
        buffer.write(i);
    }

    buffer.read();

    REQUIRE(!buffer.full());
}

TEST_CASE("buffer force wraparound") {
    Buffer<int32_t, 2> buffer;

    buffer.write(1);
    buffer.write(2);
    buffer.read();
    buffer.write(3);

    REQUIRE(buffer.read() == 2);
    REQUIRE(buffer.read() == 3);
    REQUIRE(buffer.empty());
}

TEST_CASE("buffer is full after wraparound") {
    Buffer<int32_t, 2> buffer;

    buffer.write(1);
    buffer.write(2);
    buffer.read();
    buffer.write(3);

    REQUIRE(buffer.full());
}

TEST_CASE("write fails when putting to full buffer") {
    Buffer<int32_t, 1> buffer;

    buffer.write(1);
    REQUIRE(!buffer.write(2));
}

TEST_CASE("read returns default when reading from empty buffer") {
    Buffer<int32_t, 1> buffer;

    REQUIRE(buffer.read() == buffer.default_value);
}

TEST_CASE("buffer write to full does not harm values") {
    Buffer<int32_t, 1> buffer;

    buffer.write(41);
    REQUIRE(!buffer.write(42));
    REQUIRE(buffer.read() == 41);
    REQUIRE(buffer.empty());
}

TEST_CASE("buffer read from empty does no harm") {
    Buffer<int32_t, 1> buffer;

    buffer.read();
    REQUIRE(buffer.empty());
    REQUIRE(!buffer.full());

    buffer.write(42);
    REQUIRE(buffer.full());
    REQUIRE(!buffer.empty());
    REQUIRE(buffer.read() == 42);
    REQUIRE(buffer.empty());
}
