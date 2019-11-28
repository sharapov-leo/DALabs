#include <iostream>

const int MAXNM = 51;

int main() {
	freopen("knight.in", "r", stdin);
	freopen("knight.out", "w", stdout);

	int n, m;
	std::cin >> n >> m;

	int d[MAXNM][MAXNM];

	for (int i = 0; i < MAXNM; ++i)
		for (int j = 0; j < MAXNM; ++j)
			d[i][j] = -1; // Изначально все клетки недостижимы

	d[n][m] = 1;
	// Нисходящий анализ
	for (int i = n; i > 0; --i)
		for (int j = m; j > 0; --j) {
			if (d[i][j] == -1)
				continue;
			if ((i - 2 > 0) && (j - 1 > 0))
				if (d[i - 2][j - 1] == -1)
					d[i - 2][j - 1] = d[i][j];
				else
					d[i - 2][j - 1] += d[i][j];
			if ((i - 1 > 0) && (j - 2 > 0))
				if (d[i - 1][j - 2] == -1)
					d[i - 1][j - 2] = d[i][j];
				else
					d[i - 1][j - 2] += d[i][j];
		}

	std::cout << (d[1][1] != -1 ? d[1][1] : 0);

	return 0;
}