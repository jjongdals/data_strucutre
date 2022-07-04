//201921782 ������ �ڷᱸ�� �⸻��ü ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define M 500
#define MAX 15
//�л� ����ü
typedef struct student {
	int ID;
	char name[15];
	char department[10];
	int schoolYear;
	double grade;
	char subCode[20][5];
	char subjectCode[20][5];
	int str[MAX+1];
} student;
//�л� ���� hashtable ����
student ht[M];
//random �迭 ����
int random[M] = { 0 };
//h �Լ�
int h(int x) {
	return x % M;
}
//�л����� �߰� �Լ�
void addStudent(int id, char name[], char dept[], int year, double gpa, char subCode[20][5], int subNum) {
	int a, b, num;
	int n = h(id);
	int i = 0, j = 0, x = 0;
	while (1) {
		if (!ht[(n + random[j]) % M].ID) {
			ht[(n + random[j]) % M].ID = id;
			strcpy(ht[(n + random[j] % M)].name, name);
			strcpy(ht[(n + random[j] % M)].department, dept);
			ht[(n + random[j] % M)].grade = gpa;
			ht[(n + random[j] % M)].schoolYear = year;
			for (i = 0; i < 15; i++) {
				strcpy(ht[(n + random[j] % M)].subjectCode[i], subCode[i]);
				if (subCode[i] != NULL) {
					if (subCode[i][2] != NULL) {
						a = (int)(subCode[i][1]) - 48;
						b = (int)subCode[i][2] - 48;
						num = 10 * a + b;
					}
					else if (subCode[i][2] == NULL) {
						num = (int)(subCode[i][1]) - 48;
					}
					ht[(n + random[j]) % M].str[num] = 1;
				}
			}
			printf("����Ǿ����ϴ�.\n\n");
			break;
		}
		else {
			if (ht[(n + random[j]) % M].ID == id) {
				printf("�̹� �ִ� �л��Դϴ�.\n\n");
				x = 1;
				break;
			}
			j++;
			if (j == M) {
				printf("��������� �����ϴ�.\n");
				x = 1;
				break;
			}
		}
	}
	if (j > 0 && x == 0) {
		printf("Overflow�� �߻��߽��ϴ�.\n\n");
	}
}
//�л������˻� �Լ�
void seachStudent(int id) {

	char sub[15][30] = { "Programming I", "Discrete Mathematics", "Data Structures", "Calculus I",
	   "Calculus II", "linear Algebra", "Analysis of Algorithms", "Assembly language", "Operating Systems",
	   "Programming Languages", "Compiler Design", "Artificial Intelligencce", "Computational Theory",
	   "Parallel Algorithms", "Numberical Analysis" };

	int i = h(id);
	int j = 0;
	while (id != ht[(i + random[j]) % M].ID) {
		j++;
		if (j == M) {
			printf("�л��� �������� �ʽ��ϴ�.\n\n");
			break;
		}
	}
	if (id == ht[(i + random[j]) % M].ID) {
		printf("�й�: %d\n", ht[(i + random[j]) % M].ID);
		printf("�̸�: %s\n", ht[(i + random[j]) % M].name);
		printf("�а�: %s\n", ht[(i + random[j]) % M].department);
		printf("�г�: %d\n", ht[(i + random[j]) % M].schoolYear);
		printf("����: %.1f\n", ht[(i + random[j]) % M].grade);
		printf("�̼��� ���� ����Ʈ: \n");

		for (int k = 1; k < 16; k++) {
			if (ht[(i + random[j]) % M].str[k] == 0) {
				printf("%s\n", sub[k - 1]);
			}
		}
	}
}
//�л��������� �Լ�
void deleteStudent(int id) {
	int x, y;
	int n = h(id);
	int j = 0;
	while (id != ht[(n + random[j]) % M].ID) {
		j++;
		if (j == M) {
			printf("������ �л� �����Ͱ� �����ϴ�.\n\n");
			break;
		}
	}

	if (id == ht[(n + random[j]) % M].ID) {
		ht[(n + random[j]) % M].ID = 0;
		for (y = 0; y < 15; y++) {
			ht[(n + random[j]) % M].name[y] = 0;
		}
		for (y = 0; y < 10; y++) {
			ht[(n + random[j]) % M].department[y] = 0;
		}
		ht[(n + random[j]) % M].grade = 0;
		ht[(n + random[j]) % M].schoolYear = 0.0;
		for (y = 0; y < 20; y++) {
			ht[(n + random[j]) % M].department[y] = 0;
		}
		for (y = 0; y < MAX+1; y++) {
			ht[(n + random[j]) % M].str[y] = 0;
		}

		printf("�����Ǿ����ϴ�.\n\n");
	}
}
//�г⺰�������� �Լ�
void rankGrade(int year) {
	student A[M];
	int u = 0;
	int k, l, i;
	student temp;
	int n = h(ht->ID);
	int count = 0;
	
	for (int p = 0; p < M; p++) {
		if (ht[p].schoolYear == year) {
			A[u++] = ht[p];
			count++;
		}
	}

	for (k = 0; k < count - 1; k++) {
		for (l = 0; l < count - k - 1; l++) {
			if (A[l].grade < A[l+1].grade) {
				temp = A[l];
				A[l] = A[l + 1];
				A[l + 1] = temp;
			}
			else if (A[l].grade == A[l + 1].grade) {
				if (strcmp(A[l].name, A[l+1].name) == 1) {
					temp = A[l];
					A[l] = A[l + 1];
					A[l + 1] = temp;
				}
			}
		}		
	}
	printf("�й�\t\t�̸�\t\t����\n");
	for (i = 0; i < count; i++) {
		printf("%d\t\t%s\t\t%.1f\n", A[i].ID, A[i].name, A[i].grade);
	}
}
//file write �Լ�
void fileWirte() {
	FILE *fp = fopen("student.txt", "w");

	for (int i = 0; i < M; i++) {
		strcpy(ht[i].subCode, "C");
		if (ht[i].ID != 0) {
			fprintf(fp, "%d, %s, %s, %d, %.1f, %s\n",
				ht[i].ID, ht[i].name, ht[i].department,
				ht[i].schoolYear, ht[i].grade, ht[i].subjectCode);
		}
	}
	fclose(fp);
}
//���� �Լ�
int main() {

	int arr[M] = { 0, };
	arr[0] = 1;
	double gpa;
	int select, id, year, subNum, temp = 0, num = 0;
	char name[10], dept[15], subCode[20][5];

	for (int n = 0; n < 20; n++) {
		for (int m = 0; m < 5; m++) {
			subCode[n][m] = NULL;
		}
	}

	srand(time(NULL));
	for (int i = 1; i < M;) {
		temp = rand() % M;
		if (arr[temp] != 1) {
			random[i] = temp;
			arr[temp] = 1;
			i++;
		}
	}
	for (int i = 0; i < M; i++) {
		ht[i].ID = 0;
	}

	while (1) {
		printf("�л��������� ���α׷�\n\n");
		printf("===============================\n");
		printf("1. �л������˻�\n");
		printf("2. �л������߰�\n");
		printf("3. �л���������\n");
		printf("4. �г⺰ ��������\n");
		printf("5. ���α׷� ����\n\n");
		printf("===============================\n");
		printf("����� ��ȣ�� �Է��ϼ���: ");
		scanf("%d", &select);
		//�˻����
		if (select == 1) {
			printf("�˻��� �л��� �й��� �Է��ϼ���: ");
			scanf("%d", &id);
			printf("\n");
			seachStudent(id);
		}
		//�߰����
		else if (select == 2) {
			printf("�й��� �Է��ϼ���: ");
			scanf("%d", &id);
			printf("�̸��� �Է��ϼ���: ");
			scanf("%s", name);
			printf("�а��� �Է��ϼ���: ");
			scanf("%s", dept);
			printf("�г��� �Է��ϼ���: ");
			scanf("%d", &year);
			printf("������ �Է��ϼ���: ");
			scanf("%lf", &gpa);
			printf("�̼��� ������ ���� �Է��ϼ���: ");
			scanf("%d", &subNum);
			printf("�̼��� �����ڵ� %d���� �Է��ϼ���: \n", subNum);

			for (int i = 0; i < subNum; i++) {
				scanf("%s", subCode[i]);
				strcpy(subCode[i], "");
			}
			addStudent(id, name, dept, year, gpa, subCode, subNum);
		}
		//�������
		else if (select == 3) {
			printf("������ �й��� �Է��ϼ���: ");
			scanf("%d", &id);
			deleteStudent(id);
		}
		//�˻����
		else if (select == 4) {
			printf("�˻��� �г��� �Է��ϼ���: ");
			scanf("%d", &year);
			rankGrade(year);
		}
		//���α׷� ����
		else if (select == 5) {
			printf("���α׷��� �����մϴ�.\n");
			fileWirte();
			exit(1);
		}
		//�̿��� ���̽�
		else {
			printf("��ȣ�� �߸� �Է��ϼ̽��ϴ�. �ٸ� ��ȣ�� �Է��ϼ���.\n");
		}

	}

	return 0;
}