.PHONY: clean transposer test

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
SRC_DIR := src
TEST_DIR := test

GTEST_DIR := googletest
LIBGTEST := $(OBJ_DIR)/libgtest.a
GTEST_MAIN := $(GTEST_DIR)/src/gtest_main.cc

CFLAGS := -g -std=c++11 -pedantic -Wall -Wextra
LD_FLAGS := -lboost_regex
TEST_CFLAGS := $(CFLAGS) -isystem $(GTEST_DIR)/include -pthread
TEST_LDFLAGS := $(LD_FLAGS)

transposer: $(BIN_DIR)/transposer

test: $(BIN_DIR)/test

$(BIN_DIR)/transposer: $(SRC_DIR)/*.cpp | $(BIN_DIR)
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $^


# TESTS
$(BIN_DIR)/test: $(GTEST_MAIN) $(TEST_DIR)/*.cpp $(LIBGTEST) | $(BIN_DIR)
	g++ $(TEST_CFLAGS) $(TEST_LDFLAGS) $^ -o $@

$(OBJ_DIR)/gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc | $(OBJ_DIR)
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $^ -o $@

$(LIBGTEST): $(OBJ_DIR)/gtest-all.o
	ar -rv $@ $^


$(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
