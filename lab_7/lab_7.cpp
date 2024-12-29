#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void findLongestIncreasingSubsequence(const vector<int>& sequence) {
    int n = sequence.size();
    vector<int> dp(n, 1);
    vector<int> prev(n, -1);

    int maxLength = 1;
    int lastIndex = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[j] < sequence[i] && dp[j] + 1 > dp[i]) { 
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] >= maxLength) {
            maxLength = dp[i];
            lastIndex = i;
        }
    }

    vector<int> lis;
    for (int i = lastIndex; i != -1; i = prev[i]) {
        lis.push_back(sequence[i]);
    }
    reverse(lis.begin(), lis.end());

    cout << "Длинна последовательности: " << maxLength << endl;
    cout << "Последовательность: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<int> sequence = { 5,10,6,12,3,24,7,8 };

    findLongestIncreasingSubsequence(sequence);

    return 0;
}