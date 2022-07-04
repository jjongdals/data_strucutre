//201921782 박종원 자료구조 14주차 과제4
#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define M 13

typedef struct {
	char data[20];
} element;

element ht[M];

int random[M] = { 0 };

int changeInt(char data[]) {
	int total = 0, i;

	for (i = 0; data[i] != NULL; i++) {
		total += data[i];
	}
	return total;
}

int h(int x) {
	return x % M;
}

void hashing(char data[]) {
	int n = h(changeInt(data));
	int i = 0, j = 0, x = 0;
	while (i == 0) {
		if (!ht[(n + random[j]) % M].data[0]) {
			for (; data[i] != NULL; i++) {
				ht[(n + random[j]) % M].data[i] = data[i];
			}
			printf("인덱스 %d번에 저장되었습니다.\n\n", (n + random[j]) % M);
		}
		else {
			if (!strcmp(ht[(n + random[j]) % M].data, data)) {
				printf("이미 있는 동물입니다.\n\n");
				x = 1;
				break;
			}
			j++;
			if (j == M) {
				printf("저장공간이 없습니다.");
				x = 1;
				break;
			}
		}
	}
	if (j > 0 && x == 0) {
		printf("Overflow가 발생했습니다.\n\n");
	}
}

void search(char data[]) {
	int i = h(changeInt(data));
	int j = 0;
	while (strcmp(data, ht[(i + random[j]) % M].data)) {
		j++;
		if (j == M) {
			printf("탐색한 동물의 이름은 존재하지 않습니다.\n\n", data);
			break;
		}
	}
	if (!strcmp(data, ht[(i + random[j]) % M].data)) {
		printf("탐색한 동물의 이름은 인덱스 %d번에 있습니다.\n\n", (i + random[j]) % M);
	}
}

void delete(char data[]) {
	int n = h(changeInt(data));
	int j = 0, i;
	while (strcmp(data, ht[(n + random[j]) % M].data)) {
		j++;
		if (j == M) {
			printf("삭제할 데이터가 없습니다.\n\n");
			break;
		}
	}
	if (!strcmp(data, ht[(n + random[j]) % M].data)) {
		for (i = 0; data[i] != NULL; i++) {
			ht[(n + random[j]) % M].data[i] = NULL;
		}
		printf("삭제되었습니다.\n\n");
	}
}

int main() {
	char input = ' ';
	char data[20];
	int x[M], temp = 0;

	srand(time(NULL));
	for (int i = 1; i < M;) {
		temp = rand() % (M - 1) + 1;
		if (x[temp] != 1) {
			random[i] = temp;
			x[temp] = 1;
			i++;
		}
	}

	while (input != 'q') {
		printf("삽입(i), 탐색(s), 삭제(d), 종료(q) : ");
		scanf_s("%c", &input);
		getchar();
		if (input == 'i') {
			printf("저장할 동물의 이름을 입력하세요. : ");
			scanf_s("%s", data, sizeof(data));
			getchar();
			hashing(data);
		}
		else if (input == 's') {
			printf("탐색할 동물의 이름을 입력하세요. : ");
			scanf_s("%s", data, sizeof(data));
			getchar();
			search(data);
		}
		else if (input == 'd') {
			printf("삭제할 동물의 이름을 입력하세요. :");
			scanf_s("%s", data, sizeof(data));
			getchar();
			delete(data);
		}
	}
	printf("종료합니다.\n");

}