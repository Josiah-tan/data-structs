SRC_DIR := .
OBJ_DIR := include
IN_DIR := in
OUT_DIR := out
CMP_DIR := cmp

CC := g++
EXE := ./output
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CMP := $(sort $(wildcard $(CMP_DIR)/*.txt))
IN := $(CMP:$(CMP_DIR)/%.txt=$(IN_DIR)/%.txt)
OUT := $(CMP:$(CMP_DIR)/%.txt=$(OUT_DIR)/%.txt)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall -fsanitize=address -g
LDFLAGS  := -Llib -fsanitize=address
LDLIBS   := -lm

.PHONY: all clean compare test stress

stress: $(EXE)
	$(EXE)

compare: test
	diff -r --ignore-trailing-space $(CMP_DIR) $(OUT_DIR)

test: $(OUT) $(EXE)

$(OUT_DIR)/%.txt: $(IN_DIR)/%.txt $(EXE) | $(OUT_DIR)
	cat $< | $(EXE) > $@
	
all: $(EXE)

# if anything in the object directory changes, then 
$(EXE): $(OBJ)
		$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# how to make anything in the object directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(OUT_DIR):
	mkdir -p $@

clean:
		@$(RM) -rv $(OBJ_DIR) $(EXE)
		@$(RM) -rv $(OUT_DIR)

-include $(OBJ:.o=.d)
