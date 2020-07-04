#include "Header.h"

//Выделение памяти тексту
char** memTextAlloc(int* rows, int* sizeOfString) {
	char** unit;
	if (*sizeOfString <= 0)* sizeOfString = 128;

	
	unit = (char**)calloc(*rows, sizeof(char*));						// Выделение памяти под строки
	if (unit == NULL) return 0;											// Проверка на выделение памяти под строки
	for (int i = 0; i < *rows; i++) {									// Цикл по строкам
		*(unit + i) = (char*)calloc(*sizeOfString, sizeof(char));		// Выделение памяти под символы строки
		if (*(unit + i) == NULL) return 0;								// Проверка на выделение памяти под символы строки
	}
	return unit;																			// Возврат текста
}

void rowsText(int* rows) {
	printf("Enter amount of rows: ");
	while (!(scanf_s("%d", rows))) {
		rewind(stdin);
		printf("Input incorrect, please enter again: ");
	}
}
// Перевыделение памяти под текст
char** reallText(char** sourceText, int* rows) {
	char** helpText = NULL;																	// Создание вспомогательного текста
	int i, strsize = 0;
	helpText = (char**)calloc(*rows, sizeof(char*));										// Выделение памяти под строки
	if (helpText == NULL) return 0;															// Проверка на выделение памяти
	for (i = 0; i < *rows; i++) {
		// Подсчет симоволов в строке
		while (*(*(sourceText + i) + strsize)) {											// Нахождение длины строки
			strsize++;
		}
		strsize++;
		*(helpText + i) = (char*)realloc(*(sourceText + i), strsize * sizeof(char));		// Перевыделение памяти под строку
		*(sourceText + i) = *(helpText + i);												// Присвоение основной строке вспомогательную
		strsize = 0;																		// Обнуление количество символов в строке
	}
	return sourceText;
}

// Функция для сдвига строки символов
char* moveSym(char* str, int curr) {
	int step = curr + 1;
	while (str[step + 1] == ' ' || str[step + 1] == '\n') step++;		// Пропуск пробелов и переносов
	for (; str[curr] != '\n' && str[curr] != '\0'; curr++, step++) {	// Сдвиг строки с шагом step
		str[curr] = str[step];
	}
	return str;
}

// Функция для удаления из строки лишних пробелов и одиночных букв
char** edText(char** text, int rows) {
	int i = 0, j = 0, rowsCount = 0;

	for (rowsCount = 0; rowsCount < rows; ++rowsCount) {																	//Цикл по строкам

		for (i = 0; text[rowsCount][i] && text[rowsCount][i + 1] != '\n' && text[rowsCount][i + 1] != '\0'; i++) {																				// Цикл по символом

			while (text[rowsCount][i] != ' ' && text[rowsCount][i] != '\n') i++;										// Начиная с пробела 

			if (text[rowsCount][i + 1] == ' ') {																			// Если 2 пробела подряд и более  																	
				text[rowsCount] = moveSym(text[rowsCount], i--);															// Сдвиг строки
			}
			else if (text[rowsCount][i + 2] == ' ' || text[rowsCount][i + 2] == '\0' || text[rowsCount][i + 2] == '\n') {	// Если символ одиночный
				text[rowsCount] = moveSym(text[rowsCount], i--);															// Сдвиг строки	
			}
			else if (text[rowsCount][0] == ' ' && text[rowsCount][1] != ' ' && text[rowsCount][2] != ' ') {					// Если первый символ в строке - пробел
				text[rowsCount] = moveSym(text[rowsCount], i--);															// Сдвиг строки
			}
			else if (i - 1 == 0) {
				i--;
				text[rowsCount] = moveSym(text[rowsCount], i--);															// Если первый символ в строке - одиночный символЫ
			}
			//   w   s ds sd   fdds as f ss    ff f    a fsd   gf dd g
			
		}
		i = 0;
		while (text[rowsCount][i] != '\n') i++;

		text[rowsCount][++i] = '\0';
	}
	return text;
}


// Функция для ввода и вывода текста
void fill_text(int rows, int size_str, char** text) {
	//int valid_len;
	// Ввод
	printf("Enter your text:\n");
	for (int i = 0; i < rows; i++) {
		rewind(stdin);
		fgets(*(text + i), size_str + 1, stdin);
	}
	system("CLS");
	printf("Your text:\n");
	print_text(text, rows);
}

void print_text(char** text, int rows) {
	for (int i = 0; i < rows; i++) {
		printf("%s", text[i]);
	}
}

// Создание и заполнение файла текстом
FILE* fillFile(FILE* pointer, int rows, char** text, char* name) {
	//fopen_s(&pointer, name, "w+");									// Создание файла pointer
	pointer = fopen(name, "w+");
	if (!pointer) return 0;
	for (int i = 0; i < rows; i++) fprintf(pointer, "%s", text[i]);	// Заполнение файла pointer
	fclose(pointer);										// Закрытие файла pointer
	return pointer;
}

// Освобождение памяти выделенную под текст
void freeText(char** text, int rows) {
	for (int i = 0; i < rows; i++) {
		free(text[i]);
	}
	free(text);
}

void print_file(char* filename) {
	int flag;
	FILE* file = fopen(filename, "r");
	while (!feof(file) && !ferror(file)) {
		flag = getc(file);
		if (flag != EOF) {
			putchar(flag);
		}
	}
	putchar('\n');
	fclose(file);
}

//Функция вывода информации из файла на экран
void output_file(FILE* f, int size)
{
	char *str;
	if(!(str = (char*)malloc(size*sizeof(char)))) return;
	rewind(f);
	
	
	//rewind(f);
	while (!feof(f) && !ferror(f))
	{
		fgets(str, size, f);
		puts(str);
		*str = NULL;
	}
}

int rowsInFile(char* filename) {
	int  rows = 0;
	char flag;
	FILE* file = fopen(filename, "r+");
	while (!feof(file) && !ferror(file)) {
		flag = getc(file);
		if ( flag == '\n') {
			rows++;
		}
	}
	//rows--;
	fclose(file);
	return rows;
}


//Зацикливание программы
int endProgram() {														
	int end, chek = 0;
	puts("\nTo enter text again enter 1, else 0");
	do {
		rewind(stdin);
		chek = scanf_s("%d", &end);
	} while (chek == 0 || (end != 1 && end != 0));
	system("CLS");
	return end;
}