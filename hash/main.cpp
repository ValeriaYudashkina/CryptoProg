#include <iostream>
#include <string>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>

using namespace std;
using namespace CryptoPP;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Использование программы " << argv[0] << " (имя_файла)" << endl;
        cout << "Программа вычисляет SHA-256 хэш указанного файла" << endl;
        return 1;
    }
    string filename = argv[1];
    string digest;
    try {
        SHA256 hash;
        FileSource(filename.c_str(), true,
                  new HashFilter(hash,
                               new HexEncoder(
                               new StringSink(digest))));
        cout << digest << endl;
    } catch(const Exception& e) {
        cerr << "Ошибка Crypto++: " << e.what() << endl;
        return 1;
    } catch(const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
