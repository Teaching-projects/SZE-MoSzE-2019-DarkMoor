all: Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	g++ -std=c++11 -std=c++0x -o bin Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	
clean:
	rm -f Terminal/*.o