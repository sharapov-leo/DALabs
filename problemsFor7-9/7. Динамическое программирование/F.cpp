#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9, MAXN = 3 * 1e5 + 5;

int a[MAXN], b[MAXN]; // Перемещены в кучу, потому что для функций ограничение размера стека - 16384 байт

int main() {
	//freopen("balls.in", "r", stdin);
	//freopen("balls.out", "w", stdout);

	int t, m[25], n = 1;

	std::cin >> t;
	for (int i = 1; i <= t; ++i) 
		std::cin >> m[i];

	b[1] = 1;
	for (int i = 2; ; ++i) {
		b[i] = b[i - 1] + i;
		if (b[i] > MAXN) 
			break;
	}

	a[1] = 1;
	for (int i = 2; ; ++i) {
		a[i] = a[i - 1] + b[i];
		++n;
		if (a[i] > MAXN) 
			break;
	}

	std::vector<int> d(2 * MAXN, INF);

	d[0] = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j <= MAXN - a[i]; ++j) {
			int d1 = d[j + a[i]], d2 = d[j] + 1;
			d[j + a[i]] = std::min(d1, d2);
		}
	}

	for (int i = 1; i <= t; ++i) {
		if (i - 1) 
			std::cout << std::endl;
		std::cout << d[m[i]];
	}

	return 0;
}