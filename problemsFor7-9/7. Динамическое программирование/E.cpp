#include <iostream>
#include <algorithm>

const int INF = 1e9, MAXN = 105;

int main() {
	//freopen("slalom.in", "r", stdin);
	//freopen("slalom.out", "w", stdout);

	int n, m, dp[MAXN][MAXN], a[MAXN][MAXN], ans = -INF;

	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
			std::cin >> a[i][j];
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; j++) 
			dp[i][j] = -INF;

	dp[1][1] = a[1][1];
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
			dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - 1]) + a[i][j];

	for (int i = 1; i <= n; ++i)
		ans = std::max(ans, dp[n][i]);

	std::cout << ans << std::endl;

	return 0;
}