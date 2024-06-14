#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Monkey {
private:
    char name;
    int maxNumOfChildren;
    vector<Monkey *> children;
    Monkey *parent = nullptr;
    bool isBlocked = false;

public:
    Monkey(char name, int maxNum) : name(name), maxNumOfChildren(maxNum) {
        parent = nullptr;
    }

    void setParent(Monkey *parent) {
        Monkey::parent = parent;
    }

    bool addChild(Monkey *child) {
        if (children.size() < maxNumOfChildren) {
            child->parent = this;
            children.push_back(child);
            if (children.size() == maxNumOfChildren) {
                isBlocked = true;
            }
            return true;
        }
        return false;
    }

    bool isFull() const {
        return isBlocked;
    }

    char getName() const {
        return name;
    }


    const vector<Monkey *> &getChildren() const {
        return children;
    }


    Monkey() {
        parent = nullptr;
    }


    Monkey *getChild(int index) {
        if (index < children.size()) {
            return children[index];
        }
    }
};

void printMonkeys(Monkey *m) {
    if (m == nullptr) {
        return;
    }
    cout << m->getName();
    for (int i = 0; i < m->getChildren().size(); i++) {
        printMonkeys(m->getChild(i));
    }
}
int main() {


    int numbersOfSets;
    cin >> numbersOfSets;
    cin.ignore();
    for (int i = 0; i < numbersOfSets; i++) {
        int numbersOfMonkeys;
        cin >> numbersOfMonkeys;
        cin.ignore();
        if (numbersOfMonkeys == 0) {
            continue;
        }
        Monkey *monkeyArr = new Monkey[numbersOfMonkeys];
        queue<Monkey *> monkeyQueue;

        for (int j = 0; j < numbersOfMonkeys; j++) {
            char monkeyName;
            int monkeyNumber;
            cin >> monkeyName >> monkeyNumber;
            cin.ignore();
            monkeyArr[j] = Monkey(monkeyName, monkeyNumber);

            if (j == 0) {
                monkeyQueue.push(&monkeyArr[j]);
                continue;
            }

            if (monkeyQueue.front()->addChild(&monkeyArr[j])) {

                monkeyArr[j].setParent(monkeyQueue.front());
                if (monkeyQueue.front()->isFull()) {
                    monkeyQueue.pop();
                }
            }
            monkeyQueue.push(&monkeyArr[j]);
        }

        printMonkeys(&monkeyArr[0]);

        cout << "\n";

        delete[] monkeyArr;
    }
    return 0;
}