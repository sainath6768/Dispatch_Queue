CXX = g++
CFLAGS = -Iinclude
TARGET = build/ALU
SRC = ./src/add.cpp src/sub.cpp src/mul.cpp src/div.cpp src/dispatchqueue.cpp 
OBJ = src/add.o src/sub.o src/mul.o src/div.o src/dispatchqueue.o
INC = include/add.hpp include/sub.hpp include/mul.hpp include/div.hpp include/dispatchqueue.hpp 

all: $(TARGET)
	 
$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) src/main.cpp $(OBJ)  -o $(TARGET)

src/add.o : src/add.cpp $(INC)
	$(CXX) $(CFLAGS) -c src/add.cpp -o src/add.o 

src/sub.o : src/sub.cpp $(INC)
	$(CXX) $(CFLAGS) -c src/sub.cpp -o src/sub.o 

src/mul.o : src/mul.cpp $(INC)
	$(CXX) $(CFLAGS) -c src/mul.cpp -o src/mul.o

src/div.o : src/div.cpp $(INC)
	$(CXX) $(CFLAGS) -c src/div.cpp -o src/div.o 

src/dispatchqueue.o : src/dispatchqueue.cpp $(INC)
	$(CXX) $(CFLAGS) -c src/dispatchqueue.cpp -o src/dispatchqueue.o 

clean:
	rm -f $(OBJ)