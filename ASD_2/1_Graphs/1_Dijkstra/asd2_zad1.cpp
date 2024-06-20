#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

class Graf {
public:
    int num{};
    map<int, int> sasiedzi;
};

class Point {
public:
    int x;
    int y;
    int num;
};

void dijkstra(Graf *pGraf, int start, int koniec, int n) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> kolejka;
    vector<int> odleglosc(n, INT_MAX);
    vector<bool> odwiedzone(n, false);

    odleglosc[start] = 0;
    kolejka.emplace(0, start);

    while (!kolejka.empty()) {
        pair<int, int> para = kolejka.top();
        kolejka.pop();

        int index = para.second;

        odwiedzone[index] = true;

        for (auto &sasiad: pGraf[index].sasiedzi) {
            int sasiadId = sasiad.first;
            int sasiadWaga = sasiad.second;

            if (!odwiedzone[sasiadId] && odleglosc[index] + sasiadWaga < odleglosc[sasiadId]) {
                odleglosc[sasiadId] = odleglosc[index] + sasiadWaga;
                kolejka.emplace(odleglosc[sasiadId], sasiadId);
            }
        }
    }

    cout << odleglosc[koniec];
};

int main() {

    int n, start, koniec;
    cin >> n;

    auto *punkty = new Point[n];

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        punkty[i].x = a;
        punkty[i].y = b;

        punkty[i].num = i;
    }

    cin >> start >> koniec;

    //pierwsze sortowanie po x
    sort(punkty, punkty + n, [](const Point &a, const Point &b) {
        return a.x < b.x;
    });

    Graf *graf = new Graf[n];

    //tworzenie wag w grafie na podstwawie X. tutaj nie musze sprawdzać czy krawedz istnieje bo na pewno nie istnieje
    for (int i = 0; i < n - 1; i++) {

        int temp = punkty[i + 1].x - punkty[i].x;
        graf[punkty[i].num].sasiedzi[punkty[i + 1].num] = temp;
        graf[punkty[i + 1].num].sasiedzi[punkty[i].num] = temp;
    }

    //drugie sortowanie po y
    sort(punkty, punkty + n, [](const Point &a, const Point &b) {
        return a.y < b.y;
    });

    //tworzenie wag w grafie na podstawie Y
    for (int i = 0; i < n - 1; i++) {

        //sprawdz czy już istnieje krawedz. Jak istnieje weź z mniejszą wagą a jak nie to stardardowo wczytaj krawedz z waga
        if (graf[punkty[i].num].sasiedzi.find(punkty[i + 1].num) != graf[punkty[i].num].sasiedzi.end()) {

            if (graf[punkty[i].num].sasiedzi[punkty[i + 1].num] > punkty[i + 1].y - punkty[i].y) {
                graf[punkty[i].num].sasiedzi[punkty[i + 1].num] = punkty[i + 1].y - punkty[i].y;
                graf[punkty[i + 1].num].sasiedzi[punkty[i].num] = punkty[i + 1].y - punkty[i].y;
            }
        } else {

            graf[punkty[i].num].sasiedzi[punkty[i + 1].num] = punkty[i + 1].y - punkty[i].y;
            graf[punkty[i + 1].num].sasiedzi[punkty[i].num] = punkty[i + 1].y - punkty[i].y;
        }
    }


    dijkstra(graf, start, koniec, n);

    delete[] punkty;
    delete[] graf;

    return 0;
}
