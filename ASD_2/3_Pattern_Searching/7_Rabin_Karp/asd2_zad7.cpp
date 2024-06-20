#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define d 256

void search(long long *pat, long long *txt, long long q, long long patSize, long long txtSize) {
    long long M = patSize;
    long long N = txtSize;
    long long i, j;
    long long p = 0;
    long long t = 0;
    long long h = 1;

    long long counter = 0;


    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;


    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }


    //stworz tablice 3 elementową
    long long *tab = new long long[3]();

    for (i = 0; i <= N - M; i++) {

        if (p == t) {

            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }

            if (j == M) {
                counter++;

                if (counter == 1) {
                    tab[0] = i;
                } else if (counter == 2) {
                    tab[1] = i;
                } else {
                    break;
                }

            }

        }


        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            if (t < 0)
                t = (t + q);
        }
    }

    for (long long int i = 2; true; i++) {
        tab[i % 3] = (tab[(i - 1) % 3] + tab[(i - 2) % 3]);

        if (tab[i % 3] >= txtSize) {
            cout << tab[i % 3] - txtSize << "\n";
            break;
        }
    }

    delete[] tab;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long q = 101;

    long long txtSize, patSize;
    cin >> txtSize;
    long long *txt = new long long[txtSize];


    for (long i = 0; i < txtSize; i++) {
        cin >> txt[i];
    }
    cin >> patSize;
    long long *pat = new long long[patSize];

    for (long i = 0; i < patSize; i++) {
        cin >> pat[i];
    }

    search(pat, txt, q, patSize, txtSize);


    delete[] txt;
    delete[] pat;

    return 0;
}