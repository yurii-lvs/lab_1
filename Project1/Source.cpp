#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

typedef struct TEACHER {
	int departament;
	int status;
	char* fam;
	char* name;
	char* father;
} Teacher;

void printTable() {
	printf("%s\n", "");
	printf("%s", "Фамилия");
	printf("%18s", "Имя");
	printf("%23s", "Отчество");
	printf("%22s", "Кафедра");
	printf("%28s\n", "Ученое звание");
	for (int i = 0; i < 98; i++) {
		printf("%s", "-");
	}
	printf("%s\n", "");
}

void newTeacher(Teacher** t, int n) {
	printf("%s\n", "");
	printf("%s\n", "Добаваление нового преподавателя");
	*t = (Teacher*)realloc(*t, (n + 1) * sizeof(Teacher));
	printf("%s", "Введите кафедру (1-ИПОВС, 2-ВМ, 3-ВТ): ");
	scanf("%d", &(t[0][n].departament));
	char buff[100];
	while (getchar() != '\n');
	printf("%s", "Введите фамилию: ");
	gets_s(buff);
	t[0][n].fam = (char*)malloc(strlen(buff) + 1);
	strcpy(t[0][n].fam, buff);
	printf("%s", "Введите имя: ");
	gets_s(buff);
	t[0][n].name = (char*)malloc(strlen(buff) + 1);
	strcpy(t[0][n].name, buff);
	printf("%s", "Введите отчество: ");
	gets_s(buff);
	t[0][n].father = (char*)malloc(strlen(buff) + 1);
	strcpy(t[0][n].father, buff);
	printf("%s", "Введите ученое звание (1- преподаватель, 2- доцент,3-доктор наук): ");
	scanf("%d", &(t[0][n].status));
}

void printTeacher(Teacher* t, int i)
{
	printf("%s", t[i].fam);
	for (int j = 0; j < 15 - strlen(t[i].fam) + 7; j++) printf("%s", " ");
	printf("%s", t[i].name);
	for (int j = 0; j < 15 - strlen(t[i].name) + 3; j++) printf("%s", " ");
	printf("%s", t[i].father);
	int temp = 0;
	for (int j = 0; j < 15 - strlen(t[i].father) + 8; j++) printf("%s", " ");
	if (t[i].departament == 1) printf("%s", "ИПОВС");
	if (t[i].departament == 2) printf("%s", "ВМ");
	if (t[i].departament == 3) printf("%s", "ВТ");
	if (t[i].departament == 1) temp = 5;
	if (t[i].departament == 2) temp = 2;
	if (t[i].departament == 3) temp = 2;
	for (int j = 0; j < 15 - temp + 7; j++) printf("%s", " ");
	if (t[i].status == 1) printf("%s\n", "преподаватель");
	if (t[i].status == 2) printf("%s\n", "доцент");
	if (t[i].status == 3) printf("%s\n", "доктор наук");

}

void printAllTeachers(Teacher* t, int n) {
	printf("%s\n", "");
	printf("%s", "Список всех преподавателей");
	printTable();
	for (int i = 0; i < n; i++) {
		printTeacher(t, i);
	}
	for (int i = 0; i < 98; i++) {
		printf("%s", "-");
	}
	printf("%s\n", "");
}

void searchTeacher(Teacher* t, int n) {
	printf("%s\n", "");
	printf("%s\n", "Поиск преподавателя по фио");
	char sur[100]; char im[100]; char ot[100];
	printf("%s", "Введите фамилию: ");
	while (getchar() != '\n');
	gets_s(sur);
	printf("%s", "Введите имя: ");
	gets_s(im);
	printf("%s", "Введите отчество: ");
	gets_s(ot);
	int temp1 = -1, temp2 = -1, temp3 = -1;
	for (int i = 0; i < n; i++) {
		if (strcmp(t[i].fam, sur) == 0) temp1 = i;
		if (strcmp(t[i].name, im) == 0) temp2 = i;
		if (strcmp(t[i].father, ot) == 0) temp3 = i;
	}
	if (temp1 != -1 && temp2 != -1 && temp3 != -1) {
		if (temp1 == temp2 && temp2 == temp3)
		{
			printTable();
			printTeacher(t, temp1);
			for (int i = 0; i < 98; i++) {
				printf("%s", "-");
			}
			printf("%s\n", "");
		}
	}
	else
	{
		printf("%s\n", "");
		printf("%s\n", "Такого преподавателя нет!");
	}
}

void filterStatus(Teacher* t, int n) {
	printf("%s\n", "");
	printf("%s\n", "Фильтр по статусу");
	int temp;
	printf("%s", "Введите статус (1- преподаватель, 2- доцент, 3-доктор наук): ");
	scanf("%d", &temp);
	printTable();
	for (int i = 0; i < n; i++) {
		if (t[i].status == temp) printTeacher(t, i);
	}
	for (int i = 0; i < 98; i++) {
		printf("%s", "-");
	}
	printf("%s\n", "");
}

void sortTeachers(Teacher* t, int n) {
	printf("%s\n", "");
	printf("%s\n", "Сортировка");
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = j + 1; i < n; i++)
		{
			if (strcmp(t[j].fam, t[i].fam) > 0)
			{
				swap(t[j].fam, t[i].fam);
				swap(t[j].name, t[i].name);
				swap(t[j].father, t[i].father);
				swap(t[j].status, t[i].status);
				swap(t[j].departament, t[i].departament);
			}
		}
	}
	printAllTeachers(t, n);
}

void loadTeacher(Teacher** t, int* n) {
	FILE* f;
	char buff[100];
	f = fopen("data.txt", "r");
	for (int i = 0; !feof(f)-1; i++) {
		*t = (Teacher*)realloc(*t, (*n + 1) * sizeof(Teacher));
		fscanf(f, "%s", buff);
		t[0][i].departament = atof(buff);
		fscanf(f, "%s", buff);
		t[0][i].fam = (char*)malloc(strlen(buff) + 1);
		strcpy(t[0][i].fam, buff);
		fscanf(f, "%s", buff);
		t[0][i].name = (char*)malloc(strlen(buff) + 1);
		strcpy(t[0][i].name, buff);
		fscanf(f, "%s", buff);
		t[0][i].father = (char*)malloc(strlen(buff) + 1);
		strcpy(t[0][i].father, buff);
		fscanf(f, "%s", buff);
		t[0][i].status = atof(buff);
		(*n)++;
	}
	fclose(f);
}


void saveTeacher(Teacher* t, int n) {
	FILE* f;
	f = fopen("data.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf(f, "%d ", t[i].departament);
		fprintf(f, "%s ", t[i].fam);
		fprintf(f, "%s ", t[i].name);
		fprintf(f, "%s ", t[i].father);
		fprintf(f, "%d ", t[i].status);
	}
	fclose(f);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Teacher* t;
	FILE* f;
	int n = 0, menu;
	t = (Teacher*)malloc(n * sizeof(Teacher));
	if ((f = fopen("data.txt", "r+")) == NULL)
	{
		printf("%s", "Файла нет создание\n");
		f = fopen("data.txt", "w+");
		fclose(f);
	}
	else
	{
		loadTeacher(&t, &n);
		n--;
	}
	while (1) {
		printf("%s\n", "");
		printf("%s\n", "Меню");
		printf("%s\n", "1 - Добавить преподавателя");
		printf("%s\n", "2 - Распечатать информацию о всех преподавателях");
		printf("%s\n", "3 - Поиск преподавателя по фио");
		printf("%s\n", "4 - Фильтр по статусу (найти преподавателей заданного статуса)");
		printf("%s\n", "5 - Сортировка по алфавиту");
		printf("%s\n", "0 - Выход ");
		printf("%s", "Пункт меню: ");
		scanf("%d", &menu);

		switch (menu) {

		case 1: newTeacher(&t, n);
			n++;
			break;

		case 2: printAllTeachers(t, n);

			break;

		case 3: searchTeacher(t, n);

			break;

		case 4: filterStatus(t, n);

			break;

		case 5: sortTeachers(t, n);

			break;

		case 0: saveTeacher(t, n);
			free(t);
			return 0;
			break;

		default:cout << "Введите нужную цифру!" << endl;

			break;

		}
	}
}



