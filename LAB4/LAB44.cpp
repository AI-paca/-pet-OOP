#include <iostream>
#include <vector>

// ���������, ����������� ������ � ������ ����� � �����
struct Sensor {
    unsigned shifr;
    char name[256];

    // �������� ��� ��������� �������� �� ����� � �����
    bool operator==(const Sensor& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

// ���������, ����������� ���������� � ������ ����� � �����
struct Subsys {
    unsigned shifr;
    char name[256];

    // �������� ��� ��������� ��������� �� ����� � �����
    bool operator==(const Subsys& other) const {
        return shifr == other.shifr && strcmp(name, other.name) == 0;
    }
};

// ���������, ����������� ����� ����� �������� � �����������
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
                if (shifr < 100 || shifr > 999) { throw "������������ ����"; }
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
        if (index < 0 || index >= database.size()) { throw "������������ ������"; }
        return *database[index];
    }

    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < database.size(); i++) {
            if (database[i]->shifr == shifr) {
                return i;
            }
        }
        throw "������ �� ������";
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

   // �������� ������ � �������� ������ � ������
    void addItem(unsigned shifr, char* name) {
        // ��������� ������� ������
        if (shifr < 10 || shifr > 99) { throw "������������ ����"; }
        try {
            getIndexByshifr(shifr);
        }
        catch (char* e) {
            // ��������� ������. � ������� ��� ������ �����
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
        if (index < 0 || index >= database.size()) { throw "������������ ������"; }
        return *database[index];
    }

    int getIndexByshifr(unsigned shifr) {
        for (int i = 0; i < database.size(); i++) {
            if (database[i]->shifr == shifr) {
                return i;
            }
        }
        throw "������ �� ������";
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
//    // ����� ��� ������ � ���������/������������
//private:
//    std::vector<T*> database;
//public:
//    void addItem(T* item) {
//        database.push_back(item);
//    }
//
//    // �������� ������� �� ���� ������
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
//    // ��������� ���� �������� �� ���� ������
//    std::vector<T> getAllItems() {
//        std::vector<T> items;
//        for (auto& item : database) {
//            items.push_back(*item);
//        }
//        return items;
//    }
//
//    // ������ � ��������� ���� ������ �� ������� ��� ������ ���������� ��� ������������ �������
//    T& operator[](int index) {
//        if (index < 0 || index >= database.size()) { throw "������������ ������"; }
//        return *database[index];
//    }
//
//    // ��������� ������� ������� �� ��� �����
//    int getIndexByshifr(unsigned shifr) {
//        for (int i = 0; i < database.size(); i++) {
//            if (database[i]->shifr == shifr) {
//                return i;
//            }
//        }
//        throw "������ �� ������";
//    }
//
//    // ����������, ������������� �������, ������� ��������� ���� ������
//    ~DatabaseWithshifr() {
//        for (auto& item : database) {
//            delete item;
//        }
//        database.clear();
//    }
//};
//
//typedef DatabaseWithshifr<Sensor> _SensorDatabase;
//// ����� ��� ������ � ����� ������ ��������
//class SensorDatabase : public _SensorDatabase {
//public:
//    // ���������� ������� � �������� ������ � ������
//    
//};
//typedef DatabaseWithshifr<Subsys> _SubsysDatabase;

//// ����� ��� ������ � ����� ������ ���������
//class SubsysDatabase : public _SubsysDatabase {
//public:

//};


class LinkDatabase{
public:
    // ���������� ����� ����� �������� � �����������
    void addLink(unsigned sensorIndex, unsigned subsysIndex) {
      Link* newLink = new Link{ sensorIndex, subsysIndex };
      links.push_back(newLink);
    }


    // �������� ������ �� ������� �������
    void removeLinkBySensorIndex(unsigned sensorIndex) {
      links.erase(std::remove_if(links.begin(), links.end(),
        [sensorIndex](const Link* link) {
          bool toRemove = (link->sensor_index == sensorIndex);
          if (toRemove) delete link;
          return toRemove;
        }),
        links.end());
    }


    // ��������� ���� ������ �� ���� ������
    std::vector<Link> getAllLinks() {
      std::vector<Link> allLinks;
      for (const auto& link : links) {
        allLinks.push_back(*link);
      }
      return allLinks;
    }


    // ���������, ������������ �� ������ � �����-���� ������
    bool isSensorUnused(unsigned sensorIndex) {
        for (const auto& link : links) {
            if (link->sensor_index == sensorIndex) {
                return false;
            }
        }
        return true;
    }



    // �������� ���� ������, ����������� � ������������ ����������
    void removeAllLinksBySubsystemIndex(unsigned subsystemIndex) {
      links.erase(std::remove_if(links.begin(), links.end(),
        [subsystemIndex](const Link* link) {
          bool toRemove = (link->subsys_index == subsystemIndex);
          if (toRemove) delete link;
          return toRemove;
        }),
        links.end());
    }


    // ��������� �������� ��������, ����������� � ������������ ����������, �� ������� ����������
    std::vector<unsigned> getSensorIndexesBySubsysIndex(unsigned subsysIndex) {
      std::vector<unsigned> sensorIndexes;


      for (const auto& link : links) {
        if (link->subsys_index == subsysIndex) {
          sensorIndexes.push_back(link->sensor_index);
        }
      }


      return sensorIndexes;
    }


    // ����������, ������������� �������, ������� ��������� ���������
    ~LinkDatabase() {
      for (auto& link : links) {
        delete link;
      }
      links.clear();
    }


  private:
      // ������ ������ ����� ��������� � ������������
      std::vector<Link*> links;
};
// ������� ��� ����������� ����� ������������� �������� � ������� ��������� ������������
int IntInput(const std::string& userMessage) {
    int value;
    bool validInput = false;
    while (!validInput) {
        // ������ ������������ ������ ��������, ���� ��� �� ������ ����������
        std::cout << userMessage;
        std::cin >> value;
        if (std::cin.fail()) {
            // ���� ��������� ������ - �������� ������� ����� � �������� ������������ �� ������
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������������ ����. ����������, ������� ����� �����." << std::endl;
        }
        else validInput = true;
    }
    return value;
}

int main() {
    // ������� ������ SensorDatabase
    SensorDatabase sensorDatabase;

    // �������� ��� ������� � ���� ������
    sensorDatabase.addItem(1, "������ 1");
    sensorDatabase.addItem(2, "Sensor 2");

    // �������� ��� ������� �� ���� ������
    std::vector<Sensor> sensors = sensorDatabase.getAllItems();

    // �������� ����� ���� ��������
    for (const Sensor& sensor : sensors) {
        std::cout << sensor.name << std::endl;
    }

    // ������� ������ SubsysDatabase
    SubsysDatabase subsysDatabase;

    // ��������� ��� ���������� � ���� ������
    subsysDatabase.addItem(1, "���������� 1");
    subsysDatabase.addItem(2, "���������� 2");

    // �������� ��� ���������� �� ���� ������
    std::vector<Subsys> subsys = subsysDatabase.getAllItems();

    // �������� ����� ���� ���������
    for (const Subsys& subsys : subsys) {
        std::cout << subsys.name << std::endl;
    }

    // ������� ������ LinkDatabase
    LinkDatabase linkDatabase;

    // ��������� ����� ����� �������� 1 � ����������� 1
    linkDatabase.addLink(1, 1);

    // ���������� ����� ����� �������� 2 � ����������� 2
    linkDatabase.addLink(2, 2);

    // �������� ��� ������ �� ���� ������
    std::vector<Link> links = linkDatabase.getAllLinks();

    // �������� ������� �������� � ��������� ��� ���� ������
    for (const Link& link : links) {
        std::cout << link.sensor_index << " " << link.subsys_index << std::endl;
    }

    // ���������� 0 ��� ��������� ������
    return 0;
}

//int main() {
//    int choice = 0;
//    Database database;
//    while (choice != -1)
//    {
//        system("chcp 1251");;//������������ ��������� ��� ����������� �����/������
//
//        // ����������� ����
//        std::cout << "����� ���������� � ���� ������!" << std::endl;
//        std::cout << "1. �������� ������ �������" << std::endl;
//        std::cout << "2. �������� ������ ����������" << std::endl;
//        std::cout << "3. �������� ������ � ������" << std::endl;
//        std::cout << "4. �������� ���������� ��� �������" << std::endl;
//        std::cout << "5. �����" << std::endl;
//
//        // ��������� ����� ������������
//        while (choice < 1 || choice > 8) {
//            std::cout << "�������� ��������:" << std::endl;
//            std::cin >> choice;
//        }
//
//        unsigned shifr;
//        char name[41];
//        // ��������� ��������� ��������
//        switch (choice) {
//        case 1:
//            // �������� ������ � �������
//            std::cout << "������� ������������� �������: ";
//            std::cin >> shifr;
//            std::cout << "������� ��� �������: ";
//            std::cin >> name;
//            database.addSensorRecord(shifr, name);
//            break;
//        case 2:
//            // �������� ������ ����������
//            std::cout << "������� ������������� ����������: ";
//            std::cin >> shifr;
//            std::cout << "������� ��� ����������: ";
//            std::cin >> name;
//            database.addSubsysRecord(shifr, name);
//            break;
//        case 3:
//            // �������� ������ ������
//            std::cout << "������� ������������� �������: ";
//            unsigned sensor_idx;
//            std::cin >> sensor_idx;
//            std::cout << "������� ������������� ����������: ";
//            unsigned subsys_idx;
//            std::cin >> subsys_idx;
//            database.addLinkRecord(sensor_idx, subsys_idx);
//            break;
//        case 4:
//            // �������� ���������� ��� �������
//            std::cout << "������� ������������� �������: ";
//            std::cin >> shifr;
//            subsys subsys = database.get_subsystem_subsys(shifr);
//            printf("����������� ��� ������� %d �������� %s\n", shifr, subsys.name);
//            break;
//        case 5:
//            // �����
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
