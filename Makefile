SRC_DIR := ./src
OBJ_DIR := ./obj
LIB_DIR := ./lib
TEST_DIR := ./test
SRC_FILES := $(filter-out $(SRC_DIR)/main.cc, $(shell find $(SRC_DIR) -name "*.cc"))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
LFLAGS := -lglfw3 -ldl -lGL -lGLU -lGLEW -lX11 -lpthread
SLFLAGS = $(LIB_DIR)/stb_image.a
INCFLAGS = -I./include -I./src

main: $(SRC_DIR)/main.cc $(OBJ_FILES)
	g++ -g $(INCFLAGS) $< -o $@ $(OBJ_FILES) $(LFLAGS) $(SLFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/%.h
	@mkdir -p $(@D)
	g++ -g $(INCFLAGS) -c -o $@ $<

.PHONY : all
all: main