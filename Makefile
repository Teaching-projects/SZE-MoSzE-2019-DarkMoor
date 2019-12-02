MKDIR_P = mkdir -p
LIB_DIR	= /usr/lib
LIBS	=
TEST_LIBS	= $(LIB_DIR)/gtest.a $(LIB_DIR)/gtest_main.a

SRC_DIR	= Terminal
TEST_SRC_DIR	= TerminalTests

OBJ_DIR	= obj
OBJS	= $(OBJ_DIR)/Base.o $(OBJ_DIR)/CD.o $(OBJ_DIR)/CommandBase.o $(OBJ_DIR)/Directory.o $(OBJ_DIR)/Exit.o $(OBJ_DIR)/File.o $(OBJ_DIR)/FSJsonHandler.o $(OBJ_DIR)/jsoncpp.o $(OBJ_DIR)/LS.o $(OBJ_DIR)/MKDir.o $(OBJ_DIR)/RM.o $(OBJ_DIR)/Terminal.o $(OBJ_DIR)/Touch.o $(OBJ_DIR)/Echo.o $(OBJ_DIR)/MV.o
EXECUTABLE_OBJS	=  $(OBJ_DIR)/main.o
TEST_OBJS	= $(OBJ_DIR)/test.o  $(OBJ_DIR)/CDTest.o  $(OBJ_DIR)/DirectoryTest.o  $(OBJ_DIR)/MVTest.o  $(OBJ_DIR)/TerminalTests.o
GTEST_OBJS = $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest-main.o

GTEST_DIR	= /usr/src/gtest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h  $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

OUT_DIR = bin
OUT	= bin.out

CC	 = g++

FLAGS	 = -c -std=c++11 -std=c++0x
CXXFLAGS	= -std=c++11 -std=c++0x -Wall

all: release

debug: CXXFLAGS += -g
debug: FLAGS += -g
debug: directories executable

release: CXXFLAGS += -O3
release: directories executable

test: CXXFLAGS += -g -pthread -Wextra
test: FLAGS += -g
test: OUT := bin.test
test: directories testexecutable

directories: 
	@mkdir -p $(OUT_DIR) $(OBJ_DIR) $(LIB_DIR)

testexecutable: $(OBJS) $(TEST_OBJS)
	$(CC) $(CXXFLAGS) -o $(OUT_DIR)/$(OUT) -I$(GTEST_DIR)/include -L$(LIB_DIR) $^ $(LIB_DIR)/libgtest_main.a -lpthread -lgtest -lgtest_main 

executable: $(OBJS) $(EXECUTABLE_OBJS)
	$(CC) $(OBJS) $(EXECUTABLE_OBJS) -o $(OUT_DIR)/$(OUT) $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(GTEST_SRCS)
	$(CC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c -o $@ $(GTEST_DIR)/src/gtest-all.cc

$(OBJ_DIR)/%.o : $(GTEST_SRCS)
	$(CC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c -o $@ $(GTEST_DIR)/src/gtest_main.cc

$(LIB_DIR)/gtest.a : $(OBJ_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(LIB_DIR)/gtest_main.a : $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(EXECUTABLE_OBJS) $(TEST_OBJS) $(GTEST_OBJS)
