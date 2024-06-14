#include <iostream>
#include <vector>

using namespace std;
int uniqueNumber = 1;


void FillBoard(int n, int **L, int filledY, int filledX, int colStart, int rowStart) {
    if (n == 1) {
        L[filledY][filledX] = uniqueNumber;
        return;
    }

    int midPosY = (n / 2) + rowStart;
    int midPosX = (n / 2) + colStart;

    uniqueNumber++;
    int num = uniqueNumber;


    int leftUpX, leftUpY, rightUpX, rightUpY, leftDownX, leftDownY, rightDownX, rightDownY;



    //lewy gorny
    if (filledY < midPosY && filledX < midPosX) {


        rightDownX = midPosX;
        rightDownY = midPosY;

        rightUpX = midPosX;
        rightUpY = midPosY - 1;

        leftDownX = midPosX - 1;
        leftDownY = midPosY;

        leftUpX = filledX;
        leftUpY = filledY;


        if (n == 2) {
            L[rightDownY][rightDownX] = num;
            L[rightUpY][rightUpX] = num;
            L[leftDownY][leftDownX] = num;

            return;
        }

        L[rightDownY][rightDownX] = num;
        L[rightUpY][rightUpX] = num;
        L[leftDownY][leftDownX] = num;

//        L[leftUpY][leftUpX] = num; // punkt startowy





    }
        //prawy gorny
    else if (filledY < midPosY && filledX >= midPosX) {
        rightDownX = midPosX;
        rightDownY = midPosY;

        rightUpX = filledX;
        rightUpY = filledY;

        leftDownX = midPosX - 1;
        leftDownY = midPosY;

        leftUpX = midPosX - 1;
        leftUpY = midPosY - 1;

        if (n == 2) {
            L[rightDownY][rightDownX] = num;
            L[leftDownY][leftDownX] = num;
            L[leftUpY][leftUpX] = num;

            return;
        }

        L[rightDownY][rightDownX] = num;
        L[leftDownY][leftDownX] = num;
        L[leftUpY][leftUpX] = num;

//        L[rightUpY][rightUpX] = num; // punkt startowy
    }
        // prawy dolny
    else if (filledY >= midPosY && filledX >= midPosX) {
        rightDownX = filledX;
        rightDownY = filledY;

        rightUpX = midPosX;
        rightUpY = midPosY - 1;

        leftDownX = midPosX - 1;
        leftDownY = midPosY;

        leftUpX = midPosX - 1;
        leftUpY = midPosY - 1;

        if (n == 2) {

            L[rightUpY][rightUpX] = num;
            L[leftDownY][leftDownX] = num;
            L[leftUpY][leftUpX] = num;
            return;
        }

        L[rightUpY][rightUpX] = num;
        L[leftDownY][leftDownX] = num;
        L[leftUpY][leftUpX] = num;

//        L[rightDownY][rightDownX] = num; // punkt startowy


    }
        // lewy dolny
    else if (filledY >= midPosY && filledX < midPosX) {
        rightDownX = midPosX;
        rightDownY = midPosY;

        rightUpX = midPosX;
        rightUpY = midPosY - 1;

        leftDownX = filledX;
        leftDownY = filledY;

        leftUpX = midPosX - 1;
        leftUpY = midPosY - 1;

        if (n == 2) {
            L[rightDownY][rightDownX] = num;
            L[rightUpY][rightUpX] = num;
            L[leftUpY][leftUpX] = num;

            return;
        }

        L[rightDownY][rightDownX] = num;
        L[rightUpY][rightUpX] = num;
        L[leftUpY][leftUpX] = num;

//        L[leftDownY][leftDownX] = num; // punkt startowy
    }

    //lewy gorny
    FillBoard(n / 2, L, leftUpY, leftUpX, colStart, rowStart);
    //prawy gorny
    FillBoard(n / 2, L, rightUpY, rightUpX, midPosX, rowStart);
    //lewy dolny
    FillBoard(n / 2, L, leftDownY, leftDownX, colStart, midPosY);
    //prawy dolny
    FillBoard(n / 2, L, rightDownY, rightDownX, midPosX, midPosY);
}

class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
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
        int m, x, y, p;
        cin >> m >> x >> y >> p;
        cin.ignore();
        int **L = new int *[m];
        for (int j = 0; j < m; ++j) {
            L[j] = new int[m];
        }
        L[y][x] = -1;

        FillBoard(m, L, y, x, 0, 0);

        for (int z = 0; z < p; ++z) {
            int n1, n2;
            cin >> n1 >> n2;
            cin.ignore();
            int wynik = L[n2][n1];

            vector<Point> points;

            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < m; ++k) {
                    if (j == n2 && k == n1) {
                        continue;
                    }

                    if (L[j][k] == wynik) {
                        points.push_back(Point(k, j));
                    }
                }
            }

            if (points[0].getX() > points[1].getX()) {
                swap(points[0], points[1]);
            }

            cout << points[0].getX() << " " << points[0].getY() << " ";
            cout << points[1].getX() << " " << points[1].getY() << endl;

        }


        for (int j = 0; j < m; ++j) {
            delete[] L[j];
        }
        delete[] L;
    }


    return 0;
}