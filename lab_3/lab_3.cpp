#include <iostream>
#include <climits>
#include <chrono>
#include <vector>

#define V 9

using namespace std;

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    cout << " -> " << char('A' + j);
}

void printSolution(int dist[], int parent[], int src)
{
    char vertices[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };

    cout << "Вершина\tРасстояние\tПуть" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << vertices[i] << "\t" << dist[i] << "\t\t" << char('A' + src);
        printPath(parent, i);
        cout << endl;
    }
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];        
    bool sptSet[V];    
    int parent[V];      

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; 
    }

    dist[src] = 0; 

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;                  

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; 
            }
        }
    }

    printSolution(dist, parent, src);
}

int main()
{
    setlocale(LC_ALL, "rus");
    int graph[V][V] =
    {
        //   A  B  C   D  E  F  G  H  I
            {0, 7, 10, 0, 0, 0, 0, 0, 0},  // A
            {7, 0, 0, 0, 0, 9, 27, 0, 0},  // B
            {10, 0, 0, 0, 31, 8, 0, 0, 0}, // C
            {0, 0, 0, 0, 32, 0, 0, 17, 21},// D
            {0, 0, 31, 32, 0, 0, 0, 0, 0}, // E
            {0, 9, 8, 0, 0, 0, 0, 11, 0},  // F
            {0, 27, 0, 0, 0, 0, 0, 0, 15}, // G
            {0, 0, 0, 17, 0, 11, 0, 0, 15},// H
            {0, 0, 0, 21, 0, 0, 15, 15, 0} // I
    };

    char dot;
    int start;
    do
    {
        cout << "Введите начальную вершину (A-I): ";
        cin >> dot;
        start = dot - 'A'; 
    } while (start < 0 || start >= V);

    auto start_time = chrono::high_resolution_clock::now();

    dijkstra(graph, start);

    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end_time - start_time;
    cout << "Время выполнения: " << elapsed.count() << " секунд" << endl;

    cout << "Сложность алгоритма Дейкстры: O(n^2+m)" << endl;

    return 0;
}
