.PHONY: all clean

CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lcrypto++

all: encrypt decrypt

encrypt: encrypt.cpp
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

decrypt: decrypt.cpp
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f encrypt decrypt *.hex encrypted.bin decrypted.txt original.txt

test:
	echo "This is a test file for encrypting/decrypting program" > original.txt
	./encrypt
	./decrypt
	diff original.txt decrypted.txt && echo "SUCCESS" || echo "FAIL"
