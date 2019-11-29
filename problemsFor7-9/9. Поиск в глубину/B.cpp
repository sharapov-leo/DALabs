#include <iostream>
#include <vector>

std::vector<std::vector<int>> g; // Списки смежности (орграф)
std::vector<int> entry;					// Время входа
std::vector<int> leave;					// Время выхода
std::vector<bool> used;				// 0 - непройденная вершина, 1 - пройденная

int t = 0;

void dfs(int u) {
	++t;
	entry[u] = t;
	used[u] = true;
	for (int i = 0; i < g[u].size(); ++i)
		if (!used[g[u][i]])
			dfs(g[u][i]);
	++t;
	leave[u] = t;
}

bool ok = false;

void searchCycle(int b, int u) {
	used[u] = true;
	if (b == u) {
		std::cout << u << " ";
		ok = true;
		return;
	}
	for (int i = 0; i < g[u].size(); ++i)
		if ((!used[g[u][i]]) &&  (!ok))
			searchCycle(b, g[u][i]);
	if (ok) 
		std::cout << u << " ";
}

int main() {
	freopen("cycle2.in", "r", stdin);
	freopen("cycle2.out", "w", stdin);

	int n;
	std::cin >> n;
	g.resize(n + 1); // Списки смежности
	entry.resize(n + 1);
	leave.resize(n + 1);
	used.resize(n + 1);
	int m;
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		int a, b; // (a, b) - дуга, ведущая из узла a в b
		std::cin >> a >> b;
		g[a].push_back(b);
	}

	for (int i = 1; i < n + 1; ++i)
		if (!used[i])
			dfs(i);

	bool cycleDetected = false;
	int a, b;

	for (int i = 1; i < n + 1; ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			if ((entry[g[i][j]] < entry[i]) && (entry[i] < leave[i]) && (leave[i] < leave[g[i][j]])) {
				cycleDetected = true;
				a = i;
				b = g[i][j];
				break;
			}
		}
		if (cycleDetected)
			break;
	}

	if (cycleDetected) {
		std::cout << "Yes" << std::endl;
		for (int i = 1; i < n + 1; ++i)
			used[i] = false;
		searchCycle(a, b);
	}
	else
		std::cout << "No" << std::endl;

	/*
7 10
1 2
1 3
2 4
2 5
2 7
3 6
4 1
5 7
6 1
6 7
	*/

	return 0;
}