#include <iostream>
#include <cmath>

int row, col;
using namespace std;

double P(int i, int j) {
    return 30 - sqrt((i - 5) * (i - 5) + (j - 5) * (j - 5));
}

double binSearch(int left, int right) {

    if (left > right) return -1;
    int mid_col = (left + right) / 2;

    double maxi = 0;
    int max_index = 0;

    for (int i = 0; i < row; i++) {
        double d = P(i, mid_col);
        if (d > maxi) {
            maxi = d;
            max_index = i;
        }
    }

    if (abs(left - right) == 1) {
        cout << (int) maxi;
        exit(0);
    }


    bool goLeft = false;
    bool goRight = false;

    if (mid_col > 0 && P(max_index, mid_col - 1) > maxi) {
        goLeft = true;
    }
    if (mid_col < col - 1 && P(max_index, mid_col + 1) > maxi) {
        goRight = true;
    }

    if (goLeft && goRight) {
        return binSearch(left, mid_col);
    } else if (goLeft) {
        return binSearch(left, mid_col);
    } else if (goRight) {
        return binSearch(mid_col, right);
    } else {
        return maxi;
    }
}

int main() {
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//    std::cout.tie(nullptr);

    cin >> row >> col;

    cout << (int) binSearch(0, col);
}