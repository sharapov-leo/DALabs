#include <iostream>

const int MAXN = 1001;

int main() {
	freopen("lepus.in", "r", stdin);
	freopen("lepus.out", "w", stdout);

	int n;
	std::cin >> n;

	int a[MAXN], b[MAXN];
	for (int i = 0; i < n; ++i) {
		char c;
		std::cin >> c;
		if (c == '.')
			a[i + 1] = 0;
		else if (c == 'w')
			a[i + 1] = -1;
		else if (c == '"')
			a[i + 1] = 1;
		b[i + 1] = -1; // »значально все клетки недостижимые
	}
	b[n] = 0;
	// Ќисход€щий анализ
	for (int i = n; i > 0; --i) {
		if ((a[i] == -1) || (b[i] == -1)) // ≈сли текуща€ клетка недостижима,
			continue; // то переходим к следующей
		if ((a[i - 1] != -1) && ((b[i - 1] == -1) || (b[i - 1] < a[i - 1] + b[i])))
			b[i - 1] = a[i - 1] + b[i];
		if ((i - 3 >= 1) && (a[i - 3] != -1) && ((b[i - 3] == -1) || (b[i - 3] < a[i - 3] + b[i])))
			b[i - 3] = a[i - 3] + b[i];
		if ((i - 5 >= 1) && (a[i - 5] != -1) && ((b[i - 5] == -1) || (b[i - 5] < a[i - 5] + b[i])))
			b[i - 5] = a[i - 5] + b[i];
	}

	std::cout << b[1]; // ≈сли -1, то невозможно прийти из начала в конец

	return 0;
}