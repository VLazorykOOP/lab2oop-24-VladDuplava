#include <iostream>
#include <fstream>

using namespace std;

void Deshifruvanna(unsigned short Rez[64], char S[64]) {
    unsigned short r, i, b;
    for (i = 0; i < 64; i++) {
        r = Rez[i];

        // Витягуємо номер рядка (3 біти)
        int row = r & 0x07;

        // Витягуємо позицію символу (3 біти)
        int col = (r >> 3) & 0x07;

        // Перевірка біта парності (6 біт)
        b = 0;
        for (int j = 0; j < 6; j++) {
            if (r & (1 << j)) b = !b;
        }
        if (b != ((r >> 6) & 0x01)) {
            cerr << "Помилка парності у мета-даних!" << endl;
            return;
        }

        // Витягуємо ASCII-код (8 біт)
        char ch = (r >> 7) & 0xFF;

        // Перевірка біта парності для ASCII-коду
        b = 0;
        for (int j = 7; j < 15; j++) {
            if (r & (1 << j)) b = !b;
        }
        if (b != ((r >> 15) & 0x01)) {
            cerr << "Помилка парності у ASCII-коді!" << endl;
            return;
        }

        // Зберігаємо символ у відповідне місце
        S[row * 8 + col] = ch;
    }
}

int main() {
    unsigned short Rez[64];
    char S[64] = { 0 };

    ifstream inputFile("encrypted.bin", ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }
    inputFile.read(reinterpret_cast<char*>(Rez), sizeof(Rez));
    inputFile.close();

    Deshifruvanna(Rez, S);

    // Вивід у консоль
    cout << "Розшифрований текст:\n";
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0 && i != 0) cout << endl;
        cout << S[i];
    }
    cout << endl;

    // Запис у файл
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return 1;
    }
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0 && i != 0) outputFile << endl;
        outputFile << S[i];
    }
    outputFile.close();

    cout << "Результат записано у файл 'output.txt'." << endl;

    return 0;
}
