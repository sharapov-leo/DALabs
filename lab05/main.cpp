#include <iostream>
#include <string>
#include <memory>

const int alphabetSize = 26; // Без маркера конца ('a' - 'z' without #)

class suffixTree { // Состояние
	std::shared_ptr<suffixTree> children[alphabetSize]; // Переходы на дочерние состояния
	std::shared_ptr<suffixTree> suffixLink;				// Суффиксная ссылка
	int start;											// Начальная позиция в тексте, соответствующая данному состоянию
	int* end = nullptr;									// Конечная позиция в тексте
public:
	suffixTree(int start, int* end);    // Заполяет значениями поумолчанию данный узел и указанными начальной и конечной позициями
	int suffixLength();					// Длина суффикса текста
	void addCharacterToTree(int pos);
	void linearizeTheCyclicString();	// Алгоритм линеаризации циклической строки
	void setSuffixLink();				// Устанавливает суффиксную ссылку на корень
};

std::string text;					// Текст
int sizeText;						// Длина неудвоенного текста
std::shared_ptr<suffixTree> root;	// Корень
int lastChar;						// Позиция текущего символа, а в итоге - позиция последнего символа в тексте
int numSufToAdd;					// Количество суффиксов, которые осталось добавить

struct active {
	std::shared_ptr<suffixTree> node;	// Состояние
	int c;								// Заменить на c
	int length;							// Длина
};

active activePoint; // Активная точка

suffixTree::suffixTree(int start, int* end) {
	for (int i = 0; i < alphabetSize; ++i) {
		this->children[i] = NULL;
	}
	this->suffixLink = root;
	this->start = start;
	this->end = end;
}

int suffixTree::suffixLength() {
	return *end - start + 1;
}

void suffixTree::addCharacterToTree(int pos){
	++numSufToAdd;

	std::shared_ptr<suffixTree> cur = root;
	std::shared_ptr<suffixTree> link = root;

	while (numSufToAdd > 0) {

		if (activePoint.length == 0) {
			activePoint.c = pos;
		}

		int c = text[activePoint.c] - 'a';
		if (!activePoint.node->children[c]) {
			activePoint.node->children[c] = std::make_shared<suffixTree>(pos, &lastChar);

			if (link != root) {
				link->suffixLink = activePoint.node;
				link = root;
			}
			else link = activePoint.node;
		}
		else {

			if (activePoint.length >= activePoint.node->children[c]->suffixLength()) {
				int length = activePoint.node->children[c]->suffixLength();
				activePoint.length -= length;
				activePoint.node = activePoint.node->children[c];
				activePoint.c += length;
				continue;
			}

			if (text[activePoint.node->children[c]->start + activePoint.length] == text[pos]) {
				activePoint.length++;

				if (link != root) link->suffixLink = activePoint.node;
				break;
			}

			cur = activePoint.node->children[c];

			int* position = new int;
			*position = cur->start + activePoint.length - 1;
			int next_pos = cur->start + activePoint.length;
			int next_c = text[next_pos] - 'a';
			int cur_c = text[pos] - 'a';

			std::shared_ptr<suffixTree> curNode = std::make_shared<suffixTree>(pos, &lastChar);
			std::shared_ptr<suffixTree> nextNode = std::make_shared<suffixTree>(cur->start, position);

			activePoint.node->children[c] = nextNode;
			cur->start = next_pos;
			nextNode->children[next_c] = cur;
			nextNode->children[cur_c] = curNode;

			if (link != root) link->suffixLink = nextNode;
			link = nextNode;
		}

		--numSufToAdd;

		if (activePoint.node == root && activePoint.length > 0) {
			activePoint.length--;
			activePoint.c = pos - numSufToAdd + 1;
		}
		else {
			activePoint.node = activePoint.node->suffixLink;
		}
	}
}

void suffixTree::linearizeTheCyclicString() {
	suffixTree* cur = root.get();
	int size = 0;
	for(;;) {
		for (int i = 0; i < alphabetSize; ++i) {
			if (cur->children[i]) {
				cur = cur->children[i].get();
				for (int k = cur->start; k <= *(cur->end); ++k) {
					if (size < sizeText) std::cout << text[k];
					else {
						std::cout << std::endl;
						return;
					}
					++size;
				}				
				break;
			}
		}
	}
}

void suffixTree::setSuffixLink() {
	suffixLink = root;
}

int main() {
	std::ios::sync_with_stdio(false);
	int tmp = -1;
	std::cin >> text;
	lastChar = -1;
	numSufToAdd = 0;

	root = std::make_shared<suffixTree>(-1, &tmp);
	root->setSuffixLink();

	activePoint.length = 0;
	activePoint.node = root;

	sizeText = text.size();
	text += text;
	for (int i = 0; i < 2 * sizeText; ++i) {
		++lastChar;
		root->addCharacterToTree(lastChar);
	}
	root->linearizeTheCyclicString();

	return 0;
}
