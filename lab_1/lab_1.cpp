#include <iostream>
#include <chrono>
#include <locale>

using namespace std;
using namespace std::chrono;

int moveCount = 0; 

void hanoi(int i, int k, int n) {
    if (n == 1) {
        cout << "Переместить диск 1 со стержня " << i << " на стержень " << k << endl;
        moveCount++; 
    }
    else {
        int tmp = 6 - i - k;
        hanoi(i, tmp, n - 1);
        cout << "Переместить диск " << n << " со стержня " << i << " на стержень " << k << endl;
        moveCount++; 
        hanoi(tmp, k, n - 1);
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int source, destination, c;

    cout << "С какого стержня переместить диски? ";
    cin >> source;

    cout << "На какой стержень переместить диски? ";
    cin >> destination;

    if (source < 1 || source > 4 || destination < 1 || destination > 4 || source == destination) {
        cout << "Введены некорректные данные." << endl;
        return 0;
    }

    cout << "Сколько дисков? ";
    cin >> c;

    if (c < 1) {
        cout << "Введены некорректные данные." << endl;
        return 0;
    }

    // Начало отсчёта времени
    auto start = high_resolution_clock::now();

    hanoi(source, destination, c);

    // Конец отсчёта 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Время выполнения: " << duration.count() << " миллисекунд" << endl;
    cout << "Общее количество ходов: " << moveCount << endl; 

    return 0;
}
