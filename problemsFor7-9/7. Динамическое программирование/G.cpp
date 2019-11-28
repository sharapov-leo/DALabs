#include <iostream>
#include <algorithm>

const int INF = 1e9, MAXN = 1e4 + 5;

int d[MAXN]; // Перемещен в кучу, потому что размер стека функции ограничен 16384 байтами
				// Изначально все эл-ты равны нулю

int main() {
	//freopen("longpath.in", "r", stdin);
	//freopen("longpath.out", "w", stdout);

	int n, m, mx = 0;
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int b, e;
		std::cin >> b >> e;
		d[e] = std::max(d[e], d[b] + 1);
	}
	
	for (int i = 1; i <= n; ++i) 
		mx = std::max(mx, d[i]);

	std::cout << mx;

	return 0;
}