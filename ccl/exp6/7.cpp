#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    Node(int val) {
        data = val;
        color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree {
    Node* root;
    Node* NIL;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)       root = y;
        else if (x == x->parent->left) x->parent->left  = y;
        else                            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)       root = x;
        else if (y == y->parent->left) y->parent->left  = x;
        else                            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
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
                Node* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
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

    // Checks: no two consecutive red nodes, and equal black-height on all paths
    bool checkProperties(Node* node, int blackCount, int& pathBlackCount) {
        if (node == NIL) {
            if (pathBlackCount == -1) pathBlackCount = blackCount;
            return blackCount == pathBlackCount;
        }
        if (node->color == RED)
            if (node->left->color == RED || node->right->color == RED)
                return false;
        if (node->color == BLACK) blackCount++;
        return checkProperties(node->left, blackCount, pathBlackCount) &&
               checkProperties(node->right, blackCount, pathBlackCount);
    }

    void inorder(Node* node) {
        if (node == NIL) return;
        inorder(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorder(node->right);
    }

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(int key) {
        Node* z = new Node(key);
        z->left = z->right = NIL;

        Node* y = nullptr;
        Node* x = root;

        while (x != NIL) {
            y = x;
            if (z->data < x->data) x = x->left;
            else x = x->right;
        }
        z->parent = y;

        if (y == nullptr)           root = z;
        else if (z->data < y->data) y->left  = z;
        else                        y->right = z;

        fixInsert(z);
    }

    bool isValidRBTree() {
        if (root == NIL) return true;
        if (root->color != BLACK) return false;
        int pathBlackCount = -1;
        return checkProperties(root, 0, pathBlackCount);
    }

    void inorder() { inorder(root); cout << endl; }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);

    cout << "Inorder traversal (R=Red, B=Black): ";
    rbt.inorder();

    cout << "Is valid Red-Black Tree: " << (rbt.isValidRBTree() ? "Yes" : "No") << endl;

    return 0;
}