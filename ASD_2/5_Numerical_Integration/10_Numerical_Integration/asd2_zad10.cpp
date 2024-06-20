#include <iostream>
#include <cmath>

using namespace std;

//double butelka(double cm) {
//    return 10 - (cm - 2) * (cm - 2);
//}

double objetoscBrylyButelkiCalkowanie(double a, double b, int n) {

    double dx = (b - a) / n;
    double wynik = 0.0;
    for (int i = 0; i < n; ++i) {
        double x1 = a + i * dx;
        double x2 = a + (i + 1) * dx;
        double fx1 = butelka(x1);
        double fx2 = butelka(x2);
        if (fx1 > 0 && fx2 > 0) {
            wynik += (fx1 * fx1 + fx2 * fx2) * dx / 2.0;
        }

    }
    return wynik * M_PI;
}


int main() {
    int sz, dl, wys;
    cin >> sz >> dl >> wys;
    double stopien;
    cin >> stopien;

    double max = sz * dl * wys;
    double ileWody = sz * dl * wys * stopien;
//    cout << ileWody << endl;
    int n;
    cin >> n;

    double ostatnia = 0;
    for (int i = 0; i < n; i++) {
        double a;
        cin >> a;

        double wynik = objetoscBrylyButelkiCalkowanie(ostatnia, a, 1000);

        ileWody += wynik;

        if (ileWody > max) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << "NIE" << endl;
    return 0;
}
