#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>

const int RESIDENTS_COUNT = 5;
const char* FILENAME = "residents2.txt";
const char* RESULT_FILENAME = "results2.txt";

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
        std::cout << "Resident Info: " << firstName << " " << lastName << ", ID: " << id << ", Phone: " << phone << "\n";
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

}
