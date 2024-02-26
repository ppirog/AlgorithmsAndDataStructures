#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void backtracing(int *kcal, int destiny, int current, int index, int &counter, int size, vector<int> &currVec) {

    if (current > destiny) {
        return;
    }

    if (current == destiny) {
        counter++;
        return;
    }

    if (index == size) {
        return;
    }

    if (current + kcal[index] <= destiny) {
        backtracing(kcal, destiny, current + kcal[index], index + 1, counter, size, currVec);
    }

    backtracing(kcal, destiny, current, index + 1, counter, size, currVec);

}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {

        int m;
        cin >> m;
        cin.ignore();

        int *kcal = new int[m];
        int requiredKcal;

        for (int j = 0; j < m; ++j) {
            int temp;
            cin >> temp;
            kcal[j] = temp;

        }

        sort(kcal, kcal + m, greater<int>());

        cin >> requiredKcal;

        int counter = 0;

        vector<int> currVec(m);

        backtracing(kcal, requiredKcal, 0, 0, counter, m, currVec);
        cout << counter << "\n";

        delete[] kcal;
    }

    return 0;
}
