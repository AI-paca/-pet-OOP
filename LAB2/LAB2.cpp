#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*Написать программу, которая создаёт в текущем каталоге текстовый файл с
именем, вводимым с клавиатуры, и заполняет его произвольными строками,
которые также вводятся с клавиатуры.После создания исходного файла
необходимо создать новый текстовый файл с именем, вводимым с клавиатуры, в
который строки исходного файла поместить по возрастанию их длин.Для этого
содержимое исходного файла следует полностью переписать в оперативную
память, после чего использовать для их сортировки стандартную функцию
qsort().*/

class Wt_File {//файл на запись
public:
    FILE* file;//Поток доступа на запись
    Wt_File(const char* name) { //коснтруктор
        file = fopen(name, "wt");
    }
    int Write(const char* string) { //запись строки в файл
        if (strlen(string) == 1)
            return 0;
        fputs(string, file);
        return 1;
    }
    ~Wt_File() { //деструктор
        if (file != nullptr) {
            fclose(file);
        }
    }
};

class Rt_File { //файл на чтение 
public:
    FILE* file;//Поток доступа на чтение
    Rt_File(const char* name) { //коснтруктор
        file = fopen(name, "rt");
    }
    char* Read() { //чтение строки из файла
        char* buffer = (char*)calloc(128, sizeof(char));
        if (fgets(buffer, 128, file) == NULL) {
            free(buffer);
            return NULL;
        }
        return buffer;
    }
    ~Rt_File() { //деструктор
        if (file != nullptr) {
            fclose(file);
        }
    }
};

int compare(const void* a, const void* b) { //сравнить длины строк
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strlen(str1) - strlen(str2);
}

char** SortByLen(char** arrstrings, int num) { //сортировка
    qsort(arrstrings, num, sizeof(char*), compare);
    return arrstrings;
}

int LAB2()
{
    system("chcp 1251");
    char filename[16];

    /*исходный файл*/
    std::cout << "Введите имя файла = "; std::cin >> filename; Wt_File w_file(filename);//создать файл на запись
    char string[100]; gets_s(string, 100); while(w_file.Write(strcat(gets_s(string, 100),"\n")));//ввод и запись строк в файл
    w_file.~Wt_File();//закрыть файл на запись

    /*запись содержимого исходного файла в оперативную память*/
    Rt_File r_file(filename); //открыть файл на чтение
    char** arr = (char**)malloc(sizeof(char*)); int len = 0;
    while (char* line = r_file.Read()) { 
        arr = (char**)realloc(arr, sizeof(char*) * (len + 1));
        arr[len] = line;  len += 1;} //записать файл построчно в массив строк

    arr = SortByLen(arr, len); 

    /*новый текстовый файл*/
    std::cout << "Введите имя файла = "; std::cin >> filename; Wt_File w_sortedfile(filename); //создать отсортированный файл на запись
    for (int i = 0; len > i && w_sortedfile.Write(arr[i]); i++); //записать массив в отсортированный файл
    w_sortedfile.~Wt_File(); //закрыть отсортированный файл на запись

    /*вывод строк нового файла*/
    std::cout << "\nОтсортированный файл:\n";
    Rt_File r_sortedfile(filename);  //открыть отсортированный файл на чтение
    while (char* line = r_sortedfile.Read())
        std::cout << line; //вывести отсортированный файл построчно

    return 0;
}