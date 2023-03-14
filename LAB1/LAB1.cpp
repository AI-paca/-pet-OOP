#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Sentence {
public:
	char* arrchars;//сивмвольная строка
	char** arrwords;//упорядоченный набор слов 
	int lenArr = 0;
	class Sentence() //создать абстрактное предложение
	{
		arrchars = (char*)malloc(81 * sizeof(char));
		arrwords = (char**)malloc(41 * sizeof(char*));
		int count;//подсчет количества
		puts("Введи предложение");
		for (int i = 0; (i < 80 && arrchars[i-1] != '\n'); i++) {
			arrchars[i] = getchar();
			count = i;//подсчет количества символов 
		}
		arrchars = (char*)realloc(arrchars, count * sizeof(char));
		arrchars[count] = '\0';
		char* arrchars = _strdup(this->arrchars);
		arrwords[0] = strtok(arrchars, " ");
		for (int i = 1; (i < 40 && arrwords[i - 1] != NULL); i++) {
			arrwords[i] = strtok(NULL, " ");
			count = i;//подсчет количества слов
		}
		arrwords = (char**)realloc(arrwords, (count+1) * sizeof(char*));
		//arrwords[count+1] = 'NULL';
	}
	void clear() //удалить предложение
	//int clear()
	    {
		puts("очистка"); 
		free(arrwords);
		//free(arrchars);
	//return 0;
		}
	void SortByAlfa() //метод сортировки 
	{
		for (int i = 0; i < sizeof(arrwords) - 2; i++) {
			int k = 0;
		start:
			std::cout << k;
			if (arrwords[i][k] < arrwords[i + 1][k]) {
				puts(arrwords[i]);
				char* temp = arrwords[i];
				arrwords[i] = arrwords[i + 1];
				arrwords[i + 1] = temp;
				free(temp);
			}
			else if (arrwords[i][k] == arrwords[i + 1][k]) {
				if (k<sizeof(*arrwords[i])) { k+=1; goto start; }
			else { puts(arrwords[i]); }
		}
			else {
				puts(arrwords[i+1]);
			}
		}
		printf("\n");
	}
};


int main()
{
	system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода 
	std::cout << "лабораторная №1\n";
	Sentence sent;
	puts(sent.arrchars);//вывести предложение
	for (int i = 0; (i < 40 && sent.arrwords[i] != NULL); i++) {
		puts(sent.arrwords[i]);
	}//вывести слова
	sent.SortByAlfa();
	sent.clear();
	return 1;
}