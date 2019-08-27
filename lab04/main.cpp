#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int lengthStr = 17; // ����� ������ � ����������� �����

int sizeS = 4;
int* S; // ������, �������� �������� �������� ���-�� ���� �� i+1-�� ������
int sizeP = 4;
int* P; // ������ ��� ����������� ��������������� ������� � ������ (��� C[] � ��������)
int k = 0; // ���������� ��������
int numWord = 0; // ���-�� ���� � ������
int numQues = 0; // ���-�� ��������� ��������, ������������� ������

struct keywordTree;
struct stackState { // ���� ��������� ���������
	struct keywordTree* state;
	struct stackState* next;
};

struct stackOccur { // ���� ������� ���������
	int l; // ����� ���������
	struct stackOccur* next;
	struct stackOccur* f;
};

void addS(struct stackState** head, struct keywordTree** state) { // ���������� �������� � ����
	if (!(*head)) {
		(*head) = (struct stackState*)malloc(sizeof(struct stackState));
		(*head)->state = (*state);
		(*head)->next = NULL;
	}
	else {
		struct stackState* tmp = (struct stackState*)malloc(sizeof(struct stackState));
		tmp->state = (*state);
		tmp->next = (*head);
		(*head) = tmp;
	}
}

void addSO(struct stackOccur** head, int l) { // ���������� �������� � ����
	if (!(*head)) {
		(*head) = (struct stackOccur*)malloc(sizeof(struct stackOccur));
		(*head)->l = l;
		(*head)->next = NULL;
		(*head)->f = NULL;
	}
	else {
		struct stackOccur* tmp = (struct stackOccur*)malloc(sizeof(struct stackOccur));
		tmp->l = l;
		tmp->next = (*head);
		tmp->f = NULL;
		(*head) = tmp;
	}
}

/*struct keywordTree* deleteS(struct stackState** head) // �������� �������� �� �����
{
	if ((*head)) {
		struct stackState* tmp = (*head);
		struct keywordTree* s = (*head)->state;
		(*head) = (*head)->next;
		free(tmp);
		return s;
	}
	else return NULL;
}*/

struct keywordTree* deleteS(struct stackState** head) {
	if ((*head)) {
		
		struct stackState* tmp = (*head);
		struct stackState* tmp2 = NULL;
		while (tmp->next) {
			tmp2 = tmp;
			tmp = tmp->next;
		}
		
		struct keywordTree* s = tmp->state;
		free(tmp);
		if (tmp2) tmp2->next = NULL;
		else (*head) = NULL;
		return s;
	}
	else return NULL;
}

struct keywordTree { // ��������� ������ ������ (���)
	char* word; // �����, ��� ������� ��������
	struct stackState* next; // ��������� ��������� (����)
	struct keywordTree* f; // ����� �������
	struct stackOccur* occurrence; // ���������. ���� �� NULL, �� ����� (leaf) ��������� (����)
};

struct keywordTree* KT = NULL;

void addTree(struct keywordTree** KTcur) { // ��������� �������, ��� ��������� ����� ��������	
	struct keywordTree* newKT = (struct keywordTree*)malloc(sizeof(struct keywordTree));
	newKT->f = NULL;
	newKT->next = NULL;
	newKT->occurrence = NULL;
	//newKT->word = (char*)malloc(lengthStr);
	addS(&(*KTcur)->next, &newKT);
}

void deleteTree(struct keywordTree** KTcur) {
	free((*KTcur)->word);
	// ������� ���� ���������
	struct stackOccur* tmp = (*KTcur)->occurrence;
	while (tmp) {
		struct stackOccur* tmp2=tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	struct stackState* s = (*KTcur)->next;
	while (s) {
		deleteTree(&s->state);
		struct stackState* s2 = s->next;
		free(s);
		s = s2;
	}
	free((*KTcur));
}

struct keywordTree* g(struct keywordTree** KTcur, char* word) { // ������� ��� �������� � ������ ���������
	struct stackState* tmp = (*KTcur)->next;
	while (tmp) {
		if (!strcmp(tmp->state->word, word))
			return tmp->state;
		tmp = tmp->next;
	}
	if ((*KTcur) == KT) // ���� ������ � �� ������� ����
		return KT;
	return NULL;
}

void add() { // ���������� �������� ���-�������
	//struct keywordTree* tmp = KT;
	struct keywordTree* curState = KT; // ������� ���������. ���������� � �����
	//int newState = 0; // ���-�� ���������
	struct keywordTree* arc;
	int curWord = 1; // ����� ������� ���������. ���������� � �������
	int curChar = 0; // ����� ������� ������� ������� ��� ���������� ������� ���������
	_Bool isFirst = 1; // ������ �� ������ ���������?
	int first; // ������� ����� ��������� � �������
	char* word = NULL; // ���� ��������� �����
	int length = 0; // ����� ���������
	char c, c_;
	c = c_ = 0; // ����� �� ���� ������� ������������ isalpha, ������ ��� � c_ ����� �����
	while (scanf("%c", &c) == 1) {
		if ((c == 4) || (c == 24)) {
			free(KT); // �������� ������ ����� ����������
			free(S);
			exit(0); // ���� ��� ����� ������ ����, �� ��������� ���������� ���������
		}
		if (c == '?') {
			++numQues;
			++curWord;
			if (!isFirst) { // ���� �� ������ ������ ���������, �� 
				addSO(&curState->occurrence, first+length); //  ��������� ��������� ��������� � �������
				isFirst = 1;
				++k;
			}
			curState = KT;
			curChar = 0;
			length = 0;
		}
		if (isalpha(c)) {
			if (c < 97) c += 32; // �������� ������� ����
			if (isFirst) { // ���� ������ ������, �� ����������� ��������� �� ����� � �������
				first = curWord;
				isFirst = 0;
			}
			if (!word) word = (char*)malloc(lengthStr);
			word[curChar++] = c;
		}
		else if (isalpha(c_)) { 
			numQues = 0;
			word[curChar] = 0; // ��������� �����
			curChar = 0; // ������� �������� ������� ������
			// ������� ��� � ������ - �������
			
			arc = g(&curState, word); // ���� ���� ���� ��� ������� �����
			if ((arc != KT) && (arc != NULL)) {
				curState = arc; // ��������� �� ����
			}
			else { // ���� ��� ��������, �� ��������� ����� � �������
				//addQ(&KT[curState].next, ++newState); // ��� �������� ��������� ������� ������� � �����
				addTree(&curState);
				curState = curState->next->state;
				curState->word = word;						
				word = NULL; // ��� ��� ��������� �� ����� ��� ������� ��������, �� ������� ����� ������, � ����� ������� ����� �����
			}
			++curWord;
			++length;
		}
		if (c == '\n') {
			if (!isFirst) { // ���� �� ������ ������ ���������, �� 
				//addQ(KT[curState].occurrence, first); //  ��������� ��������� ��������� � �������
				addSO(&curState->occurrence, first + length);
				isFirst = 1;
				++k;
			};
			break;
		}
		c_ = c;
	}
	{
		KT->f = KT;
		struct stackState* s = NULL;
		struct stackState* tmp = KT->next;
		while (tmp) {
			tmp->state->f = KT;
			addS(&s, &tmp->state);
			tmp = tmp->next;
		}
		while (s) {
			struct keywordTree* r = deleteS(&s);
			tmp = r->next;
			while (tmp) {
				
				struct keywordTree* u = tmp->state;
				char* word = tmp->state->word;
				addS(&s, &u);
				struct keywordTree* v = r->f;
				while (!g(&v, word))
					v = v->f;
				u->f = g(&v, word);
				// out(u) = out(u) || out(f(u))
				if (u->f->occurrence) {
					if (u->occurrence) u->occurrence->f = u->f->occurrence;
					else {
						addSO(&u->occurrence, -1);
						u->occurrence->f = u->f->occurrence;
					}
				}
				tmp = tmp->next;

			}
		}
	}
}

void search() { // ��������� ����� � ���� � ��� ������� - �����
	char* word = (char*)malloc(lengthStr);
	int curStr = 0; // ����� ������� ������. ���������� � ����
	int curWord = 0; // ����� �������� �����
	int curChar = 0; // ������� ������ � �����
	struct keywordTree* q = KT; // ��������� ��������� �������� ������
	char c, c_;
	c_ = 0;
	while (scanf("%c", &c) == 1) {
		if (isalpha(c)) {
			if (c < 97) c += 32; // �������� ������� ����
			word[curChar++] = c;
		}
		else if (isalpha(c_)) {
			++S[curStr];
			++curWord;
			if (curWord == sizeP) {
				int* newP = (int*)malloc(sizeof(int) * sizeP * 2);
				for (int i = 0;i < sizeP;++i)
					newP[i] = P[i];
				for (int i = sizeP; i < sizeP * 2; ++i)
					newP[i] = 0;
				sizeP *= 2;
				int* tmp = P;
				P = newP;
				free(tmp);
			}
			word[curChar] = 0; // ����������� ����
			curChar = 0;
			// ������������ �����
			while (g(&q, word) == NULL)
				q = q->f;
			q = g(&q, word);
			
			struct stackOccur* tmp = q->occurrence;
			while (tmp) {
				if(tmp->l > - 1) if (curWord - tmp->l + 1> -1) ++P[curWord - tmp->l + 1];
				tmp = tmp->next;
			}
			if (q->occurrence) {
				tmp = q->occurrence->f;
				if (tmp) while (tmp) {
					if (tmp->l > -1) if (curWord - tmp->l + 1 > -1) ++P[curWord - tmp->l + 1];
					tmp = tmp->next;
				}
			}
			
		}
		if (c == '\n') {
			++curStr;
			if (curStr == sizeS) { // ���� ������ ��������, �� �������� ���
				int* newS = (int*)malloc(sizeof(int) * sizeS * 2);
				for (int i = 0; i < sizeS; ++i)
					newS[i] = S[i];
				for (int i = sizeS; i < sizeS * 2; ++i)
					newS[i] = 0;
				int* tmp = S;
				sizeS *= 2;
				S = newS;
				free(tmp);
			}
		}
		if ((c == 4) || (c == 24)) break;
		c_ = c;
	}
	free(word);
	numWord = curWord; 
}

void check() { // ��������� ����� ������ � ����� ����� ��� ������� 
	numWord -= numQues;
	if (k == 0)numWord++;
	int z = 0;
	int difference = 0; // ������� 
	for (int i = 0; i < numWord; ++i) {
		if (P[i] == k) {
			int num = i - difference + 1;
			while ((num > S[z])) {
				if (z == sizeS) break;
				if (S[z] == 0) {
					++z;
					continue;
				}
				difference += S[z];
				num -= S[z];
				++z;
			}
			printf("%d, %d\n", z + 1, num);
		}
	}

}


int main() {
	S = (int*)malloc(sizeof(int) * sizeS); 
	for (int i = 0; i < sizeS; ++i)
		S[i] = 0;
	P = (int*)malloc(sizeof(int) * sizeP); // �������� ������ P[] �� ������� ������
	for (int i = 0; i < sizeP; ++i)
		P[i] = 0;
	KT = (struct keywordTree*)malloc(sizeof(struct keywordTree));
	// �������� ���������
	KT->f = NULL;
	KT->next = NULL;
	KT->occurrence = NULL;
	KT->word = NULL; // 16 �������� + ����������� ����
	add();
	search();
	check();
	free(S);
	free(P);
	deleteTree(&KT);

	return 0;
}
