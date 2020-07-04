#include "Header.h"
	// ��� ���������� ���� f.������ ��������, ����������� ���������(��-
	//��� ��� �����������) � �� ���������� �������� ������ ����, ����� ��������
	//�������.������� �� ����� ��� ������������� ����� � ������ �������.��-
	//������� �������� � ���� g.


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
				reallText(text, &rows);										// ������������� ������ ��� �����
				text = edText(text, rows);									// �������������� ������
				g = fillFile(g, rows, text, name_g);						// ���������� ����� g
				fclose(g);
				puts("Source file:\n");
				print_file(name_f);
				printf("\nYour edited text:\n\n");
				print_file(name_g);											// ����� ����� �� �����
				
				//output_file(g, sizeOfString);
				freeText(text, rows);										// ������������ ������ ��������� ��� �����
				
				
				break;
			}
			case '0': {
				rowsText(&rows);
				text = memTextAlloc(&rows, &sizeOfString);					// ��������� ������ ��� �����
				fill_text(rows, sizeOfString, text);						// ���� ������
				reallText(text, &rows);										// ������������� ������ ��� �����
				f = fillFile(f, rows, text, name_f);						// ���������� ����� f 
				fclose(f);
				text = edText(text, rows);									// �������������� ������
				g = fillFile(g, rows, text, name_g);						// ���������� ����� g
				printf("\nYour edited text:\n");							
				print_file(name_g);											// ����� ����� �� �����
				fclose(g);
				//print_text(text, rows);										
				freeText(text, rows);										// ������������ ������ ��������� ��� �����
				
				
				break;
			}
			default: break;
		}
		
		c = endProgram();
	}while (c != 0);
	return 0;
}	



