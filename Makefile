# Compiler
CXX = g++

# Add the Python include path here
# Find path by python3-config --include
CXXFLAGS = -Wall -std=c++11 -I/usr/include/python3.8    # Add necessary flags for Python and Matplotlib
PYFLAGS = -lpython3.8

# Targets
all: app 

app: main.o Request.o MyRequest.o
	$(CXX) $(CXXFLAGS) main.o Request.o MyRequest.o -o app $(PYFLAGS)

main.o: main.cpp MyRequest.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Request.o: Request.cpp Request.hpp
	$(CXX) $(CXXFLAGS) -c Request.cpp -o Request.o

MyRequest.o: MyRequest.cpp MyRequest.hpp Request.hpp
	$(CXX) $(CXXFLAGS) -c MyRequest.cpp -o MyRequest.o

test: test.cpp MyRequest.o Request.o
	g++ $(CXXFLAGS) -Wall -c test.cpp -o test.o
	g++ $(CXXFLAGS) -Wall -o tests test.o Request.o MyRequest.o $(PYFLAGS)
	./tests

.PHONY: clean
clean:
	rm -f *.o app tests
