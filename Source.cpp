#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
//��� ����� ���� �����, ����� �������� VS �� ������� ���������� ��-�� ���������� ������� scanf

#include <windows.h> //���������� ����� ��� ����� � ������ �� ����� ���������
#include <stdio.h>
#include <string.h>
#include <locale.h> 

struct data
{
	int day; //����
	int month; //�����
	int year; //���
};

void dbSave(const char*, data*, int);
int dbRead(const char*, data*);
void dbShow(data*, int);
void findNewest(data, data*, int);

int main(void)
{
	char trash[100];
	data databaseF[15]; // ������ �� ����� ����������� ������
	FILE* dbFile;
	int menuChoice = -1; //���������� ������ � ����
	int size = dbRead("history.txt", databaseF); //��� ������� ��������� ����������� ���� � ������������ ������
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

			case 1: //����������
				dbShow(databaseF, size);
				printf("\n������� ����� ���� � ������� ��.��.��: ");
				scanf("%d.%d.%d", &databaseF[size].day, &databaseF[size].month, &databaseF[size].year);
				if (databaseF[size].day < 1 || databaseF[size].day > 31 || databaseF[size].month < 1 || databaseF[size].month > 12)
				{
					printf("���� �����������. ����������, ������������� ������.\n");
					menuChoice = -1;
					break;
				}
				else size++;
				menuChoice = -1;
				break;


			case 2: //��������
				dbShow(databaseF, size);
				printf("\n������� ������, ������� ������ �������: ");
				scanf("%d", &dateToDelete);
				if (dateToDelete <= size)
				{
					for (int counter = dateToDelete; counter < size + 1; counter++)
					{
						databaseF[counter - 1] = databaseF[counter];
					}
					size--;
				}
				else printf("����� ������ �� ����������\n");
				menuChoice = -1;
				break;


			case 3: //��������� ����
				findNewest(newest, databaseF, size);
				menuChoice = -1;
				break;


			case 4: //��������� � �����
				dbSave("history.txt", databaseF, size);
				printf("\n������ �������� ������� ������ ���-1 ����� ����\n\n");
				return 1;
				break;


			default:
				break;
			}
		}
		dbShow(databaseF, size);
		printf("\n��������, ��� �� ������ �������\n");
		printf("1. �������� ����� ����\n");
		printf("2. ������� ����\n");
		printf("3. ������� ����� ������� ����\n");
		printf("4. ��������� ��� ������ � ����� �� ���������\n");
		printf("\n�������� ��������: ");
		scanf("%d", &menuChoice);
		SetConsoleCP(866);

		gets_s(trash);
	}
}

void dbShow(data* database, int size)
{
	if (size == 0)
	{
		printf("���� ������\n\n");
		return; //���������� �������
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
	FILE* fileToRead = fopen(fileName, "r"); //�������� ����� ��� ������
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
	FILE* fileToSave = fopen(fileName, "w"); //�������� ����� ��� ������

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
		printf("���� ������\n\n");
		return; //���������� �������
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
	printf("����� ������� ���� - %d.%d.%d\n\n", buffer.day, buffer.month, buffer.year);
}