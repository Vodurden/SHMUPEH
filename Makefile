CC := g++
LD := g++
CFLAGS := -Wall -g -rdynamic
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
EXE := $(BIN_DIR)/shmupeh

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(EXE) $(BIN_DIR)/Graphics
.PHONY: all

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) -g -rdynamic $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR)/Graphics: assets/Graphics
	rsync -rupE --delete assets/Graphics $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -MMD -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf obj bin

-include obj/*.d
