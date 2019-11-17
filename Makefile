all: Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	g++ -o bin Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	
Base.o: Base.cpp
	g++ -c Terminal/Base.cpp  -std=c++11
	
CD.o: CD.cpp
	g++ -c Terminal/CD.cpp -std=c++11
	
Terminal.o: Terminal.cpp
	g++ -c Terminal/Terminal.cpp -std=c++11
	
Directory.o: Directory.cpp
	g++ -c Terminal/Directory.cpp -std=c++11
	
LS.o: LS.cpp
	g++ -c Terminal/LS.cpp -std=c++11
	
MKDir.o: MKDir.cpp
	g++ -c Terminal/MKDir.cpp -std=c++11
	
main.o: main.cpp
	g++ -c Terminal/main.cpp -std=c++11
	
clean:
	rm -f Terminal/*.o