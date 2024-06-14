#include <iostream>
#include <string>

using namespace std;

int returnPriority(char item) {
    if (item == '+' || item == '-') {
        return 1;
    } else if (item == '*' || item == '/') {
        return 2;
    } else {
        return 0;
    }
}

template<typename T>
class MyQueue {
private:
    T *tab;
    unsigned int head, tail;
    unsigned int queueSize;
public:
    MyQueue() {
        head = 0;
        tail = 0;
        queueSize = 100;
        tab = new T[queueSize]();
    }

    virtual ~MyQueue();

    T pop() {
        T item = tab[head];
        head = (head + 1) % queueSize;
        return item;
    };

    void push(T item) {

        tab[tail] = item;
        tail = (tail + 1) % queueSize;
        if (tail == head) {
            T *tab_pom = new T[queueSize * 2];
            unsigned int i = 0;
            do {
                tab_pom[i] = tab[head];
                head = (head + 1) % queueSize;
                i++;
            } while (head != tail);

            delete[] tab;
            tab = tab_pom;
            head = 0;
            tail = queueSize;
            queueSize *= 2;
        }

    };

    T front() {
        return tab[head];
    };

    bool isEmpty() {
        if (head == tail) {
            return true;
        } else {
            return false;
        }
    };

};

template<typename T>
MyQueue<T>::~MyQueue() {
    delete[] tab;
}

template<typename T>
class MyStack {
private:
    T *elements;
    int maxStackSize;
    int size;
public:
    MyStack() : maxStackSize(2), size(0) {
        elements = new T[maxStackSize];
    }

    void push(T item) {
        if (size == maxStackSize) {

            maxStackSize *= 2;
            T *temp = new T[maxStackSize];


            for (int i = 0; i < size; ++i) {
                temp[i] = elements[i];
            }

            delete[] elements;

            elements = temp;
        }

        elements[size] = item;
        size++;
    };

    void pop() {
        if (size > 0) {
            size--;
        }
    }

    T top() {
        if (size > 0) {
            return elements[size - 1];
        }
    };

    bool isEmpty() {
        return size == 0;
    };

};


string addSpaces(string basicString) {
    string result;

    for (int i = 0; i < basicString.length(); i++) {
        result = basicString[i];

    }
}

bool isOperator(char item) {
    return item == '+' || item == '-' || item == '*' || item == '/' || item == '(' || item == ')' || item == '{' ||
           item == '}' || item == '[' || item == ']';
}

bool isAction(int item) {
    return item == '+' || item == '-' || item == '*' || item == '/';
}

bool isNumber(char item) {
    return item >= '0' && item <= '9';
}

bool isLeftBracket(char item) {
    return item == '(' || item == '{' || item == '[';
}

bool isRightBracket(char item) {
    return item == ')' || item == '}' || item == ']';
}

bool isMatchingBracket(char left, char right) {
    return (left == '(' && right == ')') || (left == '{' && right == '}') || (left == '[' && right == ']');
}

int getNumber(string basicString, int position) {
    string number;

    while (isNumber(basicString[position])) {
        number += basicString[position];
        position++;
    }

    return stoi(number);
}

void przelicz(MyQueue<int> &numbers, MyQueue<bool> &isANumber) {

    bool correct = true;

    MyStack<double> stos = MyStack<double>();

    for (int i = 0; !numbers.isEmpty(); ++i) {
        if (!isANumber.front()) {
            char op = (char) numbers.front();

            double num1;
            if (!stos.isEmpty()) {
                num1 = stos.top();
            } else {
                correct = false;
                break;
            }
            stos.pop();

            double num2;
            if (!stos.isEmpty()) {
                num2 = stos.top();
            } else {
                correct = false;
                break;

            }
            stos.pop();

            if (op == '+') {
                stos.push(num1 + num2);
            } else if (op == '-') {
                stos.push(num2 - num1);
            } else if (op == '*') {
                stos.push(num1 * num2);
            } else if (op == '/') {
                if (num1 == 0.0) {
                    correct = false;
                }

                stos.push((double) num2 / (double) num1);
            }


        } else {
            stos.push(numbers.front());
        }
        numbers.pop();
        isANumber.pop();
    }


    if (correct) {
        cout << stos.top() << "\n";
    } else {
        cout << "BLAD" << "\n";
    }

}

bool infixToPostfix(MyQueue<int> &infix, MyQueue<bool> &isANumber) {
    bool correct = true;

    MyStack<char> stack = MyStack<char>();
    MyQueue<int> numbers = MyQueue<int>();
    MyQueue<bool> checker = MyQueue<bool>();


    for (int i = 0; !infix.isEmpty(); i++) {
        if (!isANumber.front()) {

            if (isOperator((char) infix.front())) {
                char op = (char) infix.front();
                // + - * /
                if (isAction(op)) {

                    char temp;
                    if (!stack.isEmpty()) {
                        temp = stack.top();
                    }

                    while (!stack.isEmpty() && isAction(temp) &&
                           returnPriority(temp) >= returnPriority(op)) {

                        numbers.push(temp);
                        checker.push(false);

                        stack.pop();
                        if (!stack.isEmpty()) {
                            temp = stack.top();
                        }
                    }
                    stack.push(op);
                }

                //nawiasy
                if (isLeftBracket(op) || isRightBracket(op)) {


                    if (isLeftBracket(op)) {
                        if (op == '(') {
                            stack.push(op);
                        }
                        if (op == '[') {
                            stack.push(op);
                        }
                        if (op == '{') {
                            stack.push(op);
                        }
                    }

                    if (isRightBracket(op)) {
                        if (stack.isEmpty()) {
                            correct = false;
                            break;
                        } else {

                            if (op == ')') {
                                if (stack.isEmpty()) {
                                    correct = false;
                                    break;
                                } else {
                                    char temp = stack.top();

                                    if (temp == '{') {
                                        correct = false;
                                        break;
                                    }
                                    if (temp == '[') {
                                        correct = false;
                                        break;
                                    }

                                    if (temp == ')') {
                                        correct = false;
                                        break;
                                    }
                                    if (temp == '}') {
                                        correct = false;
                                        break;
                                    }
                                    if (temp == ']') {
                                        correct = false;
                                        break;
                                    }

                                    while (temp != '(') {
                                        //dodać warunki błędu
                                        if (stack.isEmpty()) {
                                            correct = false;
                                            break;
                                        }
                                        if (temp == '{') {
                                            correct = false;
                                            break;
                                        }
                                        if (temp == '[') {
                                            correct = false;
                                            break;
                                        }

                                        numbers.push(temp);
                                        checker.push(false);
                                        stack.pop();
                                        if (!stack.isEmpty()) {
                                            temp = stack.top();
                                        }

                                    }
                                    stack.pop();
                                }


                            } else if (op == ']') {
                                char temp = stack.top();

                                if (temp == '{') {
                                    correct = false;
                                    break;
                                }
                                if (temp == '(') {
                                    correct = false;
                                    break;
                                }

                                while (temp != '[') {
                                    //dodać warunki błędu
                                    if (stack.isEmpty()) {
                                        correct = false;
                                        break;
                                    }


                                    if (temp == '{') {
                                        correct = false;
                                        break;
                                    }
                                    if (temp == '(') {
                                        correct = false;
                                        break;
                                    }


                                    numbers.push(temp);
                                    checker.push(false);
                                    stack.pop();
                                    if (!stack.isEmpty()) {
                                        temp = stack.top();
                                    }
                                }
                                stack.pop();
                            } else if (op == '}') {
                                char temp = stack.top();

                                if (temp == '[') {
                                    correct = false;
                                    break;
                                }
                                if (temp == '(') {
                                    correct = false;
                                    break;
                                }

                                while (temp != '{') {
                                    //dodać warunki błędu

                                    if (stack.isEmpty()) {
                                        correct = false;
                                        break;
                                    }

                                    if (temp == '[') {
                                        correct = false;
                                        break;
                                    }
                                    if (temp == '(') {
                                        correct = false;
                                        break;
                                    }

                                    numbers.push(temp);
                                    checker.push(false);

                                    stack.pop();
                                    if (!stack.isEmpty()) {
                                        temp = stack.top();
                                    }
                                }
                                stack.pop();
                            }
                        }


                    }
                }

            }
        } else {
            numbers.push(infix.front());
            checker.push(true);
        }


        isANumber.pop();
        infix.pop();
    }

    while (!stack.isEmpty()) {
        char op = stack.top();
        if (isRightBracket(op) || isLeftBracket(op)) {
            correct = false;
            break;
        }
        numbers.push(op);
        checker.push(false);
        stack.pop();
    }

    if (correct) {
        przelicz(numbers, checker);
    } else {
        cout << "BLAD\n";
    }

//    for (int i = 0; !numbers.isEmpty(); ++i) {
//        if (checker.front()) {
//            cout << numbers.front() << " ";
//        } else {
//            cout << (char) numbers.front() << " ";
//        }
//        numbers.pop();
//        checker.pop();
//    }
//    cout << "\n";

    return correct;
}

int main() {


    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        MyQueue<int> infix = MyQueue<int>();

        MyQueue<bool> isANumber = MyQueue<bool>();

        string num = "";
        for (int i = 0; i < line.length(); ++i) {
            char temp = line[i];

            if (i == 0 && temp == '-') {
                infix.push(0);
                isANumber.push(true);
            }

            if (isOperator(temp)) {

                if (num != "") {
                    infix.push(stoi(num));
                    isANumber.push(true);
                    num = "";
                }

                infix.push(temp);
                isANumber.push(false);

            } else {
                if (temp >= '0' && temp <= '9') {
                    if (temp == '0') {
                        num += '0';
                    } else if (temp == '1') {
                        num += '1';
                    } else if (temp == '2') {
                        num += '2';
                    } else if (temp == '3') {
                        num += '3';
                    } else if (temp == '4') {
                        num += '4';
                    } else if (temp == '5') {
                        num += '5';
                    } else if (temp == '6') {
                        num += '6';
                    } else if (temp == '7') {
                        num += '7';
                    } else if (temp == '8') {
                        num += '8';
                    } else if (temp == '9') {
                        num += '9';
                    }
                }
                if (i == line.length() - 1 && num != "") {
                    infix.push(stoi(num));
                    isANumber.push(true);
                    num = "";
                }
            }
        }

        infixToPostfix(infix, isANumber);

    }

    return 0;
}
