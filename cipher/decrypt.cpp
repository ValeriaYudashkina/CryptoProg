#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
using namespace std;
using namespace CryptoPP;

int main() {
    string input_file, output_file, password, iv_file;
    cout << "Входной файл: ";
    cin >> input_file;
    cout << "Выходной файл: ";
    cin >> output_file;
    cout << "Пароль: ";
    cin >> password;
    cout << "Файл с IV: ";
    cin >> iv_file;

    try {
        string iv_hex;
        FileSource(iv_file.c_str(), true, new StringSink(iv_hex));

        byte iv[AES::BLOCKSIZE];
        StringSource(iv_hex, true,
            new HexDecoder(
                new ArraySink(iv, sizeof(iv))));
        cout << "IV был прочитан из " << iv_file << endl;

        byte key[AES::DEFAULT_KEYLENGTH];
        SHA256 hash;
        hash.CalculateDigest(key, (byte*)password.data(), password.size());
        cout << "Ключ был выработан из пароля" << endl;

        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, sizeof(key), iv);
        FileSource(input_file.c_str(), true,
            new StreamTransformationFilter(decryptor,
                new FileSink(output_file.c_str())));
        cout << "Файл " << input_file << " был расшифрован в " << output_file << endl;
    } catch(const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
