using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include <string>

struct element {
    string wartosc;
    element *nastepny;
    element *poprzedni;
};

class Lista {
private:
    element *pierwszy;
    element *ostatni;
    int counter;

public:
    Lista() : pierwszy(nullptr), ostatni(nullptr), counter(0) {}

    ~Lista() {
        element *pom;
        while (pierwszy != nullptr) {
            pom = pierwszy;
            pierwszy = pierwszy->nastepny;
            delete pom;
        }
    }

    void push_back(string value) {
        element *newElement = new element{value, nullptr};
        if (empty()) {
            pierwszy = ostatni = newElement;
        } else {
            newElement->poprzedni = ostatni;
            ostatni->nastepny = newElement;
            ostatni = newElement;
        }
        counter++;
    }

    int size() {
        return this->counter;
    }

    string front() {
        if (pierwszy != nullptr) {
            return pierwszy->wartosc;
        }
    }

    string back() {
        if (pierwszy != nullptr) {
            return ostatni->wartosc;
        }
    }

    void push_front(string value) {
        element *newElement = new element{value, pierwszy};
        if (empty()) {
            pierwszy = ostatni = newElement;
        } else {
            pierwszy->poprzedni = newElement;

            element *temp = pierwszy;
            pierwszy = newElement;
            pierwszy->nastepny = temp;

        }
        counter++;
    }

    bool empty() {
        return (pierwszy == nullptr);
    }

    void pop_front() {
        if (pierwszy != nullptr) {
            element *pom = pierwszy;
            pierwszy = pierwszy->nastepny;

            if (pierwszy != nullptr) {
                pierwszy->poprzedni = nullptr;
            }

            delete pom;
            counter--;
        }
    }

    void pop_back() {
        if (pierwszy != nullptr) {
            if (pierwszy->nastepny == nullptr) {
                delete pierwszy;
                pierwszy = ostatni = nullptr;
            } else {
                element *it = ostatni;
                ostatni = ostatni->poprzedni;
                ostatni->nastepny = nullptr;
                delete it;
            }
            counter--;
        }
    }

    void insert(string value, int pos) {
        if (pos < 0 || pos > counter) {
            cout << "Invalid position\n";
            return;
        }

        element *srodkowy = new element{value, nullptr, nullptr};

        if (pos == 0) {

            srodkowy->nastepny = pierwszy;
            if (pierwszy != nullptr) {
                pierwszy->poprzedni = srodkowy;
            }
            pierwszy = srodkowy;

            if (empty()) {
                ostatni = srodkowy;
            }

        } else if (pos == counter) {

            ostatni->nastepny = srodkowy;
            srodkowy->poprzedni = ostatni;
            ostatni = srodkowy;

        } else {

            element *pom = pierwszy;
            for (int i = 0; i < pos - 1; ++i) {
                pom = pom->nastepny;
            }

            srodkowy->nastepny = pom->nastepny;
            srodkowy->poprzedni = pom;
            pom->nastepny->poprzedni = srodkowy;
            pom->nastepny = srodkowy;

        }

        counter++;
    }

    void display() {
        element *current = pierwszy;

        while (current != nullptr) {
            cout << current->wartosc << "\n";
            current = current->nastepny;
        }
    }

    element *first() {
        return pierwszy;
    }

    element *last() {
        return ostatni;
    }


    void swap(element *a, element *b) {

        if (a == b) return;
        string temp = a->wartosc;
        a->wartosc = b->wartosc;
        b->wartosc = temp;
    }


    void moveElementDown(element *a, int howManyIndexToMove) {
        if (a == nullptr || a->nastepny == nullptr) return;
        if (howManyIndexToMove == 0)return;

        element *temp = a;
        for (int i = 0; i < howManyIndexToMove; ++i) {
            if (temp->nastepny == nullptr) return;
            temp = temp->nastepny;
        }

        if (temp->nastepny == nullptr) {
            if (a->poprzedni != nullptr)
                a->poprzedni->nastepny = a->nastepny;
            else
                pierwszy = a->nastepny;

            if (a->nastepny != nullptr)
                a->nastepny->poprzedni = a->poprzedni;
            else
                ostatni = a->poprzedni;

            temp->nastepny = a;
            a->poprzedni = temp;
            a->nastepny = nullptr;
            ostatni = a;
        } else {
            element *temp2 = temp->nastepny;

            if (a->poprzedni != nullptr)
                a->poprzedni->nastepny = a->nastepny;
            else
                pierwszy = a->nastepny;

            if (a->nastepny != nullptr)
                a->nastepny->poprzedni = a->poprzedni;

            temp->nastepny = a;
            a->poprzedni = temp;
            a->nastepny = temp2;
            temp2->poprzedni = a;
        }

    }

    void moveElementUp(element *a, int howManyIndexToMove) {
        if (a == nullptr || a->poprzedni == nullptr) return;
        if (howManyIndexToMove == 0)return;

        element *temp = a;
        for (int i = 0; i < howManyIndexToMove; ++i) {
            if (temp->poprzedni == nullptr) return;
            temp = temp->poprzedni;
        }

        if (temp->poprzedni == nullptr) {
            if (a->poprzedni != nullptr)
                a->poprzedni->nastepny = a->nastepny;
            else
                pierwszy = a->nastepny;

            if (a->nastepny != nullptr)
                a->nastepny->poprzedni = a->poprzedni;

            a->nastepny = temp;
            a->poprzedni = nullptr;
            temp->poprzedni = a;
            pierwszy = a;
        } else {
            element *temp2 = temp->poprzedni;

            if (a->poprzedni != nullptr)
                a->poprzedni->nastepny = a->nastepny;
            else
                pierwszy = a->nastepny;

            if (a->nastepny != nullptr)
                a->nastepny->poprzedni = a->poprzedni;

            temp2->nastepny = a;
            a->poprzedni = temp2;
            a->nastepny = temp;
            temp->poprzedni = a;
        }
    }

};

enum Color { RED, BLACK };


struct Node {
    std::string key;
    element* value;
    Color color;
    Node *left, *right, *parent;

    Node(std::string key, element* value) : key(key), value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void insertFixup(Node* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    Node* searchNode(const std::string& key) {
        Node* x = root;

        while (x != nullptr && key != x->key) {
            if (key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        return x;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const std::string& key, element* value) {
        Node* z = new Node(key, value);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key == x->key) {
                x->value = value;
                delete z;
                return;
            }
            else if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = nullptr;
        z->right = nullptr;
        z->color = RED;

        insertFixup(z);
    }


    element* search(const std::string& key) {
        Node* resultNode = searchNode(key);
        if (resultNode)
            return resultNode->value;
        else
            return nullptr;
    }
};
int main() {
    Lista lista;
//    map < string, element * > mapa;
    RedBlackTree tree;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        lista.push_back(s);
        element *temp = lista.last();
//        mapa.insert(pair<string, element *>(s, temp));
        tree.insert(s, temp);
    }
    cin >> m;

    for (int i = 0; i < m; ++i) {
        char op;
        string s1, s2;
        int ile;
        cin >> op;

        if (op == 'a') {
            cin >> s1;
            lista.push_back(s1);

            element *temp = lista.last();
//            mapa.insert(pair<string, element *>(s1, temp));
            tree.insert(s1, temp);
        } else if (op == 'r') {
            cin >> s1 >> s2;

            element *temp1 = tree.search(s1);
            element *temp2 = tree.search(s2);
            lista.swap(temp1, temp2);
//            mapa[s1] = temp2;
//            mapa[s2] = temp1;
            tree.insert(s1,temp2);
            tree.insert(s2,temp1);
        } else if (op == 'm') {
            cin >> s1 >> ile;

            if (ile > 0) {
                lista.moveElementUp(tree.search(s1), abs(ile));
            } else {
                lista.moveElementDown(tree.search(s1), abs(ile));
            }
        }
    }
    lista.display();


    return 0;
}