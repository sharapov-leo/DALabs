#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<int> b(n);
	for (int i = 0; i < n; ++i)
		std::cin >> a[i] >> b[i];
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += a[i] * b[i];
	std::cout << sum;

	return 0;
}