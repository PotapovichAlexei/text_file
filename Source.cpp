#include "Header.h"
	// Дан символьный файл f.Группы символов, разделенные пробелами(од-
	//ним или несколькими) и не содержащие пробелов внутри себя, будем называть
	//словами.Удалить из файла все однобуквенные слова и лишние пробелы.Ре-
	//зультат записать в файл g.


int main() {
	int c;
	do{
		FILE* f = NULL, * g = NULL;
		char flag, str[100];
		char** text, name_f[] = "sourceText.txt", name_g[] = "editedText.txt";
		int sizeOfString = 128, rows = 0, i = 0, j =0;
		printf("Press 0 (zero) to create file or press 1 (one) to open file:\n");
		rewind(stdin);
		flag = getchar();
		switch (flag){
		case '1': {
				f = fopen(name_f, "r+");
				rows = rowsInFile(name_f);
				text = memTextAlloc(&rows, &sizeOfString);
 				for (i = 0; i < rows; i++) {
					text[i] = fgets(text[i], sizeOfString, f);
					j = 0;
					while (text[i][j]) j++;
					if(text[i][j - 1] != '\n' && j < 128) text[i][j] = '\n';
					//fscanf(f,"%s", text[0]);
				}
				fclose(f);
				reallText(text, &rows);										// Перевыделение памяти под текст
				text = edText(text, rows);									// Редактирование текста
				g = fillFile(g, rows, text, name_g);						// Заполнение файла g
				fclose(g);
				puts("Source file:\n");
				print_file(name_f);
				printf("\nYour edited text:\n\n");
				print_file(name_g);											// Вывод файла на экран
				
				//output_file(g, sizeOfString);
				freeText(text, rows);										// Освобождение памяти выделеную под текст
				
				
				break;
			}
			case '0': {
				rowsText(&rows);
				text = memTextAlloc(&rows, &sizeOfString);					// Выделение памяти под текст
				fill_text(rows, sizeOfString, text);						// Ввод текста
				reallText(text, &rows);										// Перевыделение памяти под текст
				f = fillFile(f, rows, text, name_f);						// Заполнение файла f 
				fclose(f);
				text = edText(text, rows);									// Редактирование текста
				g = fillFile(g, rows, text, name_g);						// Заполнение файла g
				printf("\nYour edited text:\n");							
				print_file(name_g);											// Вывод файла на экран
				fclose(g);
				//print_text(text, rows);										
				freeText(text, rows);										// Освобождение памяти выделеную под текст
				
				
				break;
			}
			default: break;
		}
		
		c = endProgram();
	}while (c != 0);
	return 0;
}	



