#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string txt;
    string pat;

    char ch;

    while (cin.get(ch) && ch != '\n') {
        pat += ch;
    }

    int *ps = new int [(pat.length())];
    int i = 0;
    int l = 0;
    ps[0] = 0;

    unsigned long length = pat.length();
    for (i = 1; i < length;) {

        if (pat[i] == pat[l]) {
            l++;
            ps[i] = l;
            i++;
        } else if (pat[i] != pat[l] && l != 0) {
            l = ps[l - 1];
        } else if (pat[i] != pat[l] && l == 0) {
            ps[i] = 0;
            i++;
        }

    }


    char wczytany;

    bool flag = false;
    int j = 0;
    while (cin.get(wczytany) && wczytany != '\n') {

        if (wczytany == '\n') {
            break;
        }
        if (wczytany >= 'a' && wczytany <= 'z') {
            wczytany = 'a';
        } else if (wczytany >= 'A' && wczytany <= 'Z') {
            wczytany = 'A';
        } else if (wczytany >= '0' && wczytany <= '9') {
            wczytany = '0';
        } else if (wczytany == ' ') {
            wczytany = ' ';
        } else if (wczytany == '.') {
            wczytany = '.';
        } else if (wczytany == '?') {
            wczytany = '.';
        } else if (wczytany == '!') {
            wczytany = '.';
        } else if (wczytany == ',') {
            wczytany = '.';
        } else if (wczytany == ';') {
            wczytany = '.';
        } else if (wczytany == ':') {
            wczytany = '.';
        } else if (wczytany == '-') {
            wczytany = '.';
        }


        while (j > 0 && wczytany != pat[j]) {
            j = ps[j - 1];
        }
        if (wczytany == pat[j]) {
            j++;
        }
        if (j == pat.size()) {
            cout << "T";
            delete [] ps;
            return 0;
        }
    }

    cout << "N";
    delete [] ps;
    return 0;
}