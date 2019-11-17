all: Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	g++ -o bin Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	
Base.o: Base.cpp
	g++ -c Terminal/Base.cpp
	
CD.o: CD.cpp
	g++ -c Terminal/CD.cpp
	
Terminal.o: Terminal.cpp
	g++ -c Terminal/Terminal.cpp
	
Directory.o: Directory.cpp
	g++ -c Terminal/Directory.cpp
	
LS.o: LS.cpp
	g++ -c Terminal/LS.cpp
	
MKDir.o: MKDir.cpp
	g++ -c Terminal/MKDir.cpp
	
main.o: main.cpp
	g++ -c Terminal/main.cpp
	
clean:
	rm -f Terminal/*.o