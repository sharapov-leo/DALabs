#include <iostream>
#include <vector>
#include <algorithm>

struct subject { // Характеристики предмета
	double weight;		// Вес
	double value;		// Стоимость
	double unitCost;	// Удельная стоимость = цена / вес
};

bool cmp(const subject& x, const subject& y) { return x.unitCost > y.unitCost; }

int main() {
	int n;
	double w; // n - число предметов, а w - вместимость мешка
	std::cin >> n >> w;
	std::vector<struct subject> v(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> v[i].value >> v[i].weight;
		v[i].unitCost = v[i].value / v[i].weight;
	}
	std::sort(v.begin(), v.end(), cmp); // Сортируем по удельной стоимости
	double sumV = 0;
	for (int i = 0; i < n; ++i) {
		double d = w / v[i].weight;
		if (d < 1) {
			sumV += v[i].value * d; // Если предмет не умещается целиком, то делим его вес
									//, который уместится в рюкзак, и ценность,
			break;					// Рюкзак заполнен
									// Если предмет нельзя делить, то жадный алгоритм не будет работать
		}
		else {
			sumV += v[i].value;
			w -= v[i].weight;
		}

	}
	std::cout << sumV;

	return 0;
}