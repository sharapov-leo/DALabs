#include <iostream>
#include <algorithm>

const int INF = 1e9, MAXN = 1e4 + 5;

int dp[MAXN];

int main() {
	//freopen("knapsack.in", "r", stdin);
	//freopen("knapsack.out", "w", stdout);

	int s, n, a[305];

	std::cin >> s >> n;
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];

	dp[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = s - a[i]; j >= 0; --j)
			if (dp[j])
				dp[j + a[i]] = 1;
	}

	for (int i = s; i >= 0; --i)
		if (dp[i]) {
			std::cout << i;
			break;
		}

	return 0;
}