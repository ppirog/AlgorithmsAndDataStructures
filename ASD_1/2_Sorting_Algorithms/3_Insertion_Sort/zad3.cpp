#include <iostream>
#include <string>

using namespace std;

const int MAX = 1000003;

class Person {
private:
    string name;
    int num;
public:
    Person(const string &name, int num) : name(name), num(num) {}

    Person() {}

    const string &getName() const {
        return name;
    }

    int getNum() const {
        return num;
    }
};

bool generalComparator(const Person &firstPerson, const Person &secondPerson) {
    int num1 = firstPerson.getNum() - secondPerson.getNum();
    if (num1 == 0) {
        return firstPerson.getName() > secondPerson.getName();
    } else {
        return num1 < 0;
    }
}

int countedTime(Person *persons, int n) {
    long long time = 0;
    for (int i = 0; i < n; i++) {
        time += 1 + i * persons[i].getNum();
    }
    return time % MAX;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        int n, p;
        cin >> n >> p;
        cin.ignore();
        Person *persons = new Person[n];
        for (int j = 0; j < n; j++) {
            string name;
            int num;
            cin >> name >> num;
            cin.ignore();
            Person tab = Person(name, num);

            int k;
            for (k = j; k > 0 && generalComparator(persons[k - 1], tab); k--) {
                persons[k] = persons[k - 1];
            }

            persons[k] = Person(name, num);

        }

        for (int k = 0; k < p; k++) {
            cout << persons[k].getName() << " ";
        }

        cout << '\n';
        cout << countedTime(persons, n) << '\n';

        delete[] persons;
    }

    return 0;
}
