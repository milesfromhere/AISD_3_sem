#include<iostream>
using namespace std;
int D[6][6] = {
    { 0, 28, 21, 59, 12, 27 },
    { 7, 0, 24, INT_MAX, 21, 9 },
    { 9, 32, 0, 13, 11, INT_MAX },
    { 8, INT_MAX, 5, 0, 16,INT_MAX },
    { 14, 13, 15, 10, 0, 22 },
    { 15, 18, INT_MAX, INT_MAX, 6, 0 }
};
int S[6][6];

void Trio() {
    for (int m = 0; m < 6; m++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (D[i][j] > D[i][m] + D[m][j]) {
                    D[i][j] = D[i][m] + D[m][j];
                    S[i][j] = S[m][j];
                }
            }
        }
    }
}

void main() {
    setlocale(LC_ALL, "rus");

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i == j) {
                S[i][j] = 0;
                continue;
            }
            S[i][j] = j + 1;
        }
    }

    Trio();

    cout << "Матрица D:\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << D[i][j] << "\t";
        }
        cout << '\n';
    }

    cout << "Матрица S:\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << S[i][j] << "\t";
        }
        cout << '\n';
    }
}
