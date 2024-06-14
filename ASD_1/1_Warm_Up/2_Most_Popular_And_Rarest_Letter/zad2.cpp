#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {

    int *data = new int[127];
    bool isMin = false;
    bool isMax = false;

    while (true) {
        string input;
        getline(cin, input);
        char lastChar = input[input.size() - 1];

        char *arrTemp = new char[input.size() + 1];
        strcpy(arrTemp, input.c_str());

        for (int i = 0; i < input.size(); i++) {
            if (((arrTemp[i] >= 97) && (arrTemp[i] <= 122)) || ((arrTemp[i] >= 65) && (arrTemp[i] <= 90))) {
                data[arrTemp[i]]++;
            }
        }

        if (lastChar == '^') {
            break;
        }
        delete[] arrTemp;
    }

    int max = 0;
    char maxChar = 'a';

    for (int i = 97; i <= 122; i++) {
        int number = data[i] + data[i - 32];
        if (number > max) {
            max = number;
            maxChar = i;
            isMax = true;
        }
    }

    int min = max;
    char minChar = maxChar;
    for (int i = 97; i <= 122; i++) {
        int number = data[i] + data[i - 32];
        if ((number >= 1) && (number < min)) {
            min = number;
            minChar = i;
            isMin = true;
        }
    }

    cout << maxChar << " " << minChar << endl;


    delete[] data;
    return 0;
}