#include <iostream>
#include <vector>

std::vector<std::vector<int>> g; // Списки смежности
std::vector<int> d;					// Время входа
std::vector<int> f;					// Время выхода
std::vector<bool> used;				// 0 - непройденная вершина, 1 - пройденная

int t = 0;

void dfs(int v) {
	used[v] = true;
	d[v] = t++;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs(to);
	}
	f[v] = t++;
}

int main() {
	//freopen("ancestor.in", "r", stdin);
	//freopen("ancestor.out", "w", stdin);

	int n;
	std::cin >> n;
	g.resize(n + 1); // Списки смежности
	d.resize(n + 1);
	f.resize(n + 1);
	used.resize(n + 1);
	int root;
	for (int i = 1; i < n + 1; ++i) {
		int a;
		std::cin >> a;
		if (a == 0)
			root = i;
		else
			g[a].push_back(i);
	}
	dfs(root);
	int m;
	std::cin >> m;
	std::vector<int> ans(m);
	for (int i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		ans[i] = (d[a] < d[b] && f[b] < f[a] ? 1 : 0);
	}
	for (int i = 0; i < m; ++i)
		std::cout << ans[i] << std::endl;

	return 0;
}
