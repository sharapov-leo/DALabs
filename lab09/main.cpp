#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

std::vector<std::set<int>> g;
std::vector<int> matching;
std::vector<char> used;


bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (auto to : g[v])
		if (matching[to] == -1 || dfs(matching[to])) {
			matching[to] = v;
			matching[v] = to;
			return true;
		}
	return false;
}

int main() {
	int n, m;
	int v1, v2;
    std::cin >> n >> m;
	g.resize(n);
	used.resize(n);
    while (std::cin >> v1 >> v2) {
        --v1;
        --v2;
        g[v1].insert(v2);
        g[v2].insert(v1);
    }
	matching.assign(n, -1);

	for (int i = 0; i < n; ++i)
        if (matching[i] == -1) {
			used.assign(n, 0);
            dfs(i);
        }
	int num = 0;
	for (int i = 0; i < n; ++i)
		if (i < matching[i])
			++num;
	std::cout << num << std::endl;
	for (int i = 0; i < n; ++i)
		if (i < matching[i])
			std::cout << i + 1 << " " << matching[i] + 1 << std::endl;
}
