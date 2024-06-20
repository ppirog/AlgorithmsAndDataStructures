#include<iostream>

using namespace std;

class BTreeNode {
    pair<string, string> *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
public:
    BTreeNode(int t1, bool leaf1);
    void insertNonFull(pair<string, string> k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode *search(string k,string &res);
    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int t;
public:

    explicit BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() { if (root != nullptr) root->traverse(); }

    BTreeNode *search(string k,string &res) {
        if (root == nullptr) {
            return nullptr;
        } else {
            return root->search(k,res);
        }
    }

    void insert(pair<string, string> k);
    void update(pair<string ,string> k);

};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new pair<string, string>[2 * t - 1]; //new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}


void BTreeNode::traverse() {

    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i].first << " " << keys[i].second;
    }

    if (!leaf)
        C[i]->traverse();
}


BTreeNode *BTreeNode::search(string k,string& res) {

    int i = 0;
    while (i < n && k > keys[i].first)
        i++;

    if (keys[i].first == k) {
        res = keys[i].second;
        return this;
    }

    if (leaf)
        return nullptr;


    return C[i]->search(k,res);
}


void BTree::insert(pair<string, string> k) {


    if (root == nullptr) {

        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {

        if (root->n == 2 * t - 1) {

            BTreeNode *s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else
            root->insertNonFull(k);
    }
}

void BTree::update(pair<string, string> k) {

    string res;
    BTreeNode *temp = search(k.first,res);
    if (temp == nullptr) {
        insert(k);
    }else{
        for (int i = 0; i < temp->n; ++i) {
            if (temp->keys[i].first == k.first) {
                temp->keys[i].second = k.second;
                break;
            }
        }
    }


}

void BTreeNode::insertNonFull(pair<string, string> k) {
    int i = n - 1;


    if (leaf) {

        while (i >= 0 && keys[i].first > k.first) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    } else {

        while (i >= 0 && keys[i].first > k.first)
            i--;


        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;


    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n = n + 1;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    BTree t(10);

    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        string temp, a, b;

        getline(cin, temp);

        if (temp.find(':') != string::npos) {
            a = temp.substr(0, temp.find(":"));
            b = temp.substr(temp.find(":") + 1);

            if (b[0] == ' ') {
                b = b.substr(1);
            }

            t.update({a, b});

        } else {
            a = temp;
            string res;
            BTreeNode *temp = t.search(a,res);
            if (temp == nullptr) {
                cout << "BRAK\n";
            }else{
                cout << res << "\n";
            }
        }
    }

    return 0;
}