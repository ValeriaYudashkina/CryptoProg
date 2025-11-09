#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
using namespace std;
using namespace CryptoPP;

int main() {
    try {
        string key_hex, iv_hex;
        FileSource("key.hex", true, new StringSink(key_hex));
        FileSource("iv.hex", true, new StringSink(iv_hex));
        cout << "Были прочитаны key.hex и iv.hex" << endl;

        byte key[AES::DEFAULT_KEYLENGTH];
        StringSource(key_hex, true,
            new HexDecoder(
                new ArraySink(key, sizeof(key))));
        byte iv[AES::BLOCKSIZE];
        StringSource(iv_hex, true,
            new HexDecoder(
                new ArraySink(iv, sizeof(iv))));
        cout << "Ключ и IV были преобразованы из hex" << endl;

        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, sizeof(key), iv);
        FileSource("encrypted.bin", true,
            new StreamTransformationFilter(decryptor,
                new FileSink("decrypted.txt")));
        cout << "Файл encrypted.bin был расшифрован в decrypted.txt" << endl;
    } catch(const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
