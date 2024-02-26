#include <iostream>
#include <string>

using namespace std;

const double PI = 3.141593;
const double CAL_TO_CM = 2.54;

class Car {
public:

    Car(std::string name, long numberWheelTurnover) {
        this->name = name;
        this->numberWheelTurnover = numberWheelTurnover;
    }

    Car() {}

    long getNumberWheelTurnover() const {
        return numberWheelTurnover;
    }

    const string &getName() const {
        return name;
    }

private:
    std::string name;
    long numberWheelTurnover;
};

int carsComparator(const Car &firstCar, const Car &secondCar) {

    if (firstCar.getNumberWheelTurnover() != secondCar.getNumberWheelTurnover())
        return firstCar.getNumberWheelTurnover() < secondCar.getNumberWheelTurnover();
    return firstCar.getName() < secondCar.getName();

}

void bubbleSort(Car *arrCar, int n) {

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (carsComparator(arrCar[j], arrCar[j + 1]) != 1) {
                Car temp = arrCar[j];
                arrCar[j] = arrCar[j + 1];
                arrCar[j + 1] = temp;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n = 0;
    cin >> n;
    cin.ignore();

    Car *arrCar = new Car[4];

    for (int i = 0; i < n; i++) {

        double *p = new double;
        int *d = new int;
        long *countedNumberWheelTurnoverTemp = new long;
        string nameTemp;

        getline(cin, nameTemp);
        cin >> *p >> *d;
        cin.ignore();

        *countedNumberWheelTurnoverTemp = (*p * 100000) * 1.f / (((*d / 2.f) * CAL_TO_CM) * PI * 2.f) * 1.f;

        if (i <= 3) {
            arrCar[i] = Car(nameTemp, *countedNumberWheelTurnoverTemp);
            if (i == 3) {
                bubbleSort(arrCar, 4);
            }
        } else {
            arrCar[3] = Car(nameTemp, *countedNumberWheelTurnoverTemp);
            bubbleSort(arrCar, 4);
        }
        delete p;
        delete d;
        delete countedNumberWheelTurnoverTemp;
    }

    bubbleSort(arrCar, 3);

    for (int i = 0; i < 3; i++) {
        cout << arrCar[i].getName() << '\n' << arrCar[i].getNumberWheelTurnover() << '\n';
    }

    delete[] arrCar;
    return 0;
}