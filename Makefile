OBJS	= Terminal/main.o Terminal/Base.o Terminal/CD.o Terminal/CommandBase.o Terminal/Directory.o Terminal/Exit.o Terminal/File.o Terminal/FSJsonHandler.o Terminal/jsoncpp.o Terminal/LS.o Terminal/MKDir.o Terminal/RM.o Terminal/Terminal.o Terminal/Touch.o Terminal/Echo.o Terminal/MV.o
SOURCE	= Terminal/main.cpp, Terminal/Base.cpp, Terminal/CD.cpp, Terminal/CommandBase.cpp, Terminal/Directory.cpp, Terminal/Exit.cpp, Terminal/File.cpp, Terminal/FSJsonHandler.cpp, Terminal/jsoncpp.cpp, Terminal/LS.cpp, Terminal/MKDir.cpp, Terminal/RM.cpp, Terminal/Terminal.cpp, Terminal/Touch.cpp, Terminal/Echo.cpp Terminal/MV.cpp
HEADER	= Terminal/Base.h, Terminal/CD.h, Terminal/CommandBase.h, Terminal/Directory.h, Terminal/Exit.h, Terminal/File.h, Terminal/FSJsonHandler.h, Terminal/json\json-forwards.h, Terminal/json\json.h, Terminal/LS.h, Terminal/MKDir.h, Terminal/RM.h, Terminal/Terminal.h, Terminal/Touch.h, Terminal/Echo.h Terminal/MV.h
OUT	= bin.out
CC	 = g++
FLAGS	 = -g -c -Wall -O2 -std=c++11 -std=c++0x
CXXFLAGS	 = -std=c++11 -std=c++0x -Wall -O2

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(CXXFLAGS)

release: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(CXXFLAGS)

main.o: main.cpp,
	$(CC) $(FLAGS) Terminal/main.cpp,

Base.o: Base.cpp,
	$(CC) $(FLAGS) Terminal/Base.cpp,

CD.o: CD.cpp,
	$(CC) $(FLAGS) Terminal/CD.cpp,

CommandBase.o: CommandBase.cpp,
	$(CC) $(FLAGS) Terminal/CommandBase.cpp,

Directory.o: Directory.cpp,
	$(CC) $(FLAGS) Terminal/Directory.cpp,

Exit.o: Exit.cpp,
	$(CC) $(FLAGS) Terminal/Exit.cpp,

File.o: File.cpp,
	$(CC) $(FLAGS) Terminal/File.cpp,

FSJsonHandler.o: FSJsonHandler.cpp,
	$(CC) $(FLAGS) Terminal/FSJsonHandler.cpp,

jsoncpp.o: jsoncpp.cpp,
	$(CC) $(FLAGS) Terminal/jsoncpp.cpp,

LS.o: LS.cpp,
	$(CC) $(FLAGS) Terminal/LS.cpp,

MKDir.o: MKDir.cpp,
	$(CC) $(FLAGS) Terminal/MKDir.cpp,

RM.o: RM.cpp,
	$(CC) $(FLAGS) Terminal/RM.cpp,

Terminal.o: Terminal.cpp,
	$(CC) $(FLAGS) Terminal/Terminal.cpp,

Touch.o: Touch.cpp
	$(CC) $(FLAGS) Terminal/Touch.cpp,

Echo.o: Echo.cpp
	$(CC) $(FLAGS) Terminal/Echo.cpp,

MV.o: MV.cpp
	$(CC) $(FLAGS) Terminal/MV.cpp


clean:
	rm -f $(OBJS)
