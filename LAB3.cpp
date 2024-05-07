#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

//SENSOR.DAT 
struct sensor {
    unsigned shifr;
    char name[41];
};

//SUBSYS.DAT 
struct subsys {
    unsigned shifr;
    char name[41];
};

// LINK.IDX
struct link {
    unsigned long sensor_idx;
    unsigned long subsys_idx;
};
class SensorManager {
public:
    FILE* file;

    SensorManager() {
        file = fopen("SENSOR.DAT", "rb+");
        if (!file) {
            file = fopen("SENSOR.DAT", "wb");
            fclose(file);
            file = fopen("SENSOR.DAT", "rb+");
        }
    }

    ~SensorManager() {
        fclose(file);
    }

    void add(sensor s) {
        fseek(file, 0, SEEK_END);
        fwrite(&s, sizeof(sensor), 1, file);
    }

    int get_index(unsigned shifr) {
        sensor s;
        int index = 0;
        fseek(file, 0, SEEK_SET);
        while (fread(&s, sizeof(sensor), 1, file)) {
            if (s.shifr == shifr) return index;
            index++;
        }
        return -1;
    }

    sensor get_sensor(int index) {
        sensor s;
        fseek(file, index * sizeof(sensor), SEEK_SET);
        fread(&s, sizeof(sensor), 1, file);
        return s;
    }
};

class SubsysManager {
public:
    FILE* file;
    SubsysManager() {
        file = fopen("SUBSYS.DAT", "rb+");
        if (!file) {
            file = fopen("SUBSYS.DAT", "wb");
            fclose(file);
            file = fopen("SUBSYS.DAT", "rb+");
        }
    }

    ~SubsysManager() {
        fclose(file);
    }

    void add(subsys s) {
        fseek(file, 0, SEEK_END);
        fwrite(&s, sizeof(subsys), 1, file);
    }

    int get_index(unsigned shifr) {
        subsys s;
        int index = 0;
        fseek(file, 0, SEEK_SET);
        while (fread(&s, sizeof(subsys), 1, file)) {
            if (s.shifr == shifr) 
                return index;
            index++;
        }
        return -1;
    }

    subsys get_subsys(int index) {
        subsys s;
        fseek(file, index * sizeof(subsys), SEEK_SET);
        fread(&s, sizeof(subsys), 1, file);
        return s;
    }
};

class Database {
private:
    FILE* file;

public:
    SensorManager sensorM;
    SubsysManager subsysM;
    Database() {
        file = fopen("LINK.IDX", "rb+");
        if (!file) {
            file = fopen("LINK.IDX", "wb");
            fclose(file);
            file = fopen("SUBSYS.DAT", "rb+");
        }
    }

    void addSensorRecord(unsigned shifr, const char* name) {
        sensor new_sensor{ shifr };
        strncpy(new_sensor.name, name, sizeof(new_sensor.name) - 1);
        sensorM.add(new_sensor);
    }

    void addSubsysRecord(unsigned shifr, const char* name) {
        subsys new_subsys{ shifr };
        strncpy(new_subsys.name, name, sizeof(new_subsys.name) - 1);
        subsysM.add(new_subsys);
    }

    void addLinkRecord(unsigned long sensor_idx, unsigned long subsys_idx) {
        link new_link;
        new_link.sensor_idx = sensor_idx;
        new_link.subsys_idx = subsys_idx;
        fseek(file, 0, SEEK_END);
        fwrite(&new_link, sizeof(link), 1, file);
    }

    subsys get_subsystem_subsys(unsigned shifr) {
        int sensor_index = sensorM.get_index(shifr);
        if (sensor_index == -1) {
            return subsys{ 0000, "Error"};
        }
        link found_link;
        fseek(file, sensor_index * sizeof(link), SEEK_SET);
        fread(&found_link, sizeof(link), 1, file);
        return subsysM.get_subsys(found_link.subsys_idx);
    }

};


int main() {
    int choice = 0;
    Database database;
    while (choice !=-1)
    {
        system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода

        // Отображение меню
        std::cout << "Добро пожаловать в базу данных!" << std::endl;
        std::cout << "1. Добавить запись датчика" << std::endl;
        std::cout << "2. Добавить запись подсистемы" << std::endl;
        std::cout << "3. Добавить запись о ссылке" << std::endl;
        std::cout << "4. Получить подсистему для датчика" << std::endl;
        std::cout << "5. Выход" << std::endl;

        // Проверяем выбор пользователя
        while (choice < 1 || choice > 8) {
            std::cout << "Выберите действие:" << std::endl;
            std::cin >> choice;
        }

        unsigned shifr;
        char name[41];
        // Выполняем выбранную операцию
        switch (choice) {
        case 1:
            // Добавить запись о датчике
            std::cout << "Введите идентификатор датчика: ";
            std::cin >> shifr;
            std::cout << "Введите имя датчика: ";
            std::cin >> name; 
            database.addSensorRecord(shifr, name);
            break;
        case 2:
            // Добавить запись подсистемы
            std::cout << "Введите идентификатор подсистемы: ";
            std::cin >> shifr;
            std::cout << "Введите имя подсистемы: ";
            std::cin >> name;
            database.addSubsysRecord(shifr, name);
            break;
        case 3:
            // Добавить запись ссылки
            std::cout << "Введите идентификатор датчика: ";
            unsigned sensor_idx;
            std::cin >> sensor_idx;
            std::cout << "Введите идентификатор подсистемы: ";
            unsigned subsys_idx;
            std::cin >> subsys_idx; 
            database.addLinkRecord(sensor_idx, subsys_idx);
            break;
        case 4:
            // Получить подсистему для датчика
            std::cout << "Введите идентификатор датчика: ";
            std::cin >> shifr; 
            subsys subsys = database.get_subsystem_subsys(shifr);
            printf("Подсистемой для датчика %d является %s\n", shifr, subsys.name);
            break;
        case 5:
            // Выход
            choice = -1;
        }
        int i = 0;
        sensor sen = database.sensorM.get_sensor(i);
        subsys sub = database.subsysM.get_subsys(i);
        printf("%-10s %-26s %-25s\n", "Index", "Sensor", "Subsystem");
        while (((database.sensorM.get_index(sen.shifr) == i) || (database.subsysM.get_index(sub.shifr) == i))) {
                if ((int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000)) && (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000)))
                    break;
                else if (int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000) || (database.sensorM.get_index(sen.shifr) != i))
                    printf("%-10d %-26s %-5d %-20s\n", i, "", sub.shifr, sub.name);
                else if (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000) || (database.subsysM.get_index(sub.shifr) != i))
                    printf("%-10d %-5d %-20s %-26s\n", i, sen.shifr, sen.name, "");
                else
                    printf("%-10d %-5d %-20s %-5d %-20s\n", i, sen.shifr, sen.name, sub.shifr, sub.name);
                i += 1;
                sen = database.sensorM.get_sensor(i);
                sub = database.subsysM.get_subsys(i);
        }
        std::cin >> choice;
        system("cls");
    }
    return 0;
}
