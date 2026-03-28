#include <iostream>
using namespace std;

struct Node {
    int data, height;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int getBalance(Node* node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

Node* rightRotate(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left  = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;
    y->left  = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (root == nullptr) return new Node(key);

    if (key < root->data)      root->left  = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    else return root;

    updateHeight(root);
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->data)       return rightRotate(root);           // LL
    if (balance < -1 && key > root->right->data)      return leftRotate(root);            // RR
    if (balance > 1 && key > root->left->data) {      // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->data) {   // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool isHeightBalanced(Node* root) {
    if (root == nullptr) return true;
    int balance = getBalance(root);
    if (balance < -1 || balance > 1) return false;
    return isHeightBalanced(root->left) && isHeightBalanced(root->right);
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);  // triggers RR rotation
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);  // triggers RL rotation

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    cout << "Is height balanced: " << (isHeightBalanced(root) ? "Yes" : "No") << endl;

    return 0;
}