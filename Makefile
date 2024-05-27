# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Targets
all: app

app: main.o Request.o MyRequest.o
	$(CXX) $(CXXFLAGS) main.o Request.o MyRequest.o -o app

main.o: main.cpp MyRequest.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Request.o: Request.cpp Request.hpp
	$(CXX) $(CXXFLAGS) -c Request.cpp -o Request.o

MyRequest.o: MyRequest.cpp MyRequest.hpp Request.hpp
	$(CXX) $(CXXFLAGS) -c MyRequest.cpp -o MyRequest.o

clean:
	rm -f *.o app
