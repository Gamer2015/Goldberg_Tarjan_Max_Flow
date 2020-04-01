CC := g++

MD := mkdir
RM := rm

OUT_FILE := out.a

OUT_DIR := obj
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,$(OUT_DIR)/%.o,$(SRC_FILES))
LDFLAGS := 
CPPFLAGS := -std=c++14

$(OUT_FILE): $(OBJ_FILES) 
	$(CC) $(LDFLAGS) -o $@ $^

$(OUT_DIR): 
	$(MD) $@ $^

$(OUT_DIR)/%.o: %.cpp $(OUT_DIR)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:  
	$(RM) -r $(OUT_DIR) $(OUT_FILE)

doc:
	# Create documentation
	doxygen

