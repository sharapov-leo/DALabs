#include <iostream>

const int MAXN = 55;

int main() {
	//freopen("knight.in", "r", stdin);
	//freopen("knight.out", "w", stdout);

	int n, m, dp[MAXN][MAXN];

	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
			dp[i][j] = 0;

	std::cin >> n >> m;
	dp[1][1] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= m; ++j) {
			dp[i][j] += dp[i - 2][j - 1] + dp[i - 1][j - 2];
		}
	}

	std::cout << dp[n][m];

	return 0;
}