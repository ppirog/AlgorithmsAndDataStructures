#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int MAX_ROW, MAX_COL, STARTING_POINT, ENDING_POINT;

class CityMap {
public:
    char id{};
    std::vector<int> neighbours;
};

int index(int row, int col) {
    return row * MAX_COL + col;
}

const int inf = 10000001;

class QueueItem {
public:
    int index;
    int distance;
    int M_counter;

    QueueItem(int i, int d, int m) : index(i), distance(d), M_counter(m) {}

    bool operator>(const QueueItem &other) const {
        return distance > other.distance;
    }
};

void dijkstra(int v, vector<CityMap> &cityMap) {

    std::priority_queue<QueueItem, vector<QueueItem>, greater<>> priorityQueue;

    bool *visitedData = new bool[MAX_ROW * MAX_COL];
    int *distanceData = new int[MAX_ROW * MAX_COL];
    int *mCounterData = new int[MAX_ROW * MAX_COL];

    for (int i = 0; i < MAX_ROW * MAX_COL; i++) {
        distanceData[i] = inf;
        mCounterData[i] = 0;
        visitedData[i] = false;
    }

    distanceData[v] = 0;
    mCounterData[v] = 0;
    priorityQueue.emplace(v, 0, 0);

    while (!priorityQueue.empty()) {
        QueueItem current = priorityQueue.top();
        priorityQueue.pop();

        int currentIndex = current.index;

        visitedData[currentIndex] = true;

        if (currentIndex == ENDING_POINT) {
            break;
        }

        for (int neighbour: cityMap[currentIndex].neighbours) {
            int neighbourId = neighbour;
            int neighbourWeight = 1;

            if (!visitedData[neighbourId] && distanceData[currentIndex] + neighbourWeight < distanceData[neighbourId]) {
                distanceData[neighbourId] = distanceData[currentIndex] + neighbourWeight;

                if (cityMap[neighbourId].id == 'M') {
                    mCounterData[neighbourId] = mCounterData[currentIndex] + 1;
                } else {
                    mCounterData[neighbourId] = mCounterData[currentIndex];
                }

                priorityQueue.emplace(neighbourId, distanceData[neighbourId], mCounterData[neighbourId]);

            } else {
                if (distanceData[currentIndex] + neighbourWeight == distanceData[neighbourId]) {
                    if (cityMap[neighbourId].id == 'M') {
                        mCounterData[neighbourId] = min(mCounterData[neighbourId], mCounterData[currentIndex] + 1);
                    } else {
                        mCounterData[neighbourId] = min(mCounterData[neighbourId], mCounterData[currentIndex]);
                    }
                }
            }
        }
    }

    cout << distanceData[ENDING_POINT] << " " << mCounterData[ENDING_POINT] << '\n';

    delete[] visitedData;
    delete[] distanceData;
}

int main() {

    std::cin >> MAX_ROW >> MAX_COL;

    vector<CityMap> cityMap(MAX_ROW * MAX_COL);

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            char *mapId = new char;
            std::cin >> *mapId;

            cityMap[index(i, j)].id = *mapId;
            if (*mapId == '#') {
                continue;
            }
            if (*mapId == 'S') {
                STARTING_POINT = index(i, j);
            } else if (*mapId == 'X') {
                ENDING_POINT = index(i, j);
            }
            delete mapId;
        }
    }

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            if (cityMap[index(i, j)].id == '#') {
                continue;
            }

            if (i != 0 && cityMap[index(i - 1, j)].id != '#') {
                cityMap[index(i, j)].neighbours.emplace_back(index(i - 1, j));

            }
            if (i != MAX_ROW - 1 && cityMap[index(i + 1, j)].id != '#') {
                cityMap[index(i, j)].neighbours.emplace_back(index(i + 1, j));

            }
            if (j != 0 && cityMap[index(i, j - 1)].id != '#') {
                cityMap[index(i, j)].neighbours.emplace_back(index(i, j - 1));

            }
            if (j != MAX_COL - 1 && cityMap[index(i, j + 1)].id != '#') {
                cityMap[index(i, j)].neighbours.emplace_back(index(i, j + 1));
            }
        }
    }

    dijkstra(STARTING_POINT, cityMap);
    return 0;
}