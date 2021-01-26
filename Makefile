.PHONY: all build upload test

all: build upload

clean:
	make -f teensy4.mk clean

build:
	make -f teensy4.mk build

upload: build
	make -f teensy4.mk upload

check:
	cppcheck --enable=all src/

CPP_FLAGS=-Wall -Wpedantic -Wextra -g
SAN_FLAGS=-fsanitize=address,undefined

TEST_SRC_FILES := $(wildcard src/*.cpp) $(wildcard tests/*.cpp)
TEST_SRC_FILES := $(filter-out src/main.cpp, $(TEST_SRC_FILES))
TEST_SRC_FILES := $(filter-out tests/write_to_file.cpp, $(TEST_SRC_FILES))

TEST_OBJS := $(addprefix build/host/, $(TEST_SRC_FILES:.cpp=.o))

INCLUDES = -I./src/ -I./bench/picobench/include/ -I./tests/mocks

bin/test: $(TEST_OBJS)
	@mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) $(SAN_FLAGS) $(INCLUDES) -o $@ $^

test: bin/test
	bin/test

build/host/%.o : %.cpp
	@mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) $(INCLUDES) -c $< -o $@


BENCH_SRC_FILES := $(wildcard bench/*.cpp) $(wildcard src/*.cpp)
BENCH_SRC_FILES := $(filter-out src/main.cpp, $(BENCH_SRC_FILES))
BENCH_OBJS := $(addprefix build/host/, $(BENCH_SRC_FILES:.cpp=.o))

bin/bench: $(BENCH_OBJS)
	@mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) $(SAN_FLAGS) $(INCLUDES) -o $@ $^

bench: bin/bench
	bin/bench --samples=100

WRITE_SRC_FILES := tests/write_to_file.cpp $(wildcard src/*.cpp)
WRITE_SRC_FILES := $(filter-out src/main.cpp, $(WRITE_SRC_FILES))
WRITE_OBJS := $(addprefix build/host/, $(WRITE_SRC_FILES:.cpp=.o))

bin/write: $(WRITE_OBJS)
	g++ $(CPP_FLAGS) $(INCLUDES) -o $@ $^

write: bin/write
	@mkdir -p outputs
	bin/write outputs/generated.wav
