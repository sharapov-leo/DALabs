#include <iostream>

const int MAXN = 101;

int main() {
	freopen("ladder.in", "r", stdin);
	freopen("ladder.out", "w", stdout);

	int n;
	std::cin >> n;

	int a[MAXN], b[MAXN]; // a - номер ступеньки (стоимость), b - сумма номеров (обща€ стоимость)
	b[0] = 0; // ѕо условию номер первой ступеньки равен 0

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i + 1];
		b[i + 1] = 0;
	}
	// Ќисход€щий анализ
	for (int i = n; i > 0; --i) {
		if ((b[i - 1] == 0) || (a[i] + b[i] > b[i - 1]))
			b[i - 1] = a[i] + b[i];
		if ((i - 2 >= 0) && ((b[i - 2] == 0) || (a[i] + b[i] > b[i - 2])))
			b[i - 2] = a[i] + b[i];
	}

	std::cout << b[0];
}