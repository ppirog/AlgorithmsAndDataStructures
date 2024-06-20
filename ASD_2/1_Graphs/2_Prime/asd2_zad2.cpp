#include <iostream>
#include <vector>
#include <queue>

using namespace std;

double result = 1.0;

int n, m, temp;

class Graf {
public:
    int num{};
    vector<pair<int, double>> sasiedzi;
};


void prime(Graf *pGraf) {

    priority_queue<pair<double, int>, vector<pair<double, int>>, less<>> kolejka;
    vector<bool> odwiedzone(n, false);

    kolejka.emplace(1, 0);

    while (!kolejka.empty()) {
        pair<double, int> para = kolejka.top();
        kolejka.pop();

        int index = para.second;

        if (odwiedzone[index]) {
            continue;
        }

        odwiedzone[index] = true;

        for (auto &sasiad: pGraf[index].sasiedzi) {
            int sasiadId = sasiad.first;
            double sasiadWaga = sasiad.second;

            if (!odwiedzone[sasiadId]) {
                kolejka.emplace(sasiadWaga, sasiadId);
            }
        }

        result *= para.first;
        temp++;

        if (temp == n) {
            break;
        }
    }
}


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    temp = 0;

    std::cin >> n >> m;

    auto *graf = new Graf[n];

    for (int i = 0; i < m; i++) {
        int a, b;
        double c;
        std::cin >> a >> b >> c;
        graf[a].sasiedzi.emplace_back(b, c);
        graf[b].sasiedzi.emplace_back(a, c);
    }

    prime(graf);

    cout.precision(5);
    cout << fixed << result;

    delete[] graf;

    return 0;
}
