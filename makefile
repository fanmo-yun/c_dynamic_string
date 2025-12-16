CC = gcc

BUILD_DIR = build
SRC_DIR   = src

TARGET = $(BUILD_DIR)/main

SRC  = $(SRC_DIR)/main.c
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(TARGET) $(OBJS)

run:
	$(TARGET)
