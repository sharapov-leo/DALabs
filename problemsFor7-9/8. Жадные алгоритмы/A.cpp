#include <iostream>

int main() {
	int m;
	std::cin >> m;
	// Номинал монет: 1, 5 и 10. 5 = 1 + 1 + 1 + 1 + 1. 10 = 5 + 5. Поэтому жадный алгоритм будет работать
	int ten = m / 10;
	m -= ten * 10;
	int five = m / 5;
	m -= five * 5;
	int one = m;
	std::cout << ten + five + one;

	return 0;
}
