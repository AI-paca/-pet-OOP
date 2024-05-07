#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

//датчик
struct sensor {
    unsigned shifr; // Шифр датчика
    char name[41]; // Имя датчика

    // Оператор для сравнения датчиков по шифру и имени
    bool operator==(const sensor& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

//подсистема
struct subsys {
    unsigned shifr; // Шифр подсистемы
    char name[41]; // Имя подсистемы

    // Оператор для сравнения подсистем по шифру и имени
    bool operator==(const subsys& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

//связь между датчиком и подсистемой
struct link {
    unsigned sensor_idx; // Индекс датчика
    unsigned subsys_idx; // Индекс подсистемы
};


// SensorDatabase class
class SensorDatabase {
private:
    std::vector<sensor*> sensors;

public:

    SensorDatabase() {
        sensors = std::vector<sensor*>();
    }

    // Добавление элемента в базу данных датчиков
    void addItem(sensor* item) {
        sensors.push_back(item);
    }

    // Добавление элемента в базу данных датчиков по шифру и имени
    void addItem(unsigned shifr, const char* name) {
        if (shifr < 100 || shifr > 999) { throw "Некорректный шифр"; } //сгенерировать исключение типа const char*
        try {
            getIndexByshifr(shifr);
        }
        catch (const char* e) { //обработать ближайшее исключение типа const char*
            sensor* new_sensor = new sensor{ shifr };
            strncpy(new_sensor->name, name, sizeof(new_sensor->name) - 1);
            this->addItem(new_sensor);
        }
    }

    // Удаление элемента из базы данных датчиков по шифру
    void deleteItem(unsigned shifr) {
        sensors.erase(std::remove_if(sensors.begin(), sensors.end(),
            [&](sensor* s) {
                bool toRemove = s->shifr == shifr;
                if (toRemove) delete s;
                return toRemove;
            }),
            sensors.end());
    }

    // Получение всех элементов из базы данных датчиков
    std::vector<sensor> getAllItems() {
        std::vector<sensor> items;
        for (auto& item : sensors) {
            items.push_back(*item);
        }
        return items;
    }

    // Получение элемента из базы данных датчиков по индексу
    sensor& operator[](int index) {
        if (index < 0 || index >= sensors.size()) { throw "Некорректный индекс"; }
        return *sensors[index];
    }

    // Получение индекса элемента из базы данных датчиков по шифру
    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < sensors.size(); i++) {
            if (sensors[i]->shifr == shifr) {
                return i;
            }
        }
        throw "Объект не найден";
    }

    ~SensorDatabase() {
        for (auto& item : sensors) {
            delete item;
        }
        sensors.clear();
    }
};

// SubsysDatabase class
class SubsysDatabase {
private:
    std::vector<subsys*> subsyss;

public:

    SubsysDatabase() {
        subsyss = std::vector<subsys*>();
    }

    // Добавление элемента в базу данных подсистем
    void addItem(subsys* item) {
        subsyss.push_back(item);
    }

    // Добавление элемента в базу данных подсистем по шифру и имени
    void addItem(unsigned shifr, const char* name) {
        // Проверяем входные данные
        if (shifr < 10 || shifr > 99) { throw "Некорректный шифр"; }
        try {
            getIndexByshifr(shifr);
        }
        catch (const char* e) {
            // Ожидаемая ошибка. В системе нет такого шифра
            subsys* new_subsys = new subsys{ shifr };
            strncpy(new_subsys->name, name, sizeof(new_subsys->name) - 1);
            this->addItem(new_subsys);
        }
    }

    // Удаление элемента из базы данных подсистем по шифру
    void deleteItem(unsigned shifr) {
        subsyss.erase(std::remove_if(subsyss.begin(), subsyss.end(),
            [&](subsys* s) {
                bool toRemove = s->shifr == shifr;
                if (toRemove) delete s;
                return toRemove;
            }),
            subsyss.end());
    }

    // Получение всех элементов из базы данных подсистем
    std::vector<subsys> getAllItems() {
        std::vector<subsys> items;
        for (auto& item : subsyss) {
            items.push_back(*item);
        }
        return items;
    }

    // Получение элемента из базы данных подсистем по индексу
    subsys& operator[](int index) {
        if (index < 0 || index >= subsyss.size()) { throw "Некорректный индекс"; }
        return *subsyss[index];
    }

    // Получение индекса элемента из базы данных подсистем по шифру
    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < subsyss.size(); i++) {
            if (subsyss[i]->shifr == shifr) {
                return i;
            }
        }
        throw "Объект не найден";
    }

    ~SubsysDatabase() {
        for (auto& item : subsyss) {
            delete item;
        }
        subsyss.clear();
    }
};

class Database {
private:
    // Вектор связей между датчиками и подсистемами
    std::vector<link*> links;
public:
    // Добавление связи между датчиком и подсистемой
    void addLink(unsigned sensorIndex, unsigned subsysIndex) {
        link* newLink = new link{ sensorIndex, subsysIndex };
        links.push_back(newLink);
    }

    // Удаление ссылки по индексу датчика
    void removeLinkBySensorIndex(unsigned sensorIndex) {
        links.erase(std::remove_if(links.begin(), links.end(),
            [sensorIndex](const link* link) {
                bool toRemove = (link->sensor_idx == sensorIndex);
                if (toRemove) delete link;
                return toRemove;
            }),
            links.end());
    }

    // Удаление всех ссылок, относящихся к определенной подсистеме
    void removeAllLinksBySubsystemIndex(unsigned subsystemIndex) {
        links.erase(std::remove_if(links.begin(), links.end(),
            [subsystemIndex](const link* link) {
                bool toRemove = (link->subsys_idx == subsystemIndex);
                if (toRemove) delete link;
                return toRemove;
            }),
            links.end());
    }

    // Получение всех ссылок из базы данных
    std::vector<link> getAllLinks() {
        std::vector<link> allLinks;
        for (const auto& link : links) {
            allLinks.push_back(*link);
        }
        return allLinks;
    }

    // Проверяем, используется ли датчик в какой-либо ссылке
    bool isSensorUnused(unsigned sensorIndex) {
        for (const auto& link : links) {
            if (link->sensor_idx == sensorIndex) {
                return false;
            }
        }
        return true;
    }

    // Получение индексов датчиков, относящихся к определенной подсистеме, по индексу подсистемы
    std::vector<unsigned> getSensorIndexesBySubsysIndex(unsigned subsysIndex) {
        std::vector<unsigned> sensorIndexes;
        for (const auto& link : links) {
            if (link->subsys_idx == subsysIndex) {
                sensorIndexes.push_back(link->sensor_idx);
            }
        }
        return sensorIndexes;
    }

    // Обновление индексов датчиков после удаления элемента из вектора sensor_db
    void updateSensorIndices(unsigned deletedSensorIndex) {
        for (auto& link : links) {
            if (link->sensor_idx > deletedSensorIndex) {
                link->sensor_idx--;
            }
        }
    }

    // Деструктор, освобождающий ресурсы, занятые объектами подсистем
    ~Database() {
        for (auto& link : links) {
            delete link;
        }
        links.clear();
    }

};


void printSensorsAndSubsystems(SensorDatabase& sensorDatabase, SubsysDatabase& subsysDatabase) {
    int i = 0;
    std::vector<sensor> sensors = sensorDatabase.getAllItems();
    std::vector<subsys> subsyss = subsysDatabase.getAllItems();
    printf("%-10s %-26s %-25s\n", "Index", "Sensor", "Subsystem");
    while (i < sensors.size() || i < subsyss.size()) {
        if (i >= sensors.size()) {
            printf("%-10d %-26s %-5d %-20s\n", i, "", subsyss[i].shifr, subsyss[i].name);
        }
        else if (i >= subsyss.size()) {
            printf("%-10d %-5d %-20s %-26s\n", i, sensors[i].shifr, sensors[i].name, "");
        }
        else {
            printf("%-10d %-5d %-20s %-5d %-20s\n", i, sensors[i].shifr, sensors[i].name, subsyss[i].shifr, subsyss[i].name);
        }
        i += 1;
    }
}
void printLinks(Database& database) {
    std::vector<link> links = database.getAllLinks();
    printf("%-10s %-26s %-25s\n", "Index", "Sensor Index", "Subsystem Index");
    for (int i = 0; i < links.size(); i++) {
        printf("%-10d %-26d %-25d\n", i, links[i].sensor_idx, links[i].subsys_idx);
    }
}


int LAB4() {

    system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода

    SensorDatabase sensor_db;
    SubsysDatabase subsys_db;
    Database link_db;

    int choice = 0;
    char name[256];
    unsigned shifr;

    while (choice != 9)
    {
        // Отображение меню
        std::cout << "1. Добавить запись датчика" << std::endl;
        std::cout << "2. Добавить запись подсистемы" << std::endl;
        std::cout << "3. Удалить запись датчика" << std::endl;
        std::cout << "4. Удалить запись подсистемы" << std::endl;
        std::cout << "5. Включение датчика в подсистему." << std::endl;
        std::cout << "6. Исключение датчика из подсистемы." << std::endl;
        std::cout << "7. Удаление записей неиспользуемых датчиков из списка датчиков." << std::endl;
        std::cout << "8. Вывод на экран по заданному шифру подсистемы списка входящих в неё датчиков" << std::endl;
        std::cout << "9. Выход" << std::endl;
        if (choice == 0)
            goto start;
        try {
            switch (choice) {
            case 1:
                // Добавить запись датчика
                std::cout << "Введите шифр датчика: ";
                std::cin >> shifr;
                std::cout << "Введите имя датчика: ";
                std::cin >> name;
                sensor_db.addItem(shifr, name);
                break;
            case 2:
                // Добавить запись подсистемы
                std::cout << "Введите шифр подсистемы: ";
                std::cin >> shifr;
                std::cout << "Введите имя подсистемы: ";
                std::cin >> name;
                subsys_db.addItem(shifr, name);
                break;
            case 3:
                // Удалить запись о датчике.
                std::cout << "Введите шифр датчика для удаления: ";
                std::cin >> shifr;
                sensor_db.deleteItem(shifr);
                break;
            case 4:
                // Удалить запись подсистемы.
                std::cout << "Введите шифр подсистемы для удаления: ";
                std::cin >> shifr;
                subsys_db.deleteItem(shifr);
                break;
            case 5:
                //Включение датчика в подсистему.
                std::cout << "Введите индекс датчика: ";
                unsigned sensor_idx;
                std::cin >> sensor_idx;
                std::cout << "Введите индекс подсистемы: ";
                unsigned subsys_idx;
                std::cin >> subsys_idx;
                link_db.addLink(sensor_idx, subsys_idx);
                printLinks(link_db);
                break;
            case 6:
                //Исключение датчика из подсистемы.
                std::cout << "Введите шифр датчика для удаления из подсистемы: ";
                std::cin >> shifr;
                link_db.removeLinkBySensorIndex(sensor_db.getIndexByshifr(shifr));
                printLinks(link_db);
                break;
            case 7:
                //Удаление записей неиспользуемых датчиков из списка датчиков
                for (int i = 0; i < sensor_db.getAllItems().size(); i++) {
                    if (link_db.isSensorUnused(i)) {
                        sensor_db.deleteItem(sensor_db.getAllItems()[i].shifr);
                        link_db.updateSensorIndices(i);
                    }
                }
                printLinks(link_db);
                break;
            case 8:
                //Вывести список датчиков, включенных в подсистему по указанному шифру.
                std::cout << "Введите шифр подсистемы: ";
                std::cin >> shifr;
                std::vector<unsigned> sensorIndexes = link_db.getSensorIndexesBySubsysIndex(subsys_db.getIndexByshifr(shifr));
                printf("%-10s %-26s\n", "Index", "Sensor");
                for (int i = 0; i < sensorIndexes.size(); i++) {
                    sensor sen = sensor_db[sensorIndexes[i]];
                    printf("%-10d %-5d %-20s\n", i, sen.shifr, sen.name);
                }
                break;
            }
            printSensorsAndSubsystems(sensor_db, subsys_db);
        }
        catch (const char* e) { std::cerr << "Ошибка: " << e << std::endl; } //обработать ближайшее исключение типа const char*
    start:
        std::cin >> choice;
        //Проверяем выбор пользователя
        while (choice < 1 || choice > 9) {
            std::cout << "Выберите действие:" << std::endl;
            std::cin >> choice;
        }
        system("cls");
    }
    return 0;
}