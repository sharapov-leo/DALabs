#include <iostream>
#include <vector>
#include <string>

struct node {
	unsigned long long cost = 0;		// Стоимость действия
	char operation;	// Деление на 2 - '2', Деление на 3 - '3', Вычесть единицу - '1'
};

int main() {
	unsigned long long n;
	std::cin >> n;
	std::vector<node> v(n + 1);
	// Нисходящий анализ
	for (unsigned long long i = n; i > 0; --i) {
		if ((i != n) && ((v[i].cost > v[i + 1].cost + i + 1) || (v[i].cost == 0))) {
			v[i].cost = v[i + 1].cost + i + 1;
			v[i].operation = '1';
		}
		if ((i % 2 == 0) && ((v[i / 2].cost > v[i].cost + i) || (v[i / 2].cost == 0))) {
			v[i / 2].cost = v[i].cost + i;
			v[i / 2].operation = '2';
		}
		if ((i % 3 == 0) && ((v[i / 3].cost > v[i].cost + i) || (v[i / 3].cost == 0))) {
			v[i / 3].cost = v[i].cost + i;
			v[i / 3].operation = '3';
		}
			
	}
	std::cout << v[1].cost << std::endl;	// Выводим общую стоимость
	std::string str;
	// Вывод последовательности примененных операций
	unsigned long long numNode = 1; // От конца к началу
	while (numNode != n) {
		if (v[numNode].operation == '1') {
			str += " 1-";
			++numNode;
		}
		if (v[numNode].operation == '2') {
			str += " 2/";
			numNode *= 2;
		}
		if (v[numNode].operation == '3') {
			str += " 3/";
			numNode *= 3;
		}
	}
	unsigned long long sizeStr = str.size();
	for (unsigned long long i = sizeStr - 1; i > 0; --i)
		std::cout << str[i];
	std::cout << std::endl;

	return 0;
}
