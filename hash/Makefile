.PHONY: all clean

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = hash_program
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET) *.o
