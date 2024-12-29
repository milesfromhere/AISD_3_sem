#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

pair<int, vector<Item>> rukzak(int capacity, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    vector<Item> selectedItems;
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(items[i - 1]);
            w -= items[i - 1].weight;
        }
    }

    return { dp[n][capacity], selectedItems };
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    int n, capacity;
    cout << "Введите вместимость рюкзака (N): ";
    cin >> capacity;
    if (capacity == 0) {
        cout << "Некорректные данные.";
        return 0;
    }
    cout << "Введите количество товаров: ";
    cin >> n;
    if (n == 0) {
        cout << "Некорректные данные.";
        return 0;
    }

    vector<Item> items;
    for (int i = 0; i < n; ++i) {
        Item item;
        cout << "Введите название, вес и стоимость товара #" << i + 1 << ": ";
        cin >> item.name >> item.weight >> item.value;
        items.push_back(item);
    }

    // Решение задачи
    auto result = rukzak(capacity, items);

    // Вывод результата
    cout << "Максимальная стоимость: " << result.first << endl;
    cout << "Предметы в рюкзаке:" << endl;
    for (const auto& item : result.second) {
        cout << "- " << item.name << " (вес: " << item.weight << ", стоимость: " << item.value << ")" << endl;
    }

    return 0;
}