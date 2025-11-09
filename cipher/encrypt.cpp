#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
using namespace std;
using namespace CryptoPP;

int main() {
    try {
        AutoSeededRandomPool rng;
        byte key[AES::DEFAULT_KEYLENGTH];
        rng.GenerateBlock(key, sizeof(key));

        byte iv[AES::BLOCKSIZE];
        rng.GenerateBlock(iv, sizeof(iv));
        cout << "Сгенерирован ключ и IV" << endl;

        string key_hex, iv_hex;
        StringSource(key, sizeof(key), true,
            new HexEncoder(
                new StringSink(key_hex)));
        StringSource(iv, sizeof(iv), true,
            new HexEncoder(
                new StringSink(iv_hex)));
        StringSource(key_hex, true, new FileSink("key.hex"));
        StringSource(iv_hex, true, new FileSink("iv.hex"));
        cout << "Ключ был сохранен в key.hex" << endl;
        cout << "IV был сохранен в iv.hex" << endl;

        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, sizeof(key), iv);
        FileSource("original.txt", true,
            new StreamTransformationFilter(encryptor,
                new FileSink("encrypted.bin")));
        cout << "Файл original.txt был зашифрован в encrypted.bin" << endl;
    } catch(const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
