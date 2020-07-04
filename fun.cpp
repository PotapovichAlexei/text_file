#include "Header.h"

//��������� ������ ������
char** memTextAlloc(int* rows, int* sizeOfString) {
	char** unit;
	if (*sizeOfString <= 0)* sizeOfString = 128;

	
	unit = (char**)calloc(*rows, sizeof(char*));						// ��������� ������ ��� ������
	if (unit == NULL) return 0;											// �������� �� ��������� ������ ��� ������
	for (int i = 0; i < *rows; i++) {									// ���� �� �������
		*(unit + i) = (char*)calloc(*sizeOfString, sizeof(char));		// ��������� ������ ��� ������� ������
		if (*(unit + i) == NULL) return 0;								// �������� �� ��������� ������ ��� ������� ������
	}
	return unit;																			// ������� ������
}

void rowsText(int* rows) {
	printf("Enter amount of rows: ");
	while (!(scanf_s("%d", rows))) {
		rewind(stdin);
		printf("Input incorrect, please enter again: ");
	}
}
// ������������� ������ ��� �����
char** reallText(char** sourceText, int* rows) {
	char** helpText = NULL;																	// �������� ���������������� ������
	int i, strsize = 0;
	helpText = (char**)calloc(*rows, sizeof(char*));										// ��������� ������ ��� ������
	if (helpText == NULL) return 0;															// �������� �� ��������� ������
	for (i = 0; i < *rows; i++) {
		// ������� ��������� � ������
		while (*(*(sourceText + i) + strsize)) {											// ���������� ����� ������
			strsize++;
		}
		strsize++;
		*(helpText + i) = (char*)realloc(*(sourceText + i), strsize * sizeof(char));		// ������������� ������ ��� ������
		*(sourceText + i) = *(helpText + i);												// ���������� �������� ������ ���������������
		strsize = 0;																		// ��������� ���������� �������� � ������
	}
	return sourceText;
}

// ������� ��� ������ ������ ��������
char* moveSym(char* str, int curr) {
	int step = curr + 1;
	while (str[step + 1] == ' ' || str[step + 1] == '\n') step++;		// ������� �������� � ���������
	for (; str[curr] != '\n' && str[curr] != '\0'; curr++, step++) {	// ����� ������ � ����� step
		str[curr] = str[step];
	}
	return str;
}

// ������� ��� �������� �� ������ ������ �������� � ��������� ����
char** edText(char** text, int rows) {
	int i = 0, j = 0, rowsCount = 0;

	for (rowsCount = 0; rowsCount < rows; ++rowsCount) {																	//���� �� �������

		for (i = 0; text[rowsCount][i] && text[rowsCount][i + 1] != '\n' && text[rowsCount][i + 1] != '\0'; i++) {																				// ���� �� ��������

			while (text[rowsCount][i] != ' ' && text[rowsCount][i] != '\n') i++;										// ������� � ������� 

			if (text[rowsCount][i + 1] == ' ') {																			// ���� 2 ������� ������ � �����  																	
				text[rowsCount] = moveSym(text[rowsCount], i--);															// ����� ������
			}
			else if (text[rowsCount][i + 2] == ' ' || text[rowsCount][i + 2] == '\0' || text[rowsCount][i + 2] == '\n') {	// ���� ������ ���������
				text[rowsCount] = moveSym(text[rowsCount], i--);															// ����� ������	
			}
			else if (text[rowsCount][0] == ' ' && text[rowsCount][1] != ' ' && text[rowsCount][2] != ' ') {					// ���� ������ ������ � ������ - ������
				text[rowsCount] = moveSym(text[rowsCount], i--);															// ����� ������
			}
			else if (i - 1 == 0) {
				i--;
				text[rowsCount] = moveSym(text[rowsCount], i--);															// ���� ������ ������ � ������ - ��������� �������
			}
			//   w   s ds sd   fdds as f ss    ff f    a fsd   gf dd g
			
		}
		i = 0;
		while (text[rowsCount][i] != '\n') i++;

		text[rowsCount][++i] = '\0';
	}
	return text;
}


// ������� ��� ����� � ������ ������
void fill_text(int rows, int size_str, char** text) {
	//int valid_len;
	// ����
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

// �������� � ���������� ����� �������
FILE* fillFile(FILE* pointer, int rows, char** text, char* name) {
	//fopen_s(&pointer, name, "w+");									// �������� ����� pointer
	pointer = fopen(name, "w+");
	if (!pointer) return 0;
	for (int i = 0; i < rows; i++) fprintf(pointer, "%s", text[i]);	// ���������� ����� pointer
	fclose(pointer);										// �������� ����� pointer
	return pointer;
}

// ������������ ������ ���������� ��� �����
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

//������� ������ ���������� �� ����� �� �����
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


//������������ ���������
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