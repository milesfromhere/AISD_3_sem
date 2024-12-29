#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <windows.h>

using namespace std;

const int INF = 1e9;

vector<vector<int>> graph = 
    { { INF, 2, 4, 3, 2, 10, 5, 9},
    { 5, INF, 17, 30, 25, 15, 2, 10},
    { 9, 15, INF, 6, 1, 20, 3, 2},
    { 9, 5, 4, INF, 6, 10, 5, 9 },
    { 2, 8, 7, 10, INF, 5, 20, 1 },
    { 10, 5, 2, 10, 15, INF, 7, 3 },
    { 5, 2, 3, 5, 2, 1, INF, 6 },
    { 9, 10, 2, 9, 10, 3, 6, INF} };

int numCities = graph.size();

int populationSize;
int numGenerations;
double mutationRate;

vector<int> generateRandomRoute() {
    vector<int> route(numCities);
    for (int i = 0; i < numCities; ++i) {
        route[i] = i;
    }
    random_shuffle(route.begin(), route.end());
    return route;
}

int calculateRouteDistance(const vector<int>& route) {
    int totalDistance = 0;
    for (int i = 0; i < numCities; ++i) {
        int from = route[i];
        int to = route[(i + 1) % numCities];
        totalDistance += graph[from][to];
    }
    return totalDistance;
}

// Скрещивание 
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    vector<int> child(numCities, -1);

    int start = rand() % numCities;
    int end = rand() % numCities;
    if (start > end) swap(start, end);

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    int currentIndex = (end + 1) % numCities;
    for (int i = 0; i < numCities; ++i) {
        int city = parent2[(end + 1 + i) % numCities];
        if (find(child.begin(), child.end(), city) == child.end()) {
            child[currentIndex] = city;
            currentIndex = (currentIndex + 1) % numCities;
        }
    }

    return child;
}

void mutate(vector<int>& route) {
    if ((double)rand() / RAND_MAX < mutationRate) {
        int i = rand() % numCities;
        int j = rand() % numCities;
        swap(route[i], route[j]);
    }
}

void geneticAlgorithm() {
    // Генерация
    vector<vector<int>> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population[i] = generateRandomRoute();
    }

    vector<int> bestRoute;
    int bestDistance = INF;

    for (int generation = 1; generation <= numGenerations; ++generation) {
        vector<pair<int, vector<int>>> fitness;
        for (const auto& route : population) {
            int distance = calculateRouteDistance(route);
            fitness.push_back({ distance, route });
            if (distance < bestDistance) {
                bestDistance = distance;
                bestRoute = route;
            }
        }

        sort(fitness.begin(), fitness.end());

        cout << "Поколение: " << generation << "\n";
        cout << "Лучшая дистануия: " << bestDistance << "\n";
        cout << "Лучший путь: ";
        for (int city : bestRoute) {
            cout << city << " ";
        }
        cout << "\n\n";

        vector<vector<int>> newPopulation;
        for (int i = 0; i < populationSize / 2; ++i) {
            newPopulation.push_back(fitness[i].second);
        }

        while (newPopulation.size() < populationSize) {
            int parent1Index = rand() % (populationSize / 2);
            int parent2Index = rand() % (populationSize / 2);
            vector<int> child = crossover(fitness[parent1Index].second, fitness[parent2Index].second);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    cout << "Финальная дисталция: " << bestDistance << "\n";
    cout << "Финальный путь: ";
    for (int city : bestRoute) {
        cout << city << " ";
    }
    cout << "\n";
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "rus");

    cout << "Введите размер популяции: ";
    cin >> populationSize;
    cout << "Введите количество поколений: ";
    cin >> numGenerations;
    cout << "Введите частоту мутаций (0,0 - 1,0): ";
    cin >> mutationRate;

    geneticAlgorithm();

    return 0;
}
