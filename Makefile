CC      := gcc
CFLAGS  := -std=c17 -Wall -Wextra -Wpedantic -Iinclude -MMD -MP
LDFLAGS := -lm

SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin
TARGET    := $(BIN_DIR)/subnet

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all debug release run clean

all: $(TARGET)

debug: clean
	$(MAKE) CFLAGS="$(CFLAGS) -g -O0 -fsanitize=address,undefined" \
	        LDFLAGS="$(LDFLAGS) -fsanitize=address,undefined" all

release: clean
	$(MAKE) CFLAGS="$(CFLAGS) -O2 -DNDEBUG" all

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)/*

-include $(DEPS)
