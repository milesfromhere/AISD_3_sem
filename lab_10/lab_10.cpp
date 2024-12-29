#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>

using namespace std;

class AntColonyOptimization {
private:
    int numberOfCities;
    vector<vector<double>> distances;
    vector<vector<double>> pheromones;
    double alpha, beta;
    double evaporationRate;
    double pheromoneDeposit;
    int iterations;

public:
    AntColonyOptimization(int numberOfCities, double alpha, double beta, int iterations, double evaporationRate)
        : numberOfCities(numberOfCities), alpha(alpha), beta(beta), iterations(iterations), evaporationRate(evaporationRate) {
        distances.resize(numberOfCities, vector<double>(numberOfCities, 0));
        pheromones.resize(numberOfCities, vector<double>(numberOfCities, 1.0)); 
        generateDistances();
    }

    void generateDistances() {
        srand(time(nullptr));
        for (int i = 0; i < numberOfCities; ++i) {
            for (int j = 0; j < numberOfCities; ++j) {
                if (i != j) {
                    distances[i][j] = rand() % 100 + 1;
                }
                else {
                    distances[i][j] = 0; 
                }
            }
        }
    }

    vector<int> generateAntPath() {
        vector<int> path;
        vector<bool> visited(numberOfCities, false);
        int currentCity = rand() % numberOfCities;
        path.push_back(currentCity);
        visited[currentCity] = true;

        for (int step = 1; step < numberOfCities; ++step) {
            int nextCity = selectNextCity(currentCity, visited);
            path.push_back(nextCity);
            visited[nextCity] = true;
            currentCity = nextCity;
        }

        return path;
    }

    int selectNextCity(int currentCity, const vector<bool>& visited) {
        vector<double> probabilities(numberOfCities, 0.0);
        double sum = 0.0;

        for (int i = 0; i < numberOfCities; ++i) {
            if (!visited[i]) {
                probabilities[i] = pow(pheromones[currentCity][i], alpha) * pow(1.0 / distances[currentCity][i], beta);
                sum += probabilities[i];
            }
        }

        double randomValue = ((double)rand() / RAND_MAX) * sum;
        for (int i = 0; i < numberOfCities; ++i) {
            if (!visited[i]) {
                if (randomValue < probabilities[i]) {
                    return i;
                }
                randomValue -= probabilities[i];
            }
        }

        for (int i = 0; i < numberOfCities; ++i) {
            if (!visited[i]) return i;
        }

        return 0;
    }

    double calculatePathDistance(const vector<int>& path) {
        double distance = 0.0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            distance += distances[path[i]][path[i + 1]];
        }
        distance += distances[path.back()][path[0]];
        return distance;
    }

    void updatePheromones(const vector<vector<int>>& paths, const vector<double>& pathDistances) {
        for (int i = 0; i < numberOfCities; ++i) {
            for (int j = 0; j < numberOfCities; ++j) {
                pheromones[i][j] *= (1.0 - evaporationRate);
            }
        }

        for (size_t k = 0; k < paths.size(); ++k) {
            const vector<int>& path = paths[k];
            double contribution = pheromoneDeposit / pathDistances[k];
            for (size_t i = 0; i < path.size() - 1; ++i) {
                pheromones[path[i]][path[i + 1]] += contribution;
                pheromones[path[i + 1]][path[i]] += contribution;
            }
            pheromones[path.back()][path[0]] += contribution;
            pheromones[path[0]][path.back()] += contribution;
        }
    }

    void run() {
        vector<int> bestPath;
        double bestDistance = numeric_limits<double>::infinity();

        for (int iteration = 1; iteration <= iterations; ++iteration) {
            vector<vector<int>> paths;
            vector<double> pathDistances;

            for (int ant = 0; ant < numberOfCities; ++ant) {
                vector<int> path = generateAntPath();
                double distance = calculatePathDistance(path);
                paths.push_back(path);
                pathDistances.push_back(distance);

                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPath = path;
                }
            }

            updatePheromones(paths, pathDistances);

            cout << "Итерация " << iteration << ":\n";
            cout << "Лучший путь на данный момент: ";
            for (int city : bestPath) cout << city << " ";
            cout << "\nЛучшая дистранция: " << bestDistance << "\n\n";
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(nullptr));

    int numberOfCities, iterations;
    double alpha, beta, evaporationRate;

    cout << "Введите количество городов: ";
    cin >> numberOfCities;

    cout << "Введите альфа (влияние феромона): ";
    cin >> alpha;

    cout << "Введите бета (влияние расстояния): ";
    cin >> beta;

    cout << "Введите количество итераций: ";
    cin >> iterations;

    cout << "Введите скорость испарения (0,0 - 1,0): ";
    cin >> evaporationRate;

    AntColonyOptimization aco(numberOfCities, alpha, beta, iterations, evaporationRate);
    aco.run();

    return 0;
}
