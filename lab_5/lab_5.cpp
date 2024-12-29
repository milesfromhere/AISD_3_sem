#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

struct Edge {
    int u, v, weight;
};

int calculateCyclomaticNumber(int V, int E, int P = 1) {
    return E - V + P;
}

// алгоритм Прима
void primMST(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int i = 0; i < V; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Минимальное остовное дерево по Приму:\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] + 1 << " - " << i + 1 << " : " << graph[i][parent[i]] << endl;
}

// алгоритм Краскала
int find(vector<int>& parent, int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSet(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rank[rootU] < rank[rootV])
        parent[rootU] = rootV;
    else if (rank[rootU] > rank[rootV])
        parent[rootV] = rootU;
    else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    vector<Edge> result;
    for (Edge edge : edges) {
        int u = find(parent, edge.u);
        int v = find(parent, edge.v);
        if (u != v) {
            result.push_back(edge);
            unionSet(parent, rank, u, v);
        }
    }

    cout << "Минимальное остовное дерево по Краскалу:\n";
    for (Edge edge : result)
        cout << edge.u + 1 << " - " << edge.v + 1 << " : " << edge.weight << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int V = 8;

    vector<vector<int>> graph = {
        {0, 2, 0, 8, 2, 0, 0, 0},
        {2, 0, 3, 10, 5, 0, 0, 0},
        {0, 3, 0, 0, 12, 0, 0, 7},
        {8, 10, 0, 0, 14, 3, 1, 0},
        {2, 5, 12, 14, 0, 11, 4, 8},
        {0, 0, 0, 3, 11, 0, 6, 0},
        {0, 0, 0, 1, 4, 6, 0, 9},
        {0, 0, 0, 0, 8, 0, 9, 0}
    };

    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 8}, {6, 4, 4}, {0, 4, 2},
        {1, 2, 3}, {1, 4, 5}, {1, 3, 10}, {2, 4, 12},
        {2, 7, 7}, {3, 4, 14}, {3, 5, 3}, {3, 6, 1},
        {4, 7, 8}, {5, 6, 6}, {6, 7, 9}, {5, 6, 11}
    };
    int cyclomaticNumber = calculateCyclomaticNumber(V, edges.size());
    cout << "Цикломатическое число графа: " << cyclomaticNumber << endl;

    auto start_prim = high_resolution_clock::now();
    primMST(graph);
    auto stop_prim = high_resolution_clock::now();
    auto duration_prim = duration_cast<milliseconds>(stop_prim - start_prim);
    cout << "Время выполнения медотом Прима: " << duration_prim.count() << "мс" << endl;

    auto start_krusk = high_resolution_clock::now();
    kruskalMST(edges, V);
    auto stop_krusk = high_resolution_clock::now();
    auto duration_krusk = duration_cast<milliseconds>(stop_krusk - start_krusk);
    cout << "Время выполнения медотом Крускала: " << duration_krusk.count() << "мс" << endl;
    return 0;
}
