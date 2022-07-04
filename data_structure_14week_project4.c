//201921782 ������ �ڷᱸ�� 14���� ����4
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
			printf("�ε��� %d���� ����Ǿ����ϴ�.\n\n", (n + random[j]) % M);
		}
		else {
			if (!strcmp(ht[(n + random[j]) % M].data, data)) {
				printf("�̹� �ִ� �����Դϴ�.\n\n");
				x = 1;
				break;
			}
			j++;
			if (j == M) {
				printf("��������� �����ϴ�.");
				x = 1;
				break;
			}
		}
	}
	if (j > 0 && x == 0) {
		printf("Overflow�� �߻��߽��ϴ�.\n\n");
	}
}

void search(char data[]) {
	int i = h(changeInt(data));
	int j = 0;
	while (strcmp(data, ht[(i + random[j]) % M].data)) {
		j++;
		if (j == M) {
			printf("Ž���� ������ �̸��� �������� �ʽ��ϴ�.\n\n", data);
			break;
		}
	}
	if (!strcmp(data, ht[(i + random[j]) % M].data)) {
		printf("Ž���� ������ �̸��� �ε��� %d���� �ֽ��ϴ�.\n\n", (i + random[j]) % M);
	}
}

void delete(char data[]) {
	int n = h(changeInt(data));
	int j = 0, i;
	while (strcmp(data, ht[(n + random[j]) % M].data)) {
		j++;
		if (j == M) {
			printf("������ �����Ͱ� �����ϴ�.\n\n");
			break;
		}
	}
	if (!strcmp(data, ht[(n + random[j]) % M].data)) {
		for (i = 0; data[i] != NULL; i++) {
			ht[(n + random[j]) % M].data[i] = NULL;
		}
		printf("�����Ǿ����ϴ�.\n\n");
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
		printf("����(i), Ž��(s), ����(d), ����(q) : ");
		scanf_s("%c", &input);
		getchar();
		if (input == 'i') {
			printf("������ ������ �̸��� �Է��ϼ���. : ");
			scanf_s("%s", data, sizeof(data));
			getchar();
			hashing(data);
		}
		else if (input == 's') {
			printf("Ž���� ������ �̸��� �Է��ϼ���. : ");
			scanf_s("%s", data, sizeof(data));
			getchar();
			search(data);
		}
		else if (input == 'd') {
			printf("������ ������ �̸��� �Է��ϼ���. :");
			scanf_s("%s", data, sizeof(data));
			getchar();
			delete(data);
		}
	}
	printf("�����մϴ�.\n");

}