#include <iostream>
#include <algorithm>

const int INF = 1e9, MAXN = 55;

int main() {
	freopen("king2.in", "r", stdin);
	freopen("king2.out", "w", stdout);

	int n, m, dp[MAXN][MAXN], a[9][9];

	for (int i = 1; i < 9; ++i)
		for (int j = 1; j < 9; ++j) {
			std::cin >> a[i][j];
			dp[i][j] = INF;
		}

	dp[8][1] = 0;
	for (int i = 8; i > 0; --i) {
		for (int j = 1; j <= 8; ++j) {
			if (i - 1 >= 1) dp[i - 1][j] = std::min(dp[i - 1][j], dp[i][j] + a[i][j]);
			if (j + 1 <= 8) dp[i][j + 1] = std::min(dp[i][j + 1], dp[i][j] + a[i][j]);
			if (i - 1 >= 1 && j + 1 <= 8) dp[i - 1][j + 1] = std::min(dp[i - 1][j + 1], dp[i][j] + a[i][j]);
		}
	}
	std::cout << dp[1][8] + a[1][8];

	return 0;
}