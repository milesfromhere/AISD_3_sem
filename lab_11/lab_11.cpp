#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

bool randomStrategy(const vector<int>& boxes, int prisonerNumber) {
    vector<int> visited;
    for (int i = 0; i < 50; i++) {
        int randomBox;
        do {
            randomBox = rand() % 100;
        } while (find(visited.begin(), visited.end(), randomBox) != visited.end());
        visited.push_back(randomBox);

        if (boxes[randomBox] == prisonerNumber) {
            return true; 
        }
    }
    return false;
}

bool loopStrategy(const vector<int>& boxes, int prisonerNumber) {
    int attempts = 0;
    int currentBox = prisonerNumber - 1;

    while (attempts < 50) {
        if (boxes[currentBox] == prisonerNumber) {
            return true; 
        }
        currentBox = boxes[currentBox] - 1; 
        attempts++;
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(nullptr)); 

    int rounds;
    cout << "Введите количество кругов: ";
    cin >> rounds;

    int randomSuccess = 0; 
    int loopSuccess = 0;   

    for (int round = 0; round < rounds; round++) {
        vector<int> boxes(100);
        for (int i = 0; i < 100; i++) {
            boxes[i] = i + 1;
        }
        random_shuffle(boxes.begin(), boxes.end());

        bool randomAllSuccess = true;
        bool loopAllSuccess = true;

        for (int prisoner = 1; prisoner <= 100; prisoner++) {
            if (!randomStrategy(boxes, prisoner)) {
                randomAllSuccess = false;
            }
            if (!loopStrategy(boxes, prisoner)) {
                loopAllSuccess = false;
            }
        }

        if (randomAllSuccess) randomSuccess++;
        if (loopAllSuccess) loopSuccess++;
    }

    cout << "Результаты после " << rounds << " кругов:\n";
    cout << "Успех случайной стратегии: " << randomSuccess << "\n";
    cout << "Успех стратегии цикла: " << loopSuccess << "\n";

    return 0;
}
