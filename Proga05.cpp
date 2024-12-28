#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>

const int RESIDENTS_COUNT = 3;
const char* FILENAME = "residents2.txt";
const char* RESULT_FILENAME = "results2.txt";
#include <string>

class VisitorPass {
private:
    std::string firstName;
    std::string lastName;
    std::string id;
    std::string hairColor;
    std::string dressCode;

public:
    void setVisitor(const std::string& firstName, const std::string& lastName,
        const std::string& id, const std::string& hairColor,
        const std::string& dressCode) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = id;
        this->hairColor = hairColor;
        this->dressCode = dressCode;
    }

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
};

class Appearance {
private:
    std::string hairColor;
    std::string clothes;

public:
    Appearance() : hairColor("Unknown"), clothes("Unknown") {}

    void setAppearance(const std::string& hair, const std::string& cloth) {
        hairColor = hair;
        clothes = cloth;
    }

    const std::string& getHairColor() const {
        return hairColor;
    }

    const std::string& getClothes() const {
        return clothes;
    }
};

class Resident {
private:
    std::string firstName;
    std::string lastName;
    std::string id;
    Appearance appearance;
    std::string phone;

public:
    Resident() : firstName("Unknown"), lastName("Unknown"), id("00"), phone("Unknown") {}

    void setResident(const std::string& first, const std::string& last, const std::string& idNum, const std::string& hair, const std::string& cloth, const std::string& phoneNum) {
        firstName = first;
        lastName = last;
        id = idNum;
        appearance.setAppearance(hair, cloth);
        phone = phoneNum;
    }

    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    const std::string& getId() const { return id; }
    const std::string& getPhone() const { return phone; }

    void displayInfo() const {
        std::cout << "Информация о человеке: " << firstName << " " << lastName << ", ID: " << id << ", телефон: " << phone << "\n";
    }
};

class Game {
private:
    Resident residents[RESIDENTS_COUNT];

public:
    Game() {
        try {
            initializeResidents();
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
            exit(1);
        }
    }

    void initializeResidents() {
        std::ifstream file(FILENAME);
        if (!file) {
            throw std::runtime_error("Не удалось открыть файл жильцов.");
        }

        for (int i = 0; i < RESIDENTS_COUNT; ++i) {
            std::string first, last, id, hair, cloth, phone;
            if (file >> first >> last >> id >> hair >> cloth >> phone) {
                residents[i].setResident(first, last, id, hair, cloth, phone);
            }
            else {
                throw std::runtime_error("Ошибка чтения данных из файла.");
            }
        }
        file.close();
    }

    void run() {
        for (int i = 0; i < RESIDENTS_COUNT; ++i) {
            residents[i].displayInfo();
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Game game;
    game.run();

    // Работа с одномерным массивом объектов
    const int visitorCount = 2;
    VisitorPass visitors[visitorCount]{};
    visitors[0].setVisitor("Старушка", "Шапокляк", "12", "Седой", "официальный");
    visitors[1].setVisitor("Крокодил", "Гена", "36", "зеленый", "формальный");

    std::cout << "\nПосетители:\n";
    for (int i = 0; i < visitorCount; ++i) {
        std::cout << "Имя: " << visitors[i].getFirstName() << ", Фамилия: " << visitors[i].getLastName() << "\n";
    }

    // Работа с двумерным массивом объектов
    const int groupCount = 2;
    const int visitorsPerGroup = 2;
    VisitorPass visitorGroups[groupCount][visitorsPerGroup]{};

    visitorGroups[0][0].setVisitor("Group1_Visitor1", "G1_Last1", "01", "Brown", "Casual");
    visitorGroups[0][1].setVisitor("Group1_Visitor2", "G1_Last2", "02", "Black", "Formal");
    visitorGroups[1][0].setVisitor("Group2_Visitor1", "G2_Last1", "03", "Blonde", "Sporty");
    visitorGroups[1][1].setVisitor("Group2_Visitor2", "G2_Last2", "04", "Red", "Casual");

    std::cout << "\nГруппы посетителей:\n";
    for (int i = 0; i < groupCount; ++i) {
        std::cout << "Группа " << (i + 1) << ":\n";
        for (int j = 0; j < visitorsPerGroup; ++j) {
            std::cout << "Имя: " << visitorGroups[i][j].getFirstName() << ", Фамилия: " << visitorGroups[i][j].getLastName() << "\n";
        }
    }

    return 0;

}
