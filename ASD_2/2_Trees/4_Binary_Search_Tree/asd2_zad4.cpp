#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node *lewy;
    Node *prawy;

    Node(int data) : data(data), lewy(nullptr), prawy(nullptr) {}
};

Node *insert(Node *root, int data) {
    if (root == nullptr) {
        return new Node(data);
    } else {
        if (data < root->data) {
            root->lewy = insert(root->lewy, data);
        } else {
            root->prawy = insert(root->prawy, data);
        }
    }
    return root;
}

unordered_set<int> nums;
vector<int> numss;

void inorderTraversal(Node *root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->lewy);
    nums.insert(root->data);
    numss.push_back(root->data);
    inorderTraversal(root->prawy);
}


Node *trimTree(Node *root, int min_val, int max_val) {
    if (root == nullptr) {
        return root;
    }

    root->lewy = trimTree(root->lewy, min_val, max_val);
    root->prawy = trimTree(root->prawy, min_val, max_val);

    if (root->data < min_val) {
        Node *rChild = root->prawy;
        delete root;
        return rChild;
    }

    if (root->data > max_val) {
        Node *lChild = root->lewy;
        delete root;
        return lChild;
    }

    return root;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;

    int min, max, sum;

    Node *root = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = insert(root, x);
    }

    cin >> min >> max;
    cin >> sum;

    Node *pNode = trimTree(root, min, max);

    inorderTraversal(pNode);

    bool found = false;
    int found1, found2;

    int diffrecne = sum;
    for (int i = 0; i < numss.size(); i++) {

        int y = numss[i];
        int x = sum - numss[i];

        if (nums.find(x) != nums.end() && nums.find(y) != nums.end()) {
            if (abs(x - y) < diffrecne) {
                diffrecne = abs(x - y);
                found = true;
                found1 = x;
                found2 = y;
            }
        }
    }

    if (found) {
        if (found1 < found2) {
            cout << found1 << " " << found2 << endl;
        } else {
            cout << found2 << " " << found1 << endl;
        }
    } else {
        cout << "NIE ZNALEZIONO" << endl;
    }

    return 0;
}