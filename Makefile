CXXFLAGS=-O2 -std=c++11 -std=c++0x

Terminal: Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	g++ $(CXXFLAGS) -o bin.out Terminal/Base.o Terminal/CD.o Terminal/Terminal.o Terminal/Directory.o Terminal/LS.o Terminal/main.o Terminal/MKDir.o
	
Base.o: Base.cpp
	g++ -c Terminal/Base.cpp $(CXXFLAGS)
	
CD.o: CD.cpp
	g++ -c Terminal/CD.cpp $(CXXFLAGS)
	
Terminal.o: Terminal.cpp
	g++ -c Terminal/Terminal.cpp $(CXXFLAGS)
	
Directory.o: Directory.cpp
	g++ -c Terminal/Directory.cpp $(CXXFLAGS)
	
LS.o: LS.cpp
	g++ -c Terminal/LS.cpp $(CXXFLAGS)
	
MKDir.o: MKDir.cpp
	g++ -c Terminal/MKDir.cpp $(CXXFLAGS)
	
main.o: main.cpp
	g++ -c Terminal/main.cpp $(CXXFLAGS)
	
clean:
	rm -f Terminal/*.o