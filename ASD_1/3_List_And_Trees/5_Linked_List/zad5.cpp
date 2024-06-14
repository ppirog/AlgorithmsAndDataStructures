#include <iostream>
#include <string>

using namespace std;

class Actor {
public:
    Actor(string &name, long numberOfFans, Actor *next) : name(name), numberOfFans(numberOfFans), next(next) {}

    Actor(string &name, long numberOfFans) : name(name), numberOfFans(numberOfFans) {
        next = nullptr;
    }

    const string &getName() const {
        return name;
    }

    long getNumberOfFans() const {
        return numberOfFans;
    }

    Actor *getNext() const {
        return next;
    }

    void setNext(Actor *next) {
        Actor::next = next;
    }

private:
    string name;
    long numberOfFans;
    Actor *next;
};

class LinkedList {
private:
    Actor *first;
    Actor *last;
public:
    LinkedList() {
        first = nullptr;
        last = nullptr;
    }

    void add(string name, int numberOfFans) {
        Actor *actor = new Actor(name, numberOfFans, nullptr);
        if (first == nullptr) {
            first = actor;
            last = actor;
        } else {
            last->setNext(actor);
            last = actor;
        }
    }

    void remove(string name, int numberOfFans) {
        Actor *temp = first;
        Actor *previous = nullptr;
        while (temp != nullptr) {
            if (temp->getName() == name && temp->getNumberOfFans() == numberOfFans) {
                if (previous == nullptr) {
                    first = temp->getNext();
                } else if (temp->getName() == last->getName() && temp->getNumberOfFans() == last->getNumberOfFans()) {
                    last = previous;
                    last->setNext(nullptr);
                } else {
                    previous->setNext(temp->getNext());
                }
                delete temp;
                break;
            }
            previous = temp;
            temp = temp->getNext();
        }
    }

    Actor *getHead() const {
        return first;
    }
};


Actor checkIfIsProperActorOnTheList(LinkedList list, long numberOfFans) {
    Actor *temp = list.getHead();
    long recentMax = 0;
    string recentName;
    bool flag = false;

    while (temp != nullptr) {
        if (temp->getNumberOfFans() <= numberOfFans) {
            flag = true;
            if (temp->getNumberOfFans() > recentMax) {
                recentMax = temp->getNumberOfFans();
                recentName = temp->getName();
            } else if ((temp->getNumberOfFans() == recentMax) && (temp->getName() < recentName)) {
                recentMax = temp->getNumberOfFans();
                recentName = temp->getName();
            }
        }
        temp = temp->getNext();
    }

    if (flag) {
        Actor a = Actor(recentName, recentMax);
        return a;
    } else {
        string s = "NIC";
        Actor a = Actor(s, -1);
        return a;
    }
}

bool checkIfIsOnTheList(LinkedList list, string name, long numberOfFans) {
    Actor *temp = list.getHead();
    while (temp != nullptr) {
        if (temp->getName() == name && temp->getNumberOfFans() == numberOfFans) {
            return true;
        }
        temp = temp->getNext();
    }
    return false;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    LinkedList list;

    long n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string temp;
        long command;
        getline(cin, temp);
        command = stol(temp);
        if (command == 1) {
            string name;
            string temp1;
            long numberOfFans;
            getline(cin, name);
            getline(cin, temp1);

            numberOfFans = stol(temp1);

            bool check = checkIfIsOnTheList(list, name, numberOfFans);
            if (check) {
                cout << "NIE" << endl;
            } else {
                cout << "TAK" << endl;
                list.add(name, numberOfFans);
            }

        } else if (command == 2) {
            string temp2;
            long maxNumberOfFans;

            getline(cin, temp2);
            maxNumberOfFans = stol(temp2);

            Actor check = checkIfIsProperActorOnTheList(list, maxNumberOfFans);
            if (check.getNumberOfFans() == -1) {
                cout << "NIE" << endl;
            } else {
                cout << check.getName() << endl;
                list.remove(check.getName(), check.getNumberOfFans());
            }
        }
    }

    return 0;
}
