#include <iostream>
#include <vector>

std::vector<std::vector<int>> g; // Ñïèñêè ñìåæíîñòè (îðãðàô)
std::vector<int> entry;					// Âðåìÿ âõîäà
std::vector<int> leave;					// Âðåìÿ âûõîäà
std::vector<bool> used;				// 0 - íåïðîéäåííàÿ âåðøèíà, 1 - ïðîéäåííàÿ

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

int main() {
	//freopen("ancestor.in", "r", stdin);
	//freopen("ancestor.out", "w", stdin);

	int n;
	std::cin >> n;
	g.resize(n + 1); // Ñïèñêè ñìåæíîñòè
	entry.resize(n + 1);
	leave.resize(n + 1);
	used.resize(n + 1);
	int m;
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		int a, b; // (a, b) - äóãà, âåäóùàÿ èç óçëà a â b
		std::cin >> a >> b;
		g[a].push_back(b);
	}
	
	for (int i = 1; i < n + 1; ++i)
		if (!used[i])
			dfs(i);

	for (int i = 1; i < n + 1; ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			std::cout << "(" << i << ", " << g[i][j] << ") entry[u]=" << entry[i] << " entry[v]=" << entry[g[i][j]] << " leave[u]=" << leave[i] << " leave[v]=" << leave[g[i][j]] << std::endl;
			if ((entry[i] < entry[g[i][j]]) && (entry[g[i][j]] < leave[g[i][j]]) && (leave[g[i][j]] < leave[i]))
				std::cout << "\tsearch tree arc or straight arc" << std::endl;
			if ((entry[g[i][j]] < leave[g[i][j]]) && (leave[g[i][j]] < entry[i]) && (entry[i] < leave[i]))
				std::cout << "\tcross arc" << std::endl;
			if ((entry[g[i][j]] < entry[i]) && (entry[i] < leave[i]) && (leave[i] < leave[g[i][j]]))
				std::cout << "\tbackward arc" << std::endl;
		}
	}

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
