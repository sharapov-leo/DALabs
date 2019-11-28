#include <iostream>

const int MAXN = 9;

int main() {
	//freopen("king2.in", "r", stdin);
	//freopen("king2.out", "w", stdout);

	int a[MAXN][MAXN], b[MAXN][MAXN]; // a - стоимость клетки
	for (int i = 1; i < MAXN; ++i)
		for (int j = 1; j < MAXN; ++j) {
			std::cin >> a[i][j];
			b[i][j] = 0;
		}
	// b[8][1] - левый нижний угол
	for(int i = 8; i > 0; --i)
		for (int j = 1; j < 9; ++j) {
			// Шаг вверх
			if ((i - 1 > 0) && ((b[i - 1][j] == 0) || (b[i - 1][j] > a[i - 1][j] + b[i][j])))
				b[i - 1][j] = a[i - 1][j] + b[i][j];
			// Шаг вправо
			if ((j + 1 < 9) && ((b[i][j + 1] == 0) || (b[i][j + 1] > a[i][j + 1] + b[i][j])))
				b[i][j + 1] > a[i][j + 1] + b[i][j];
			// Шаг по диагонали
			if ((i - 1 > 0) && (j + 1 < 9) && ((b[i - 1][j + 1] == 0) || (b[i - 1][j + 1] > a[i - 1][j + 1] + b[i][j])))
				b[i - 1][j + 1] = a[i - 1][j + 1] + b[i][j];
		}

	std::cout << b[1][8];
	return 0;
}