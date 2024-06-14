#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        int m, c, d;

        long maxTime = 0;

        cin >> m >> c >> d;
        cin.ignore();

        int *arr1 = new int [m];
        bool * wykorzystane = new bool[m]();
        int *arr2 = new int [m];

        for (int j = 0; j < m; ++j) {
            int a, b;
            cin >> a >> b;
            cin.ignore();

            arr1[j] = a;
            arr2[j] = b;

            maxTime += c + d * (b - a);
        }

        sort(arr1, arr1 + m);
        sort(arr2, arr2 + m);

//        cout << maxTime << '\n';

        for (int z =  m - 1; z >= 0; z--) {
            int temp1 = arr2[z];

            auto iterator = upper_bound(arr1, arr1 + m, temp1);
            int startowyIndex = distance(arr1, iterator);

            for (int r = startowyIndex; r < m; ++r) {

                if (!wykorzystane[r]) {

                    if (arr1[r] > temp1) {
                        int timeTemp = d * (arr1[r] - temp1);

                        if (timeTemp < c) {
                            maxTime -= c;
                            maxTime += timeTemp;
                            wykorzystane[r] = true;
                            break;
                        }

                    }
                }


            }


        }
        cout << maxTime << '\n';

        delete [] arr1;
        delete [] arr2;
        delete [] wykorzystane;
    }


    return 0;
}
