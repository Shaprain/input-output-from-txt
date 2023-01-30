#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
//эта часть кода нужна, чтобы заткнуть VS на предмет исключений из-за устаревшей функции scanf

#include <windows.h> //библиотека нужна для ввода и вывода на одной кодировке
#include <stdio.h>
#include <string.h>
#include <locale.h> 

struct data
{
	int day; //день
	int month; //месяц
	int year; //год
};

void dbSave(const char*, data*, int);
int dbRead(const char*, data*);
void dbShow(data*, int);
void findNewest(data, data*, int);

int main(void)
{
	char trash[100];
	data databaseF[15]; // Массив со всеми хранящимися датами
	FILE* dbFile;
	int menuChoice = -1; //переменная выбора в меню
	int size = dbRead("history.txt", databaseF); //при запуске программы считывается файл и подгружаются данные
	int dateToDelete = 0;

	data newest = {};

	setlocale(LC_ALL, "Rus");

	for (;;)
	{
		SetConsoleCP(1251);
		system("cls");
		if (menuChoice > 0)
		{
			switch (menuChoice)
			{

			case 1: //добавление
				dbShow(databaseF, size);
				printf("\nВведите новую дату в формате дд.мм.гг: ");
				scanf("%d.%d.%d", &databaseF[size].day, &databaseF[size].month, &databaseF[size].year);
				if (databaseF[size].day < 1 || databaseF[size].day > 31 || databaseF[size].month < 1 || databaseF[size].month > 12)
				{
					printf("Ввод некорректен. Пожалуйста, перепроверьте данные.\n");
					menuChoice = -1;
					break;
				}
				else size++;
				menuChoice = -1;
				break;


			case 2: //удаление
				dbShow(databaseF, size);
				printf("\nВведите строку, которую хотите удалить: ");
				scanf("%d", &dateToDelete);
				if (dateToDelete <= size)
				{
					for (int counter = dateToDelete; counter < size + 1; counter++)
					{
						databaseF[counter - 1] = databaseF[counter];
					}
					size--;
				}
				else printf("Такой строки не существует\n");
				menuChoice = -1;
				break;


			case 3: //последняя дата
				findNewest(newest, databaseF, size);
				menuChoice = -1;
				break;


			case 4: //сохранить и выйти
				dbSave("history.txt", databaseF, size);
				printf("\nРаботу выполнил студент группы ИВТ-1 Шаппо Иван\n\n");
				return 1;
				break;


			default:
				break;
			}
		}
		dbShow(databaseF, size);
		printf("\nВыберите, что Вы хотите сделать\n");
		printf("1. Добавить новую дату\n");
		printf("2. Удалить дату\n");
		printf("3. Вывести самую позднюю дату\n");
		printf("4. Сохранить все данные и выйти из программы\n");
		printf("\nЖелаемая операция: ");
		scanf("%d", &menuChoice);
		SetConsoleCP(866);

		gets_s(trash);
	}
}

void dbShow(data* database, int size)
{
	if (size == 0)
	{
		printf("Файл пустой\n\n");
		return; //прерывание функции
	}

	//char bufferString;
	for (int counter = 0; counter < size; counter++)
	{
		printf("%d  ", counter + 1);
		printf("%d.", database[counter].day);
		printf("%d.", database[counter].month);
		printf("%d\n", database[counter].year);
	}
}

int dbRead(const char* fileName, data* database)
{
	FILE* fileToRead = fopen(fileName, "r"); //открытие файла для чтения
	int counter = 0;
	while (!feof(fileToRead))
	{
		fscanf(fileToRead, "%d.%d.%d\n", &database[counter].day, &database[counter].month, &database[counter].year);
		counter++;
	}
	fclose(fileToRead);
	return counter;
}

void dbSave(const char* fileName, data* database, int size)
{
	FILE* fileToSave = fopen(fileName, "w"); //открытие файла для записи

	for (int counter = 0; counter < size; counter++)
	{
		fprintf(fileToSave, "%d.%d.%d\n", database[counter].day, database[counter].month, database[counter].year);
	}
	fclose(fileToSave);
}

void findNewest(data buffer, data* database, int size)
{
	if (size == 0)
	{
		printf("Файл пустой\n\n");
		return; //прерывание функции
	}

	for (int counter = 0; counter < size; counter++)
	{
		if (buffer.year < database[counter].year)
		{
			buffer = database[counter];
		}

		if (buffer.year == database[counter].year)
		{
			if (buffer.month < database[counter].month)
			{
				buffer = database[counter];
			}
		}

		if (buffer.year == database[counter].year)
		{
			if (buffer.month == database[counter].month)
			{
				if (buffer.day < database[counter].day)
				{
					buffer = database[counter];
				}
			}
		}
	}
	printf("Самая поздняя дата - %d.%d.%d\n\n", buffer.day, buffer.month, buffer.year);
}