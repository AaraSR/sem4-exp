#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int key) {
    if (root == nullptr) return new Node(key);
    if (key < root->data) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

int height(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(height(root->left), height(root->right));
}

bool isValidBST(Node* root, int minVal, int maxVal) {
    if (root == nullptr) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isValidBST(root->left, minVal, root->data) &&
           isValidBST(root->right, root->data, maxVal);
}

Node* findLCA(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;
    if (root->data > n1 && root->data > n2)
        return findLCA(root->left, n1, n2);
    if (root->data < n1 && root->data < n2)
        return findLCA(root->right, n1, n2);
    return root;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    cout << "Height of tree: " << height(root) << endl;
    cout << "Is valid BST: " << (isValidBST(root, INT_MIN, INT_MAX) ? "Yes" : "No") << endl;

    Node* lca = findLCA(root, 20, 40);
    cout << "LCA of 20 and 40: " << lca->data << endl;

    lca = findLCA(root, 20, 70);
    cout << "LCA of 20 and 70: " << lca->data << endl;

    return 0;
}