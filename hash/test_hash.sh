echo "1) Тестовый файл test.txt:"
./hash_program test.txt
echo "sha256sum: $(sha256sum test.txt | cut -d' ' -f1)"
echo ""
echo "2) Пустой тестовый файл empty.txt:"
./hash_program empty.txt
echo "sha256sum: $(sha256sum empty.txt | cut -d' ' -f1)"
echo ""
echo "3) Тестовый файл test2.txt:"
./hash_program test2.txt
echo "sha256sum: $(sha256sum test2.txt | cut -d' ' -f1)"
echo ""
echo "4) Проверка для несуществующего файла:"
./hash_program not_exist.txt
echo ""
echo "5) Проверка без аргументов:"
./hash_program
