#include <iostream>

using namespace std;

class Meal {
public:
    int number;
    int modulo;
    string name;
};

void print(Meal *meal, int n) {
    for (int i = 0; i < n; ++i) {
        cout << meal[i].name << " ";
    }
    cout << "\n";
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n,k;
    cin >> n;
    cin.ignore();

    Meal *A = new Meal[n];
    Meal *B = new Meal[n];

    for (int i = 0; i < n; ++i) {
        int temp2;
        string temp1;
        cin >> temp1 >> temp2;
        cin.ignore();

        A[i].name = temp1;
        A[i].number = temp2 / n;
        A[i].modulo = temp2 % n;
    }

    //modulo sort
    int *C = new int[n];

    for (int i = 0; i < n; ++i) {
        C[i] = 0;
    }

    for(int j = 0; j < n; ++j) {
        C[A[j].modulo]++;
    }

    for (int i = 1; i < n; ++i) {
        C[i] += C[i - 1];
    }

    for (int j = n - 1; j >= 0; --j) {
        B[C[A[j].modulo] - 1] = A[j];
        C[A[j].modulo]--;
    }

    //number sort
    for (int i = 0; i < n; ++i) {
        C[i] = 0;
    }


    for (int j = 0; j < n; ++j) {
        C[A[j].number]++;
    }

    for (int i = 1; i < n; ++i) {
        C[i] += C[i - 1];
    }

    for (int j = n - 1; j >= 0; --j) {
        A[C[B[j].number] - 1] = B[j];
        C[B[j].number]--;
    }

    print(A, n);

    delete[] C;
    delete[] A;
    delete[] B;

    return 0;
}