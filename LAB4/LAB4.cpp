//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

struct sensor {
    unsigned shifr;
    char name[41];
    // Это объект sensorа.
};

struct subsys {
    unsigned shifr;
    char name[41];
    // Это объект подсистемы.
};

// LINK.IDX
struct link {
    unsigned long sensor_idx;
    unsigned long subsys_idx;
};

class SensorManager {
public:
    std::vector<sensor> sensors;

    SensorManager() {
    }

    ~SensorManager() {
    }

    // добавляет sensor в менеджер sensorов.
    void add(sensor s) {
        sensors.push_back(s);
    }

    // получает индекс sensorа в менеджере sensorов.
    int get_index(unsigned shifr) {
        int index = 0;
        for (sensor s : sensors) {
            if (s.shifr == shifr) return index;
            index++;
        }
        return -1;
    }

    // получает sensor по его индексу в менеджере sensorов.
    sensor get_sensor(int index) {
        return sensors[index];
    }

    // добавляет запись о sensorе в менеджер sensorов.
    void addSensorRecord(unsigned shifr, const char* name) {
        sensor new_sensor{ shifr };
        std::strncpy(new_sensor.name, name, sizeof(new_sensor.name) - 1);
        add(new_sensor);
    }

    // удаляет sensor из менеджера sensorов.
    void remove(unsigned shifr) {
        int sensor_index = get_index(shifr);
        if (sensor_index == -1) {
            return;
        }
        sensors.erase(sensors.begin() + sensor_index);
    }

    // получает все sensorи в менеджере sensorов.
    std::vector<sensor> getSensors() {
        return sensors;
    }
};

class SubsysManager {
public:
    std::vector<subsys> subsyss;

    SubsysManager() {
    }

    ~SubsysManager() {
    }

    // добавляет подсистему в менеджер подсистем.
    void add(subsys s) {
        subsyss.push_back(s);
    }

    // получает индекс подсистемы в менеджере подсистем.
    int get_index(unsigned shifr) {
        int index = 0;
        for (subsys s : subsyss) {
            if (s.shifr == shifr) return index;
            index++;
        }
        return -1;
    }

    // получает подсистему по ее индексу в менеджере подсистем.
    subsys get_subsys(int index) {
        return subsyss[index];
    }

    // добавляет запись о подсистеме в менеджер подсистем.
    void addSubsysRecord(unsigned shifr, const char* name) {
        subsys new_subsys{ shifr };
        std::strncpy(new_subsys.name, name, sizeof(new_subsys.name) - 1);
        add(new_subsys);
    }

    // удаляет подсистему из менеджера подсистем.
    void remove(unsigned shifr) {
        for (int i = 0; i < subsyss.size(); i++) {
            if (subsyss[i].shifr == shifr) {
                subsyss.erase(subsyss.begin() + i);
                break;
            }
        }
    }

    // получает все подсистемы в менеджере подсистем.
    std::vector<subsys> getSubsyss() {
        return subsyss;
    }
};



class Database{
private:
    std::vector<link> links;

public:
    SensorManager sensors;
    SubsysManager subsyss;
    Database() {
    }
    // добавляет связь между sensorом и подсистемой.
    void addLinkRecord(unsigned long sensor_idx, unsigned long subsys_idx) {
        link new_link;
        new_link.sensor_idx = sensor_idx;
        new_link.subsys_idx = subsys_idx;
        links.push_back(new_link);
    }

    // удаляет связь между sensorом и подсистемой.
    void removeLinkRecord(unsigned long sensor_idx, unsigned long subsys_idx) {
        for (int i = 0; i < links.size(); i++) {
            if (links[i].sensor_idx == sensor_idx && links[i].subsys_idx == subsys_idx) {
                links.erase(links.begin() + i);
                break;
            }
        }
    }

    // удаляет sensor из менеджера sensorов и все ссылки, которые его включают.
    void removeSensor(unsigned shifr) {
        int sensor_index = sensors.get_index(shifr);
        if (sensor_index == -1) {
            return;
        }
        sensors.erase(sensors.begin() + sensor_index);
        for (int i = 0; i < links.size(); i++) {
            if (links[i].sensor_idx == sensor_index) {
                links.erase(links.begin() + i);
            }
        }
    }

    // удаляет подсистему из менеджера подсистем и все ссылки, которые включают ее.
    void removeSubsys(unsigned shifr) {
        for (int i = 0; i < subsyss.size(); i++) {
            if (subsyss[i].shifr == shifr) {
                subsyss.erase(subsyss.begin() + i);
                break;
            }
        }
        for (int i = 0; i < links.size(); i++) {
            if (links[i].subsys_idx == shifr) {
                links.erase(links.begin() + i);
            }
        }
    }

    // получает все sensorи в менеджере sensorов.
    std::vector<sensor> getSensors() {
        return sensors;
    }

    // получает все подсистемы в менеджере подсистем.
    std::vector<subsys> getSubsyss() {
        return subsyss;
    }

    // получает все ссылки в базе данных.
    std::vector<link> getLinks() {
        return links;
    }
};

//int main() {
//    Database db;
//
//    db.addSensorRecord(1, "Sensor 1");
//    db.addSensorRecord(2, "Sensor 2");
//    db.addSubsysRecord(1, "Subsystem 1");
//    db.addSubsysRecord(2, "Subsystem 2");
//    db.addLinkRecord(1, 1);
//    db.addLinkRecord(2, 2);
//
//    std::cout << "Sensors: " << std::endl;
//    for (sensor s : db.getSensors()) {
//        std::cout << s.shifr << " " << s.name << std::endl;
//    }
//
//    std::cout << std::endl << "Subsystems: " << std::endl;
//    for (subsys s : db.getSubsyss()) {
//        std::cout << s.shifr << " " << s.name << std::endl;
//    }
//
//    std::cout << std::endl << "Links: " << std::endl;
//    for (link l : db.getLinks()) {
//        std::cout << l.sensor_idx << " " << l.subsys_idx << std::endl;
//    }
//
//    return 0;
//}


//int main() {
    //int choice = 0;
    //Database database;
    //while (choice != -1)
    //{
    //    system("chcp 1251");;//Использовать кириллицу для консольного ввода/вывода

    //    // Отображение меню
    //    std::cout << "Лабораторная №3" << std::endl;
    //    std::cout << "1. Добавить запись sensorа" << std::endl;
    //    std::cout << "2. Добавить запись подсистемы" << std::endl;
    //    std::cout << "3. Добавить запись о ссылке" << std::endl;
    //    std::cout << "4. Получить подсистему для sensorа" << std::endl;
    //    std::cout << "5. Выход" << std::endl;

    //    // Проверяем выбор пользователя
    //    while (choice < 1 || choice > 8) {
    //        std::cout << "Выберите действие:" << std::endl;
    //        std::cin >> choice;
    //    }

    //    unsigned shifr;
    //    char name[41];
    //    // Выполняем выбранную операцию
    //    switch (choice) {
    //    case 1:
    //        // Добавить запись о sensorе
    //        std::cout << "Введите идентификатор sensorа: ";
    //        std::cin >> shifr;
    //        std::cout << "Введите имя sensorа: ";
    //        std::cin >> name;
    //        database.addSensorRecord(shifr, name);
    //        break;
    //    case 2:
    //        // Добавить запись подсистемы
    //        std::cout << "Введите идентификатор подсистемы: ";
    //        std::cin >> shifr;
    //        std::cout << "Введите имя подсистемы: ";
    //        std::cin >> name;
    //        database.addSubsysRecord(shifr, name);
    //        break;
    //    case 3:
    //        // Добавить запись ссылки
    //        std::cout << "Введите идентификатор sensorа: ";
    //        unsigned sensor_idx;
    //        std::cin >> sensor_idx;
    //        std::cout << "Введите идентификатор подсистемы: ";
    //        unsigned subsys_idx;
    //        std::cin >> subsys_idx;
    //        database.addLinkRecord(sensor_idx, subsys_idx);
    //        break;
    //    case 4:
    //        // Получить подсистему для sensorа
    //        std::cout << "Введите идентификатор sensorа: ";
    //        std::cin >> shifr;
    //        subsys subsys = database.get_subsystem_subsys(shifr);
    //        printf("Подсистемой для sensorа %d является %s\n", shifr, subsys.name);
    //        break;
    //    case 5:
    //        // Выход
    //        choice = -1;
    //    }
    //    int i = 0;
    //    sensor sen = database.sensorM.get_sensor(i);
    //    subsys sub = database.subsysM.get_subsys(i);
    //    printf("%-10s %-26s %-25s\n", "Index", "Sensor", "Subsystem");
    //    while (((database.sensorM.get_index(sen.shifr) == i) || (database.subsysM.get_index(sub.shifr) == i))) {
    //        if ((int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000)) && (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000)))
    //            break;
    //        else if (int(sen.shifr) <= 0 || (int(sen.shifr) > 6000000) || (database.sensorM.get_index(sen.shifr) != i))
    //            printf("%-10d %-26s %-5d %-20s\n", i, "", sub.shifr, sub.name);
    //        else if (int(sub.shifr) <= 0 || (int(sub.shifr) > 80000000) || (database.subsysM.get_index(sub.shifr) != i))
    //            printf("%-10d %-5d %-20s %-26s\n", i, sen.shifr, sen.name, "");
    //        else
    //            printf("%-10d %-5d %-20s %-5d %-20s\n", i, sen.shifr, sen.name, sub.shifr, sub.name);
    //        i += 1;
    //        sen = database.sensorM.get_sensor(i);
    //        sub = database.subsysM.get_subsys(i);
    //    }
    //    std::cin >> choice;
    //    system("cls");
    //}
    //return 0;
//}
