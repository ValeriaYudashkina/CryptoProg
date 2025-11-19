#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
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
    cout << "Файл для IV: ";
    cin >> iv_file;

    try {
        AutoSeededRandomPool rng;
        byte iv[AES::BLOCKSIZE];
        rng.GenerateBlock(iv, sizeof(iv));

        string iv_hex;
        StringSource(iv, sizeof(iv), true,
            new HexEncoder(
                new StringSink(iv_hex)));
        StringSource(iv_hex, true, new FileSink(iv_file.c_str()));
        cout << "IV был сохранен в: " << iv_file << endl;

        byte key[AES::DEFAULT_KEYLENGTH];
        SHA256 hash;
        hash.CalculateDigest(key, (byte*)password.data(), password.size());
        cout << "Ключ был выработан из пароля" << endl;

        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, sizeof(key), iv);
        FileSource(input_file.c_str(), true,
            new StreamTransformationFilter(encryptor,
                new FileSink(output_file.c_str())));
        cout << "Файл " << input_file << " был зашифрован в " << output_file << endl;
    } catch(const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
