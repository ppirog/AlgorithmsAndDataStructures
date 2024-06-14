#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point {
public:
    int x;
    int y;

    bool operator<(const Point &rhs) const {
        return y < rhs.y;
    }
};

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

        vector<Point> points(m);
//        vector<bool> result(m);
        bool *result = new bool [m];
        for (int j = 0; j < m; ++j) {

            int t1, t2;
            cin >> t1 >> t2;
            cin.ignore();

            points[j].x = t1;
            points[j].y = t2;
            result[j] = false;

        }

        sort(points.begin(), points.end());

        int counter = 0;

        for (auto &point: points) {

            for (int k = point.x; k <= point.y; ++k) {
                if (!result[k]) {
                    result[k] = true;
                    counter++;
                    break;
                }
            }
        }

        if (counter == m) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
        delete [] result;
    }


    return 0;
}