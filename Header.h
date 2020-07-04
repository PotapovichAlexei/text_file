#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

char** memTextAlloc(int* rows, int* sizeOfString);						//Выделение памяти тексту
char** reallText(char** sourceText, int* rows);							// Перевыделение памяти под текст
char* moveSym(char* str, int curr);										// Функция для сдвига строки символов
char** edText(char** text, int rows);					// Функция для удаления из строки лишних пробелов и одиночных сиволов
void fill_text(int rows, int size_str, char** text);					// Функция для ввода и вывода текста
FILE* fillFile(FILE* pointer, int rows, char** text, char* name);		// Создание и заполнение файла текстом
void freeText(char** text, int rows);									// Освобождение памяти выделенную под текст 
void print_file(char* filename);
int rowsInFile(char* filename);
int endProgram(); 														//Зацикливание программы
void print_text(char** text, int rows);
void rowsText(int* rows);
void output_file(FILE* f, int size);