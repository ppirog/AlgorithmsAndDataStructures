#define N 8

#include <iostream>

using namespace std;

void print(int szachownica[N][N], int wybranyWiersz, int wybranaKolumna, int &liczbaRozwiazan) {
    if (szachownica[wybranyWiersz][wybranaKolumna]) {
        liczbaRozwiazan++;
        cout << "Rozwiazanie: " << liczbaRozwiazan << "\n";
        for (int i = 0; i < 8; ++i) {
            cout << (char) ('A' + i) << "  ";
        }
        cout << "\n";

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (szachownica[i][j]) {
                    cout << "Q  ";
                } else {
                    cout << ".  ";
                }
            }
            cout << i + 1 << "\n";
        }
        cout << "\n";

    }
}

bool czyMoznaWstawic(int szachownica[N][N], int wiersz, int kolumna) {
    int i, j;

    for (i = 0; i < kolumna; i++) {
        if (szachownica[wiersz][i]) {
            return false;
        }
    }

    for (i = wiersz, j = kolumna; i >= 0 && j >= 0; i--, j--) {
        if (szachownica[i][j]) {
            return false;
        }
    }

    for (i = wiersz, j = kolumna; j >= 0 && i < N; i++, j--) {
        if (szachownica[i][j]) {
            return false;
        }
    }
    return true;
}

void ProblemNHetmanow(int szachownica[N][N], int kolumna, int &liczbaRozwiazan, int wybranyWiersz, int wybranaKolumna) {

    if (kolumna >= N) {
        print(szachownica, wybranyWiersz, wybranaKolumna, liczbaRozwiazan);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (czyMoznaWstawic(szachownica, i, kolumna)) {
            szachownica[i][kolumna] = 1;
            ProblemNHetmanow(szachownica, kolumna + 1, liczbaRozwiazan, wybranyWiersz, wybranaKolumna);
            szachownica[i][kolumna] = 0;
        }
    }
}

int main() {

    int szachownica[N][N] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int liczbaRozwiazan = 0;

    int wybranyWiersz = 0;
    int wybranaKolumna = 0;

    for (int i = 0; i < 8; ++i) {
        cout << (char) ('A' + i) << "  ";
    }
    cout << "\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (szachownica[i][j]) {
                cout << "Q  ";
            } else {
                cout << ".  ";
            }
        }
        cout << i + 1 << "\n";
    }
    cout << "\n";

    string kolumna;
    cout << "Podaj kolumne: ";
    cin >> kolumna;

    if (kolumna[0] >= 'a' && kolumna[0] <= 'h') {
        kolumna[0] = kolumna[0] - 32;
    }
    wybranaKolumna = kolumna[0] - 'A';

    cout << "Podaj wiersz: ";
    cin >> wybranyWiersz;
    wybranyWiersz--;

    if (wybranyWiersz < 0 || wybranyWiersz >= N || wybranaKolumna < 0 || wybranaKolumna >= N) {
        cout << "Niepoprawne wspolrzedne\n";
        return 0;
    }

    ProblemNHetmanow(szachownica, 0, liczbaRozwiazan, wybranyWiersz, wybranaKolumna);

    cout << "Łączna liczba rozwiazan: " << liczbaRozwiazan << "\n";

    cout << "Wybrano: " << kolumna << wybranyWiersz + 1 << "\n";
    return 0;
}