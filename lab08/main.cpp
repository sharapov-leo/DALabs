#include <iostream>
#include <vector>

class topologicalSorting {
	std::vector< std::vector<int> > arcs;	// Дуги
	std::vector<char> color;				// Цвета вершин: 'w' - белая, 'g' - серая и 'b' - черная
	std::vector<int> result;				// Согласованная последовательность вершин
public:
	void taryanAlgo(int v);					// Алгоритм Тарьяна (топологическая сортировка)

	friend std::istream& operator>>(std::istream& in, topologicalSorting& obj);
	friend std::ostream& operator<<(std::ostream& out, topologicalSorting obj);

	int n = 0;	// Кол-во объектов
};

std::istream& operator>>(std::istream& in, topologicalSorting& obj) {
	int m;		// m - кол-во ограничений (строк)
	int from;	// from - начало ограничения
	int to;		// to - его конец
	std::cin >> obj.n >> m;		// Считываем кол-во объектов и кол-во строк

	obj.arcs.resize(obj.n);			// Размер вектора изменяем на n
	obj.color.assign(obj.n, 'w');	// Размер вектора изменяем на n и заполняем его элементы буквами 'w' (все вершины являются белыми)	

	for (int i = 0; i < m; ++i) {
		std::cin >> from >> to;
		obj.arcs[from - 1].push_back(to - 1);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, topologicalSorting obj) {
	for (int i = obj.n - 1; i > -1; --i)
		std::cout << obj.result[i] << " ";
	std::cout << std::endl;
	return out;
}

void topologicalSorting::taryanAlgo(int v) {
	if (color[v] == 'b')
		return;
	else if (color[v] == 'g') {
		std::cout << "-1";
		exit(0);
	}
	else {
		color[v] = 'g';
		int size = (int)arcs[v].size();
		for (int i = 0; i < size; ++i)
			taryanAlgo(arcs[v][i]);
		color[v] = 'b';
		result.push_back(v + 1);
	}
}

int main() {
	topologicalSorting g;
	std::cin >> g;
	for (int i = 0; i < g.n; ++i)
		g.taryanAlgo(i);
	std::cout << g;
    return 0;
}
