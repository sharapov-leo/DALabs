#include <iostream>

int main() {
	//freopen("badsubs.in", "r", stdin);
	//freopen("badsubs.out", "w", stdout);

	int n, dp[25][3];

	std::cin >> n;

	dp[1][0] = 1;
	dp[1][1] = 1;
	dp[1][2] = 1;
	for (int i = 2; i <= n; ++i) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
		dp[i][1] = dp[i - 1][1] + dp[i - 1][2];
		dp[i][2] = dp[i][0];
	}

	if (n == 0) std::cout << 1;
	else std::cout << dp[n][0] + dp[n][1] + dp[n][2];

	return 0;
}