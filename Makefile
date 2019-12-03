MKDIR_P = mkdir -p
LIB_DIR	= /usr/lib

SRC_DIR	= Terminal
SRCS = $(SRC_DIR)/*.cpp

OBJ_DIR	= obj
OBJS	= $(OBJ_DIR)/Base.o $(OBJ_DIR)/CD.o $(OBJ_DIR)/CommandBase.o $(OBJ_DIR)/Directory.o $(OBJ_DIR)/Exit.o $(OBJ_DIR)/File.o $(OBJ_DIR)/FSJsonHandler.o $(OBJ_DIR)/jsoncpp.o $(OBJ_DIR)/LS.o $(OBJ_DIR)/MKDir.o $(OBJ_DIR)/RM.o $(OBJ_DIR)/Terminal.o $(OBJ_DIR)/Touch.o $(OBJ_DIR)/Echo.o
EXECUTABLE_OBJS	=  $(OBJ_DIR)/main.o

DEP = $(OBJS:%.o=%.d) $(EXECUTABLE_OBJS:%.o=%.d)

GTEST_DIR	= /usr/src/gtest

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

directories: 
	@mkdir -p $(OUT_DIR) $(OBJ_DIR) $(LIB_DIR)

executable: $(OBJS) $(EXECUTABLE_OBJS)
	mkdir -p $(@D)
	$(CC) $(OBJS) $(EXECUTABLE_OBJS) -o $(OUT_DIR)/$(OUT) $(CXXFLAGS)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -MMD $(FLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE_OBJS) $(DEP)