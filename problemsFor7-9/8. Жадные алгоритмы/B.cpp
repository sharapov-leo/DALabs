#include <iostream>
#include <vector>
#include <algorithm>

struct subject { // �������������� ��������
	double weight;		// ���
	double value;		// ���������
	double unitCost;	// �������� ��������� = ���� / ���
};

bool cmp(const subject& x, const subject& y) { return x.unitCost > y.unitCost; }

int main() {
	int n;
	double w; // n - ����� ���������, � w - ����������� �����
	std::cin >> n >> w;
	std::vector<struct subject> v(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> v[i].value >> v[i].weight;
		v[i].unitCost = v[i].value / v[i].weight;
	}
	std::sort(v.begin(), v.end(), cmp); // ��������� �� �������� ���������
	double sumV = 0;
	for (int i = 0; i < n; ++i) {
		double d = w / v[i].weight;
		if (d < 1) {
			sumV += v[i].value * d; // ���� ������� �� ��������� �������, �� ����� ��� ���
									//, ������� ��������� � ������, � ��������,
			break;					// ������ ��������
									// ���� ������� ������ ������, �� ������ �������� �� ����� ��������
		}
		else {
			sumV += v[i].value;
			w -= v[i].weight;
		}

	}
	std::cout << sumV;

	return 0;
}