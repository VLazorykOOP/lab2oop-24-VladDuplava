#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функція для обчислення біта парності
bool calculateParity(unsigned short number, int startBit, int endBit) {
    bool parity = 0;
    for (int i = startBit; i <= endBit; ++i) {
        parity ^= (number >> i) & 1;
    }
    return parity;
}

void Shifruvanna(string lines[8], unsigned short Rez[8][8]) {
    unsigned short r;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (lines[row][col] == '\0') lines[row][col] = ' '; // символ порожній заповнюємо пробілом

            r = 0;
            unsigned char c = lines[row][col];

            // Номер рядка
            r |= (row & 0x07);

            // Позиція символу в рядку
            r |= ((col & 0x07) << 3);

            // Біт парності для номеру рядка і позиції символу
            bool parity1 = calculateParity(r, 0, 5);
            r |= (parity1 << 6);

            // ASCII-код символу
            r |= (c & 0xFF) << 7;

            // Біт парності для ASCII-коду
            bool parity2 = calculateParity(r, 7, 14);
            r |= (parity2 << 15);

            Rez[row][col] = r;
        }
    }
}

int main0() {
    string lines[8];
    unsigned short Rez[8][8];

    ifstream inputFile("test.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    // Читання файлу рядок за рядком
    for (int i = 0; i < 8; ++i) {
        getline(inputFile, lines[i]);

        // Якщо рядок менший за 8 символів, доповнюємо пробілами
        if (lines[i].length() < 8) {
            lines[i].append(8 - lines[i].length(), ' ');
        }
    }

    inputFile.close();

    // Шифрування
    Shifruvanna(lines, Rez);

    // Виведення результату у шістнадцятковому форматі
    cout << "Зашифрований результат у шістнадцятковому форматі:" << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << hex << Rez[i][j] << endl;
        }
    }

    // Запис у бінарний файл
    ofstream outputFile("encrypted.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return 1;
    }

    // Записуємо зашифровані дані в файл
    for (int i = 0; i < 8; ++i) {
        outputFile.write(reinterpret_cast<char*>(&Rez[i]), sizeof(Rez[i]));
    }

    outputFile.close();
    cout << "Результат записано у файл 'encrypted.bin'." << endl;

    return 0;
}
