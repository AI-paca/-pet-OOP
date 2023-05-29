#include <iostream>
#include <vector>

// Структура, описывающая датчик с полями шифра и имени
struct Sensor {
    unsigned shifr;
    char name[256];

    // Оператор для сравнения датчиков по шифру и имени
    bool operator==(const Sensor& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

// Структура, описывающая подсистему с полями шифра и имени
struct Subsys {
    unsigned shifr;
    char name[256];

    // Оператор для сравнения подсистем по шифру и имени
    bool operator==(const Subsys& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

// Структура, описывающая связь между датчиком и подсистемой
struct Link {
    unsigned sensor_index;
    unsigned subsys_index;
};


// SensorDatabase class
class SensorDatabase {
private:
    std::vector<Sensor*> database;

public:
    void addItem(Sensor* item) {
        database.push_back(item);
    }

    void addItem(unsigned shifr, const char* name) {
                if (shifr < 100 || shifr > 999) { throw "Некорректный шифр"; }
                try {
                    getIndexByshifr(shifr);
                }
                catch (char* e) {
                    this->addItem(shifr, name);
                }
            }

    void deleteItem(const Sensor& item) {
        database.erase(std::remove_if(database.begin(), database.end(),
            [&](Sensor* s) {
                bool toRemove = (*s == item);
                if (toRemove) delete s;
                return toRemove;
            }),
            database.end());
    }

    std::vector<Sensor> getAllItems() {
        std::vector<Sensor> items;
        for (auto& item : database) {
            items.push_back(*item);
        }
        return items;
    }

    Sensor& operator[](int index) {
        if (index < 0 || index >= database.size()) { throw "Некорректный индекс"; }
        return *database[index];
    }

    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < database.size(); i++) {
            if (database[i]->shifr == shifr) {
                return i;
            }
        }
        throw "Объект не найден";
    }

    ~SensorDatabase() {
        for (auto& item : database) {
            delete item;
        }
        database.clear();
    }
};

// SubsysDatabase class
class SubsysDatabase {
private:
    std::vector<Subsys*> database;

public:
    void addItem(Subsys* item) {
        database.push_back(item);
    }

   // Добавить подсис с заданным шифром и именем
    void addItem(unsigned shifr, char* name) {
        // Проверяем входные данные
        if (shifr < 10 || shifr > 99) { throw "Некорректный шифр"; }
        try {
            getIndexByshifr(shifr);
        }
        catch (char* e) {
            // Ожидаемая ошибка. В системе нет такого шифра
        }
    }

    void deleteItem(const Subsys& item) {
        database.erase(std::remove_if(database.begin(), database.end(),
            [&](Subsys* s) {
                bool toRemove = (*s == item);
                if (toRemove) delete s;
                return toRemove;
            }),
            database.end());
    }

    std::vector<Subsys> getAllItems() {
        std::vector<Subsys> items;
        for (auto& item : database) {
            items.push_back(*item);
        }
        return items;
    }

    Subsys& operator[](int index) {
        if (index < 0 || index >= database.size()) { throw "Некорректный индекс"; }
        return *database[index];
    }

    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < database.size(); i++) {
            if (database[i]->shifr == shifr) {
                return i;
            }
        }
        throw "Объект не найден";
    }

    ~SubsysDatabase() {
        for (auto& item : database) {
            delete item;
        }
        database.clear();
    }
};

//template<typename T>
//class DatabaseWithshifr {
//    // Класс для работы с датчиками/подсистемами
//private:
//    std::vector<T*> database;
//public:
//    void addItem(T* item) {
//        database.push_back(item);
//    }
//
//    // Удаление объекта из базы данных
//    void deleteItem(const T& item) {
//        database.erase(std::remove_if(database.begin(), database.end(),
//            [&](T* s) {
//                bool toRemove = (*s == item);
//                if (toRemove) delete s;
//                return toRemove;
//            }),
//            database.end());
//    }
//
//    // Получение всех объектов из базы данных
//    std::vector<T> getAllItems() {
//        std::vector<T> items;
//        for (auto& item : database) {
//            items.push_back(*item);
//        }
//        return items;
//    }
//
//    // Доступ к элементам базы данных по индексу или выброс исключения при недопустимом индексе
//    T& operator[](int index) {
//        if (index < 0 || index >= database.size()) { throw "Некорректный индекс"; }
//        return *database[index];
//    }
//
//    // Получение индекса объекта по его шифру
//    int getIndexByshifr(unsigned shifr) {
//        for (int i = 0; i < database.size(); i++) {
//            if (database[i]->shifr == shifr) {
//                return i;
//            }
//        }
//        throw "Объект не найден";
//    }
//
//    // Деструктор, освобождающий ресурсы, занятые объектами базы данных
//    ~DatabaseWithshifr() {
//        for (auto& item : database) {
//            delete item;
//        }
//        database.clear();
//    }
//};
//
//typedef DatabaseWithshifr<Sensor> _SensorDatabase;
//// Класс для работы с базой данных датчиков
//class SensorDatabase : public _SensorDatabase {
//public:
//    // Добавление датчика с заданным шифром и именем
//    
//};
//typedef DatabaseWithshifr<Subsys> _SubsysDatabase;

//// Класс для работы с базой данных подсистем
//class SubsysDatabase : public _SubsysDatabase {
//public:

//};


class LinkDatabase{
public:
    // Добавление связи между датчиком и подсистемой
    void addLink(unsigned sensorIndex, unsigned subsysIndex) {
      Link* newLink = new Link{ sensorIndex, subsysIndex };
      links.push_back(newLink);
    }


    // Удаление ссылки по индексу датчика
    void removeLinkBySensorIndex(unsigned sensorIndex) {
      links.erase(std::remove_if(links.begin(), links.end(),
        [sensorIndex](const Link* link) {
          bool toRemove = (link->sensor_index == sensorIndex);
          if (toRemove) delete link;
          return toRemove;
        }),
        links.end());
    }


    // Получение всех ссылок из базы данных
    std::vector<Link> getAllLinks() {
      std::vector<Link> allLinks;
      for (const auto& link : links) {
        allLinks.push_back(*link);
      }
      return allLinks;
    }


    // Проверяем, используется ли датчик в какой-либо ссылке
    bool isSensorUnused(unsigned sensorIndex) {
        for (const auto& link : links) {
            if (link->sensor_index == sensorIndex) {
                return false;
            }
        }
        return true;
    }



    // Удаление всех ссылок, относящихся к определенной подсистеме
    void removeAllLinksBySubsystemIndex(unsigned subsystemIndex) {
      links.erase(std::remove_if(links.begin(), links.end(),
        [subsystemIndex](const Link* link) {
          bool toRemove = (link->subsys_index == subsystemIndex);
          if (toRemove) delete link;
          return toRemove;
        }),
        links.end());
    }


    // Получение индексов датчиков, относящихся к определенной подсистеме, по индексу подсистемы
    std::vector<unsigned> getSensorIndexesBySubsysIndex(unsigned subsysIndex) {
      std::vector<unsigned> sensorIndexes;


      for (const auto& link : links) {
        if (link->subsys_index == subsysIndex) {
          sensorIndexes.push_back(link->sensor_index);
        }
      }


      return sensorIndexes;
    }


    // Деструктор, освобождающий ресурсы, занятые объектами подсистем
    ~LinkDatabase() {
      for (auto& link : links) {
        delete link;
      }
      links.clear();
    }


  private:
      // Вектор связей между датчиками и подсистемами
      std::vector<Link*> links;
};
// Функция для безопасного ввода целочисленных значений с выводом сообщения пользователю
int IntInput(const std::string& userMessage) {
    int value;
    bool validInput = false;
    while (!validInput) {
        // Просим пользователя ввести значение, пока оно не станет правильным
        std::cout << userMessage;
        std::cin >> value;
        if (std::cin.fail()) {
            // Если произошла ошибка - очистите входной поток и сообщите пользователю об ошибке
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неправильный ввод. Пожалуйста, введите целое число." << std::endl;
        }
        else validInput = true;
    }
    return value;
}

int main() {
    // Создаем объект SensorDatabase
    SensorDatabase sensorDatabase;

    // Добавьте два датчика в базу данных
    sensorDatabase.addItem(1, "Датчик 1");
    sensorDatabase.addItem(2, "Sensor 2");

    // Получить все датчики из базы данных
    std::vector<Sensor> sensors = sensorDatabase.getAllItems();

    // Выведите имена всех датчиков
    for (const Sensor& sensor : sensors) {
        std::cout << sensor.name << std::endl;
    }

    // Создаем объект SubsysDatabase
    SubsysDatabase subsysDatabase;

    // Добавляем две подсистемы в базу данных
    subsysDatabase.addItem(1, "Подсистема 1");
    subsysDatabase.addItem(2, "Подсистема 2");

    // Получить все подсистемы из базы данных
    std::vector<Subsys> subsys = subsysDatabase.getAllItems();

    // Выведите имена всех подсистем
    for (const Subsys& subsys : subsys) {
        std::cout << subsys.name << std::endl;
    }

    // Создаем объект LinkDatabase
    LinkDatabase linkDatabase;

    // Добавляем связь между датчиком 1 и подсистемой 1
    linkDatabase.addLink(1, 1);

    // Добавление связи между датчиком 2 и подсистемой 2
    linkDatabase.addLink(2, 2);

    // Получить все ссылки из базы данных
    std::vector<Link> links = linkDatabase.getAllLinks();

    // Выведите индексы датчиков и подсистем для всех ссылок
    for (const Link& link : links) {
        std::cout << link.sensor_index << " " << link.subsys_index << std::endl;
    }

    // Возвращаем 0 для индикации успеха
    return 0;
}

//int main() {
//    int choice = 0;
//    Database database;
//    while (choice != -1)
//    {
//        system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода
//
//        // Отображение меню
//        std::cout << "Добро пожаловать в базу данных!" << std::endl;
//        std::cout << "1. Добавить запись датчика" << std::endl;
//        std::cout << "2. Добавить запись подсистемы" << std::endl;
//        std::cout << "3. Добавить запись о ссылке" << std::endl;
//        std::cout << "4. Получить подсистему для датчика" << std::endl;
//        std::cout << "5. Выход" << std::endl;
//
//        // Проверяем выбор пользователя
//        while (choice < 1 || choice > 8) {
//            std::cout << "Выберите действие:" << std::endl;
//            std::cin >> choice;
//        }
//
//        unsigned shifr;
//        char name[41];
//        // Выполняем выбранную операцию
//        switch (choice) {
//        case 1:
//            // Добавить запись о датчике
//            std::cout << "Введите идентификатор датчика: ";
//            std::cin >> shifr;
//            std::cout << "Введите имя датчика: ";
//            std::cin >> name;
//            database.addSensorRecord(shifr, name);
//            break;
//        case 2:
//            // Добавить запись подсистемы
//            std::cout << "Введите идентификатор подсистемы: ";
//            std::cin >> shifr;
//            std::cout << "Введите имя подсистемы: ";
//            std::cin >> name;
//            database.addSubsysRecord(shifr, name);
//            break;
//        case 3:
//            // Добавить запись ссылки
//            std::cout << "Введите идентификатор датчика: ";
//            unsigned sensor_idx;
//            std::cin >> sensor_idx;
//            std::cout << "Введите идентификатор подсистемы: ";
//            unsigned subsys_idx;
//            std::cin >> subsys_idx;
//            database.addLinkRecord(sensor_idx, subsys_idx);
//            break;
//        case 4:
//            // Получить подсистему для датчика
//            std::cout << "Введите идентификатор датчика: ";
//            std::cin >> shifr;
//            subsys subsys = database.get_subsystem_subsys(shifr);
//            printf("Подсистемой для датчика %d является %s\n", shifr, subsys.name);
//            break;
//        case 5:
//            // Выход
//            choice = -1;
//        }
//        int i = 0;
//        sensor sen = database.sensorM.get_sensor(i);
//        subsys sub = database.subsysM.get_subsys(i);
//        printf("%-10s %-26s %-25s\n", "Index", "Sensor", "Subsystem");
//        while (((database.sensorM.get_index(sen.shifr) == i) || (database.subsysM.get_index(sub.shifr) == i))) {
//            if ((int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000)) && (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000)))
//                break;
//            else if (int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000) || (database.sensorM.get_index(sen.shifr) != i))
//                printf("%-10d %-26s %-5d %-20s\n", i, "", sub.shifr, sub.name);
//            else if (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000) || (database.subsysM.get_index(sub.shifr) != i))
//                printf("%-10d %-5d %-20s %-26s\n", i, sen.shifr, sen.name, "");
//            else
//                printf("%-10d %-5d %-20s %-5d %-20s\n", i, sen.shifr, sen.name, sub.shifr, sub.name);
//            i += 1;
//            sen = database.sensorM.get_sensor(i);
//            sub = database.subsysM.get_subsys(i);
//        }
//        std::cin >> choice;
//        system("cls");
//    }
//    return 0;
//}
