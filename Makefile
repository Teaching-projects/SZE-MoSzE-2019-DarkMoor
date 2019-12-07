MKDIR_P = mkdir -p
LIB_DIR	= /usr/lib

SRC_DIR	= Terminal
TEST_SRC_DIR	= TerminalTests
SRCS = $(SRC_DIR)/*.cpp $(TEST_SRC_DIR)/*.cpp

OBJ_DIR	= obj
OBJS	= $(OBJ_DIR)/Base.o $(OBJ_DIR)/CD.o $(OBJ_DIR)/CommandBase.o $(OBJ_DIR)/Directory.o $(OBJ_DIR)/Exit.o $(OBJ_DIR)/File.o $(OBJ_DIR)/FSJsonHandler.o $(OBJ_DIR)/jsoncpp.o $(OBJ_DIR)/LS.o $(OBJ_DIR)/MKDir.o $(OBJ_DIR)/RM.o $(OBJ_DIR)/Terminal.o $(OBJ_DIR)/Touch.o $(OBJ_DIR)/Echo.o $(OBJ_DIR)/MV.o
EXECUTABLE_ONLY_OBJS	= $(OBJ_DIR)/main.o
EXECUTABLE_OBJS	= $(OBJS) $(EXECUTABLE_ONLY_OBJS)
TEST_ONLY_OBJS	= $(OBJ_DIR)/CDTest.o $(OBJ_DIR)/DirectoryTest.o $(OBJ_DIR)/MKDirTest.o $(OBJ_DIR)/MVTest.o $(OBJ_DIR)/TerminalTest.o
TEST_OBJS	= $(OBJS) $(TEST_ONLY_OBJS)

DEP = $(OBJS:%.o=%.d) $(EXECUTABLE_ONLY_OBJS:%.o=%.d) $(TEST_ONLY_OBJS:%.o=%.d)

GTEST_DIR	= /usr/src/gtest

OUT_DIR = bin
OUT	= bin.out
TEST_OUT	= bin.test

CC	 = g++

FLAGS	 = -c -std=c++11 -std=c++0x
CXXFLAGS	= -std=c++11 -std=c++0x -Wall

all: release

debug: CXXFLAGS += -g
debug: FLAGS += -g
debug: directories $(OUT_DIR)/$(OUT)

release: CXXFLAGS += -O3
release: directories $(OUT_DIR)/$(OUT)

test: CXXFLAGS += -g -pthread -Wextra
test: FLAGS += -g
test: directories $(OUT_DIR)/$(TEST_OUT)

directories: 
	@mkdir -p $(OUT_DIR) $(OBJ_DIR) $(LIB_DIR)

$(OUT_DIR)/$(OUT): $(EXECUTABLE_OBJS)
	$(CC) $^ -o $@ $(CXXFLAGS)

$(OUT_DIR)/$(TEST_OUT): $(TEST_OBJS)
	$(CC) $(CXXFLAGS) -o $@ -I$(GTEST_DIR)/include -L$(LIB_DIR) $^ $(LIB_DIR)/libgtest_main.a -lpthread -lgtest -lgtest_main

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -MMD $(FLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CC) -MMD $(FLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE_ONLY_OBJS) $(TEST_ONLY_OBJS) $(DEP)