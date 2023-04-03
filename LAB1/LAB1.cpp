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
		for (int i = 0; (i < 80 && arrchars[i-1] != '\n'); i++)
		{
			arrchars[i] = getchar();
			count = i;//подсчет количества символов 
		}
		arrchars = (char*)realloc(arrchars, count * sizeof(char));
		arrchars[count] = '\0';
		char* arrchars = _strdup(this->arrchars);
		arrwords[0] = strtok(arrchars, " ");
		for (int i = 1; (i < 40 && arrwords[i - 1] != NULL); i++) 
		{
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

	int len(char** arrwords) {
		int count = 0;
		for (int i = 0; arrwords[i] != NULL; i++)
		{
			count += 1;
		}	
		return count;
	}

	int SortByAlfa(int i) //метод сортировки 
	{
		int k = 0;
		start:
			std::cout << k;
			if (arrwords[i][k] < arrwords[i + 1][k]) {return 1;}
			else if (arrwords[i][k] == arrwords[i + 1][k]) {
				if (k<len(arrwords)) { k+=1; goto start; }
				else {return 1;}}
			else { return 0;}
	}

	void Shellsort() {
		int step = len(arrwords)/2;
		while (step > 0) {
			for (int i = step; i < len(arrwords); i++)//правая i - середина, левая i - начало списка
			{
				int i_right = i;
				int i_left = i_right - step;
				while (i_left >= 0 and i_left!= i_right and SortByAlfa(i_left) == 0) { //[left] > [right] - swap
					//	std::cout << i_left;
					char* temp = arrwords[i_left];
					arrwords[i_left] = arrwords[i_right];
					arrwords[i_right] = temp;
					//free(temp);
					i_right = i_left;
					i_left = i_right - step;
				}
			}
			step /= 2; //уменьшить шаг в 2р
		}
			puts(arrchars);
			for (int i = 0; (i < 40 && arrwords[i] != NULL); i++) {
				puts(arrwords[i]);
			}
	}
		

};


int main()
{
	system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода 
	std::cout << "лабораторная №1\n";
	Sentence sent;
	for (int i = 0; (i < 40 && sent.arrwords[i] != NULL); i++) {
		puts(sent.arrwords[i]);
	}//вывести слова
	puts(sent.arrchars);//вывести предложение
	sent.Shellsort();
	puts(sent.arrchars);//вывести предложение
	sent.clear();
	return 1;
}