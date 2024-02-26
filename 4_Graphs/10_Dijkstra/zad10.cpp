#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

const long infinity = 1000000000000000000;

class Spaceship {
public:
    long number{};
    vector<pair<long, long>> neighbours;
};

void
dijkstra(vector<Spaceship> &spaceships, const map<long, vector<long>> &teleportingTimeOccupancyData, long startingPoint,
         long endPoint) {

    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<>> priorityQueue;

    vector<long> distance(spaceships.size(), infinity);
    vector<bool> visited(spaceships.size(), false);


    distance[startingPoint] = 0;
    visited[startingPoint] = true;
    priorityQueue.emplace(0, startingPoint);

    while (!priorityQueue.empty()) {
        pair<long, long> pom = priorityQueue.top();
        priorityQueue.pop();

        long shipIndex = pom.second;

        visited[shipIndex] = true;

        for (int i = 0; i < spaceships[shipIndex].neighbours.size(); i++) {
            long neighbourId = spaceships[shipIndex].neighbours[i].first;
            long neighbourScale = spaceships[shipIndex].neighbours[i].second;

            if (!visited[neighbourId] && distance[shipIndex] + neighbourScale <= distance[neighbourId]) {
                distance[neighbourId] = distance[shipIndex] + neighbourScale;

                vector<long> teleportingTimeOccupancyDataForOneTeleportingPlace = teleportingTimeOccupancyData.at(
                        neighbourId);

                for (long teleportingPlace: teleportingTimeOccupancyDataForOneTeleportingPlace) {
                    if (teleportingPlace == distance[neighbourId]) {
                        distance[neighbourId]++;
                    }
                }

                priorityQueue.emplace(distance[neighbourId], neighbourId);
            }
        }
    }

    cout << distance[endPoint] << endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int dataSetNumber;
    cin >> dataSetNumber;
    cin.ignore();

    for (int i = 0; i < dataSetNumber; i++) {
        int shipNumber, possibleTeleportingPath, startingPoint;
        cin >> shipNumber >> possibleTeleportingPath >> startingPoint;
        cin.ignore();
        vector<Spaceship> spaceships(shipNumber);
        map<long, vector<long>> teleportingTimeOccupancyData;

        for (int j = 0; j < possibleTeleportingPath; j++) {
            long teleporingPathStartpoint, teleportingPathEndpoint, teleportingTimeNeeded;
            cin >> teleporingPathStartpoint >> teleportingPathEndpoint >> teleportingTimeNeeded;
            cin.ignore();
            spaceships[teleporingPathStartpoint].number = teleporingPathStartpoint;
            spaceships[teleporingPathStartpoint].neighbours.emplace_back(teleportingPathEndpoint, teleportingTimeNeeded);
            spaceships[teleportingPathEndpoint].neighbours.emplace_back(teleporingPathStartpoint, teleportingTimeNeeded);
        }

        for (int j = 0; j < shipNumber; ++j) {
            long timeDataSets;
            cin >> timeDataSets;

            vector<long> teleportingTimeOccupancyDataForOneTeleportingPlace(timeDataSets);
            for (int l = 0; l < timeDataSets; ++l) {
                long secondWhenTeleportIsNotAvailable;
                cin >> secondWhenTeleportIsNotAvailable;
                teleportingTimeOccupancyDataForOneTeleportingPlace[l] = secondWhenTeleportIsNotAvailable;
            }
            teleportingTimeOccupancyData[j] = teleportingTimeOccupancyDataForOneTeleportingPlace;
            cin.ignore();
        }

        dijkstra(spaceships, teleportingTimeOccupancyData, startingPoint, 0);
    }

    return 0;
}