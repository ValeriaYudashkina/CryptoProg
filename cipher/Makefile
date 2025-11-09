.PHONY: all clean

CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lcrypto++ -lpthread

all: encrypt decrypt

encrypt: encrypt.cpp
	$(CXX) $(CXXFLAGS) -o encrypt encrypt.cpp $(LIBS)

decrypt: decrypt.cpp
	$(CXX) $(CXXFLAGS) -o decrypt decrypt.cpp $(LIBS)

clean:
	rm -f encrypt decrypt *.hex encrypted.bin decrypted.txt original.txt
