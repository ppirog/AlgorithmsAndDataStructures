#include <iostream>
#include <vector>

using namespace std;

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;

    cin >> n >> m;
    cin.ignore();

    int size = 3 * m;
    vector<string> names(size);

    for (int i = 0; i < n; ++i) {

        if (i < m) {
            getline(cin, names[i % size]);
//            cout << names[i % size] << '\n';
            if (i == n - 1) {
                cout << names[i % size];
            }
            continue;
        }

        int a, b, c, d;
        cin >> a >> b >> c >> d;
//        cin.ignore();

        string temp = "############";

        temp[0] = names.at(a % size)[0];
        temp[1] = names.at(a % size)[1];
        temp[2] = names.at(a % size)[2];

        temp[3] = names.at(b % size)[3];
        temp[4] = names.at(b % size)[4];
        temp[5] = names.at(b % size)[5];

        temp[6] = names.at(c % size)[6];
        temp[7] = names.at(c % size)[7];
        temp[8] = names.at(c % size)[8];

        temp[9] = names.at(d % size)[9];
        temp[10] = names.at(d % size)[10];
        temp[11] = names.at(d % size)[11];

        names[i % size] = temp;

//        cout << names[i % size] << '\n';
        if (i == n - 1) {
            cout << names[i % size];
        }

    }
    return 0;
}