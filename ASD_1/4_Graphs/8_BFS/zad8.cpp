#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Castle {
public:
    short idNumber{};
    vector<int> neighbours;
    bool visited = false;

    Castle() : idNumber(-1) {}
};

short maxLengthNumberForCastleWhichIsAvailableToSendMilitary = 0;

void bfs(unsigned short v, Castle *castles, unsigned short &maxPath, unsigned short &successMilitaryLandingCounter) {
    queue<pair<short, short>> queue;
    queue.emplace(v, 0);

    while (!queue.empty()) {
        short pom = queue.front().first;
        short pathLength = queue.front().second;
        queue.pop();

        if (!castles[pom].visited) {
            castles[pom].visited = true;

            for (short neighbour: castles[pom].neighbours) {
                queue.emplace(neighbour, pathLength + 1);
            }

            maxPath = max(maxPath, (unsigned short) pathLength);

            if (pathLength <= maxLengthNumberForCastleWhichIsAvailableToSendMilitary && pathLength > 0) {
                successMilitaryLandingCounter++;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unsigned short n, s, d;
    unsigned int m;
    cin >> n >> m >> s >> d;
    cin.ignore();

    unsigned short maxPath = 0;
    unsigned short successMilitaryLandingCounter = 0;

    Castle *castles = new Castle[n];

    for (int i = 0; i < n; i++) {
        castles[i].idNumber = (short) i;
    }

    for (int i = 0; i < m; i++) {
        unsigned short a, b;
        cin >> a >> b;
        cin.ignore();
        castles[a].neighbours.push_back(b);
        castles[b].neighbours.push_back(a);
    }

    maxLengthNumberForCastleWhichIsAvailableToSendMilitary = d / 2;

    bfs(s, castles, maxPath, successMilitaryLandingCounter);

    cout << maxPath << " " << successMilitaryLandingCounter;

    return 0;
}