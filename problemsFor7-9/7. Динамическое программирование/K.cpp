#include <iostream>

const int MAXN = 1e6 + 5;

int d[MAXN]; // Перемещено в кучу, потому что размер стека для функции ограничен 16384 байтами

int main() {
	freopen("joseph.in", "r", stdin);
	freopen("joseph.out", "w", stdout);

	int n, p;

	std::cin >> n >> p;

	for (int i = 1; i <= n; ++i)
		d[i] = (d[i - 1] + p) % i;

	std::cout << d[n] + 1;

	return 0;
}