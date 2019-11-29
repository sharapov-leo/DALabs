#include <iostream>
#include <vector>

std::vector<std::vector<int>> g;		// Списки смежности
std::vector<int> entry;					// Время входа
std::vector<int> leave;					// Время выхода
std::vector<bool> used;					// 0 - непройденная вершина, 1 - пройденная

int t = 0;								// Время

void dfs(int u) {
	++t;
	entry[u] = t;
	used[u] = true;
	for (int i = 0; i < g[u].size(); ++i)
		if (!used[g[u][i]])
			dfs(g[u][i]);
	leave[u] = t++;
}

int main() {
	//freopen("ancestor.in", "r", stdin);
	//freopen("ancestor.out", "w", stdin);

	int n;
	std::cin >> n;
	g.resize(n + 1); // Списки смежности
	entry.resize(n + 1);
	leave.resize(n + 1);
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
		ans[i] = (((entry[a] < entry[b]) && (leave[b] < leave[a])) ? 1 : 0);
	}
	for (int i = 0; i < m; ++i)
		std::cout << ans[i] << std::endl;

	return 0;
}
