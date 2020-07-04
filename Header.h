#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

char** memTextAlloc(int* rows, int* sizeOfString);						//��������� ������ ������
char** reallText(char** sourceText, int* rows);							// ������������� ������ ��� �����
char* moveSym(char* str, int curr);										// ������� ��� ������ ������ ��������
char** edText(char** text, int rows);					// ������� ��� �������� �� ������ ������ �������� � ��������� �������
void fill_text(int rows, int size_str, char** text);					// ������� ��� ����� � ������ ������
FILE* fillFile(FILE* pointer, int rows, char** text, char* name);		// �������� � ���������� ����� �������
void freeText(char** text, int rows);									// ������������ ������ ���������� ��� ����� 
void print_file(char* filename);
int rowsInFile(char* filename);
int endProgram(); 														//������������ ���������
void print_text(char** text, int rows);
void rowsText(int* rows);
void output_file(FILE* f, int size);