#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <functional>

void bubbleSort(std::vector<int>& numbers, std::function<bool(int, int)> compare) {
    auto swap = [](int& a, int& b) { std::swap(a, b); };
    int size = numbers.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (compare(numbers[j + 1], numbers[j])) {
                swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& numbers, std::function<bool(int, int)> compare) {
    auto move = [](std::vector<int>& nums, int from, int to) { nums[to] = nums[from]; };
    for (int i = 1; i < numbers.size(); i++) {
        int key = numbers[i];
        int j = i - 1;
        while (j >= 0 && compare(key, numbers[j])) {
            move(numbers, j, j + 1);
            j--;
        }
        numbers[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& numbers, std::function<bool(int, int)> compare) {
    auto swap = [](int& a, int& b) { std::swap(a, b); };
    for (int i = 0; i < numbers.size() - 1; i++) {
        int extremeIdx = i;
        for (int j = i + 1; j < numbers.size(); j++) {
            if (compare(numbers[j], numbers[extremeIdx])) {
                extremeIdx = j;
            }
        }
        swap(numbers[extremeIdx], numbers[i]);
    }
}

void readNumbersFromFile(const std::string& filename, std::vector<int>& numbers) {
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            int number;
            while (ss >> number) {
                numbers.push_back(number);
                if (ss.peek() == ',' || ss.peek() == ' ')
                    ss.ignore();
            }
        }
        file.close();
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku do odczytu." << std::endl;
    }
}

void writeResultsToFile(const std::string& filename, const std::vector<int>& numbers, double timeTaken) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Czas wykonania sortowania: " << timeTaken << " ms\n";
        for (int num : numbers) {
            file << num << " ";
        }
        file << "\n";
        file.close();
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
    }
}

int main() {
    std::vector<int> numbers;
    readNumbersFromFile("input.txt", numbers);

    int choice;
    std::cout << "Wybierz metode sortowania: \n1. Sortowanie babelkowe \n2. Sortowanie przez wstawianie\n3. Sortowanie przez wybieranie\nWybor: ";
    std::cin >> choice;

    bool ascending;
    std::cout << "Wybierz kierunek sortowania: \n1. Rosnaco \n2. Malejaco\nWybor: ";
    int orderChoice;
    std::cin >> orderChoice;
    ascending = (orderChoice == 1);

    auto compare = ascending ? [](int a, int b) { return a < b; } : [](int a, int b) { return a > b; };

    auto start = std::chrono::high_resolution_clock::now();

    switch (choice) {
    case 1:
        bubbleSort(numbers, compare);
        break;
    case 2:
        insertionSort(numbers, compare);
        break;
    case 3:
        selectionSort(numbers, compare);
        break;
    default:
        std::cout << "Nieprawidlowy wybor, prosze wybrac poprawny numer metody sortowania." << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    writeResultsToFile("output.txt", numbers, duration.count());

    std::cout << "Sortowanie zakonczone. Wyniki zapisano w pliku 'output.txt'." << std::endl;

    return 0;
}
