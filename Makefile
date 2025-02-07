CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -L raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/mizoview

$(TARGET): main.c
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: run clean
