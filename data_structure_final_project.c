//201921782 박종원 자료구조 기말대체 과제
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define M 500
#define MAX 15
//학생 구조체
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
//학생 정보 hashtable 구현
student ht[M];
//random 배열 구현
int random[M] = { 0 };
//h 함수
int h(int x) {
	return x % M;
}
//학생정보 추가 함수
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
			printf("저장되었습니다.\n\n");
			break;
		}
		else {
			if (ht[(n + random[j]) % M].ID == id) {
				printf("이미 있는 학생입니다.\n\n");
				x = 1;
				break;
			}
			j++;
			if (j == M) {
				printf("저장공간이 없습니다.\n");
				x = 1;
				break;
			}
		}
	}
	if (j > 0 && x == 0) {
		printf("Overflow가 발생했습니다.\n\n");
	}
}
//학생정보검색 함수
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
			printf("학생이 존재하지 않습니다.\n\n");
			break;
		}
	}
	if (id == ht[(i + random[j]) % M].ID) {
		printf("학번: %d\n", ht[(i + random[j]) % M].ID);
		printf("이름: %s\n", ht[(i + random[j]) % M].name);
		printf("학과: %s\n", ht[(i + random[j]) % M].department);
		printf("학년: %d\n", ht[(i + random[j]) % M].schoolYear);
		printf("학점: %.1f\n", ht[(i + random[j]) % M].grade);
		printf("미수강 과목 리스트: \n");

		for (int k = 1; k < 16; k++) {
			if (ht[(i + random[j]) % M].str[k] == 0) {
				printf("%s\n", sub[k - 1]);
			}
		}
	}
}
//학생정보삭제 함수
void deleteStudent(int id) {
	int x, y;
	int n = h(id);
	int j = 0;
	while (id != ht[(n + random[j]) % M].ID) {
		j++;
		if (j == M) {
			printf("삭제할 학생 데이터가 없습니다.\n\n");
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

		printf("삭제되었습니다.\n\n");
	}
}
//학년별학점순위 함수
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
	printf("학번\t\t이름\t\t학점\n");
	for (i = 0; i < count; i++) {
		printf("%d\t\t%s\t\t%.1f\n", A[i].ID, A[i].name, A[i].grade);
	}
}
//file write 함수
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
//메인 함수
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
		printf("학생정보관리 프로그램\n\n");
		printf("===============================\n");
		printf("1. 학생정보검색\n");
		printf("2. 학생정보추가\n");
		printf("3. 학생정보삭제\n");
		printf("4. 학년별 학점순위\n");
		printf("5. 프로그램 종료\n\n");
		printf("===============================\n");
		printf("사용할 번호를 입력하세요: ");
		scanf("%d", &select);
		//검색기능
		if (select == 1) {
			printf("검색할 학생의 학번을 입력하세요: ");
			scanf("%d", &id);
			printf("\n");
			seachStudent(id);
		}
		//추가기능
		else if (select == 2) {
			printf("학번을 입력하세요: ");
			scanf("%d", &id);
			printf("이름을 입력하세요: ");
			scanf("%s", name);
			printf("학과를 입력하세요: ");
			scanf("%s", dept);
			printf("학년을 입력하세요: ");
			scanf("%d", &year);
			printf("학점을 입력하세요: ");
			scanf("%lf", &gpa);
			printf("이수한 과목의 수를 입력하세요: ");
			scanf("%d", &subNum);
			printf("이수한 과목코드 %d개를 입력하세요: \n", subNum);

			for (int i = 0; i < subNum; i++) {
				scanf("%s", subCode[i]);
				strcpy(subCode[i], "");
			}
			addStudent(id, name, dept, year, gpa, subCode, subNum);
		}
		//삭제기능
		else if (select == 3) {
			printf("삭제할 학번을 입력하세요: ");
			scanf("%d", &id);
			deleteStudent(id);
		}
		//검색기능
		else if (select == 4) {
			printf("검색할 학년을 입력하세요: ");
			scanf("%d", &year);
			rankGrade(year);
		}
		//프로그램 종료
		else if (select == 5) {
			printf("프로그램을 종료합니다.\n");
			fileWirte();
			exit(1);
		}
		//이외의 케이스
		else {
			printf("번호를 잘못 입력하셨습니다. 다른 번호를 입력하세요.\n");
		}

	}

	return 0;
}