#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class longNumber{
	std::vector<int> num;
public:
	longNumber() {}
	longNumber(int n);		// Для создания объектов из числа

	longNumber operator+(const longNumber& right) const;
	longNumber operator-(const longNumber& right) const;
	longNumber operator*(const longNumber& right) const;
	longNumber operator/(const longNumber& right) const;
	longNumber operator^(const longNumber& right) const;

	friend std::istream& operator>>(std::istream& in, longNumber& obj);
	friend std::ostream& operator<<(std::ostream& out, longNumber obj);

	bool operator==(const longNumber& right) const;
	int cmp(longNumber& obj) const;
	void delLeadingZeros();
	longNumber binPow(const longNumber& right) const;
};

const int base = 10000;			// Основание системы счисления
const int numOfZerosInBase = 4;	// Кол-во нулей в сс

longNumber::longNumber(int n) {
	if (n < base)
		num.push_back(n);
	else 
		while (n) {
			num.push_back(n % base);
			n /= base;
		}
}

std::istream& operator>>(std::istream& in, longNumber& obj) {
	obj.num.clear();	// Если объект повторно используется, то нужно очистить вектор
	std::string str;	// Длинное число
	in >> str;			// Считываем число
	int i = 0;
	int size = (int)str.size(); // Размер строки (кол-во разрядов числа)
	while (str[i] == '0')  // Считаем кол-во незначащих нулей
		++i;
	if (i == size) { // Если все число состоит из незначащих нулей,
		str = '0';   // то заменяем все число на один ноль,
		size = 1;	 // Кол-во разрядов числа = 1
	}
	else {			 // иначе отбрасываем незначащие нули
		str = str.substr(i);	// str.substr(i) = str[i..|str|]
		size = (int)str.size(); // Изменяем длину на новую
	}
	
	for (i = size; i > 0; i -= numOfZerosInBase) {
		if (i < numOfZerosInBase)
			obj.num.push_back(stoi(str.substr(0, i)));
		else obj.num.push_back(stoi(str.substr(i - numOfZerosInBase, numOfZerosInBase)));
	}
	return in;
}


void longNumber::delLeadingZeros() { // Удаление незначащих нулей из вектора
	if (num.size() != 1) { // Если кол-во элементов вектора не равно 1,
		for (int i = (int)num.size() - 1; i > 0; --i) { // то от конца вектора до начала (число записано в обратном порядке)
			if (num[i] != 0) // Если встретился не незначащий ноль,
				break;		 // то прекращаем удаление,
			num.pop_back();  // иначе удаляем его
		}
	}
}

std::ostream& operator<<(std::ostream& out, longNumber obj) {
	int size = (int)obj.num.size();		// Длина вектора
	printf("%d", obj.num[size - 1]);	// Распечатываем первый разряд
	for (int i = size - 2; i >= 0; --i) {	// Распечатывем последующие части числа с дополнением до 4-х разрядов - кол-во нулей в сс (дополняем незначащими нулями)
		printf("%04d", obj.num[i]);
	}
	printf("\n");
	return out;
}

longNumber longNumber::operator+(const longNumber& right) const {
	int k = 0;	// Остаток
	int l, r;	// Значения разрядов
	int sizeLeft = (int)num.size();		// Размер вектора левого операнда
	int sizeRight = (int)right.num.size();	// Размер вектора правого операнда
	int maxSize = std::max(sizeLeft, sizeRight);	// Наибольший размер из двух векторов
	longNumber res;

	for (int i = 0; i < maxSize; ++i) {	// Если i >= max, но r != 0, то нужен новый разряд, чтобы поместить туда r (как в сложении столбиком)
		if (i < sizeLeft)	// Если разряд сопоставленный с разрядом другого числа не выходит за значащие разряды,
			l = num[i];		// то считываем его из вектора,
		else
			l = 0;			// иначе это незначащий ноль
		if (i < sizeRight) // Тоже самое, что и выше
			r = right.num[i];
		else
			r = 0;
		// Алгоритм A из книги Кнута том 2 стр. 295
		res.num.push_back((l + r + k) % base);
		k = (l + r + k) / base;
	}
	if (k) res.num.push_back(k);
	return res;
}

longNumber longNumber::operator-(const longNumber& right) const {
	int k = 0;
	int l, r;	// Значения разрядов
	int sizeLeft = (int)num.size();		// Размер вектора левого операнда
	int sizeRight = (int)right.num.size();	// Размер вектора правого операнда
	longNumber res;
	for (int i = 0; i < sizeLeft; ++i) { // Вычитаем число из левого операнда, поэтому считается, что он больше по размеру
		l = num[i];	// Берем текущий разряд (от младшего к старшему)
		if (i < sizeRight) 
			r = right.num[i];
		else
			r = 0;
		// Алгоритм S из книги Кнута том 2 стр. 296
		
		int add = l - r + k;
		if (add < 0) {
			add += base;
			k = -1;
		}
		else
			k = 0;
		res.num.push_back(add % base);
		
	}
	res.delLeadingZeros();
	return res;
}

longNumber longNumber::operator*(const longNumber& right) const {
	// Из тетради
	int k = 0;
	int sizeLeft = (int)num.size();
	int sizeRight = (int)right.num.size();
	longNumber res;
	res.num.resize(sizeLeft + sizeRight);
	for (int i = 0; i < sizeLeft; ++i) {
		if (num[i] == 0) continue;
		k = 0;
		for (int j = 0; j < sizeRight; ++j) {
			res.num[i + j] += num[i] * right.num[j] + k;
			k = res.num[i + j] / base;
			res.num[i + j] %= base;
		}
		if (k > 0) res.num[i + sizeRight] = k;
	}
	res.delLeadingZeros();
	return res;
}

longNumber longNumber::operator/(const longNumber& right) const {
	int norm = base / (right.num.back() + 1);

	longNumber a = *this * norm;
	longNumber b = right * norm;
	longNumber res, r;
	int size_a = (int)a.num.size();
	int size_b = (int)b.num.size();

	res.num.resize(size_a);

	for (int i = size_a - 1; i >= 0; --i) {
		r = r * base + a.num[i];
		int s1;
		if ((int)r.num.size() > size_b)
			s1 = r.num[size_b];
		else
			s1 = 0;
		int s2;
		if ((int)r.num.size() > size_b - 1)
			s2 = r.num[size_b - 1];
		else
			s2 = 0;
		int d = (s1 * base + s2) / b.num.back();

		longNumber tmp = b * d;
		while (tmp.cmp(r) > 0) {
			tmp = tmp - b;
			--d;
		}

		r = r - tmp;
		res.num[i] = d;
	}

	res.delLeadingZeros();
	return res;
}

longNumber longNumber::operator^(const longNumber& right) const {
	// Из посылки в codeforces: соревнование Math[5] задача E: Степень
	/*longNumber res = 1;
	longNumber a = *this;
	longNumber n = right;
	while (n > 0) {
		if (n.num[0] & 1)
			res = res * a;
		a = a * a;
		n = n / 2;
	}*/
	return binPow(right);
}

longNumber longNumber::binPow(const longNumber& right) const{
	if (right == 0) 
		return 1;
	if (right.num[0] & 1)
		return *this * binPow(right - 1);
	else {
		longNumber c = binPow(right / 2);
		return c * c;
	}
}

bool longNumber::operator==(const longNumber& right) const {
	// Из тетради
	int sizeLeft = (int)num.size();
	int sizeRight = (int)right.num.size(), i;
	if (sizeLeft != sizeRight)
		return false;
	for (i = 0; i < sizeLeft; ++i)
		if (num[i] != right.num[i]) 
			return false;
	return true;
}

int longNumber::cmp(longNumber& obj) const{
	// Из тетради
	int sizeLeft = (int)num.size();
	int sizeRight = (int)obj.num.size();
	if (sizeLeft != sizeRight)
		return sizeLeft > sizeRight ? 1 : -1;
	for (int i = sizeLeft - 1; i >= 0; --i)
		if (num[i] != obj.num[i])
			return num[i] > obj.num[i] ? 1 : -1;
	return 0;
}

int main() {
	longNumber longNum1, longNum2;
	char c;
	while (std::cin >> longNum1 >> longNum2 >> c) {
		switch (c) {
		case '+': std::cout << (longNum1 + longNum2);
			break;
		case '-':
			if (longNum1.cmp(longNum2) < 0)
				std::cout << "Error" << std::endl;
			else 
				std::cout << (longNum1 - longNum2);
			break;
		case '*': std::cout << (longNum1 * longNum2);
			break;
		case '/':
			if (longNum2 == 0)
				std::cout << "Error" << std::endl;
			else 
				std::cout << (longNum1 / longNum2);
			break;
		case '^': 
			if (longNum1 == 0) {
				if (!(longNum2 == 0))
					std::cout << '0' << std::endl;
				else
					std::cout << "Error" << std::endl;
			}
			else
				std::cout << (longNum1 ^ longNum2);
			break;
		case '>':
			if (longNum1.cmp(longNum2) > 0)
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;
			break;
		case '<':
			if (longNum1.cmp(longNum2) < 0)
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;
			break;
		case '=':
			if (longNum1 == longNum2)
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;
			break;
		default: 
			break;
		}
	}
	return 0;
}
