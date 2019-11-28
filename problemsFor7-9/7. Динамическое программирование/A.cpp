#include <iostream>
#include <algorithm> // std::max

int main() {
	freopen("ladder.in", "r", stdin);
	freopen("ladder.out", "w", stdout);

	int n, a[105], dp[105];

	std::cin >> n;
	for (int i = 2; i <= n + 1; ++i)
		std::cin >> a[i];

	dp[0] = 0;
	dp[1] = 0;
	for (int i = 2; i <= n + 1; ++i)
		dp[i] = std::max(dp[i - 1], dp[i - 2]) + a[i];

	std::cout << dp[n + 1];

	return 0;
}
