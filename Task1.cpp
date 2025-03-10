#include <iostream>

int main() {
    int a, b, c, d;
    std::cout << "Enter values for a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    int result = ((17 * a + 312 * c) >> 5) // (17a + 312c) / 32
                 - ((b << 7) - (b << 3))   // 120 * b = (128 - 8) * b
                 + ((d << 7) - d);         // 127 * d = (128 - 1) * d

    std::cout << "Result: " << result << std::endl;
    return 0;
}