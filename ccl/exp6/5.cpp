#include <iostream>
using namespace std;

const int ORDER = 4;

struct Node {
    bool leaf;
    int n;
    int keys[ORDER];
    Node* children[ORDER + 1];
    Node* next;

    Node(bool isLeaf) {
        leaf = isLeaf;
        n = 0;
        next = nullptr;
        for (int i = 0; i <= ORDER; i++)
            children[i] = nullptr;
    }
};

class BPlusTree {
    Node* root;

    // Returns promoted key and new node if a split happened, else {-1, nullptr}
    pair<int, Node*> insertHelper(Node* node, int key) {
        if (node->leaf) {
            int i = node->n - 1;
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->n++;

            if (node->n < ORDER)
                return {-1, nullptr};

            // Split the leaf
            Node* newLeaf = new Node(true);
            int mid = ORDER / 2;
            newLeaf->n = node->n - mid;
            for (int j = 0; j < newLeaf->n; j++)
                newLeaf->keys[j] = node->keys[j + mid];
            node->n = mid;
            newLeaf->next = node->next;
            node->next = newLeaf;
            return {newLeaf->keys[0], newLeaf};
        } else {
            int i = 0;
            while (i < node->n && node->keys[i] <= key) i++;

            auto [promKey, newChild] = insertHelper(node->children[i], key);

            if (newChild == nullptr)
                return {-1, nullptr};

            for (int j = node->n; j > i; j--)
                node->keys[j] = node->keys[j - 1];
            for (int j = node->n + 1; j > i + 1; j--)
                node->children[j] = node->children[j - 1];

            node->keys[i] = promKey;
            node->children[i + 1] = newChild;
            node->n++;

            if (node->n < ORDER)
                return {-1, nullptr};

            // Split internal node
            Node* newNode = new Node(false);
            int mid = ORDER / 2;
            int upKey = node->keys[mid];
            newNode->n = node->n - mid - 1;
            for (int j = 0; j < newNode->n; j++)
                newNode->keys[j] = node->keys[j + mid + 1];
            for (int j = 0; j <= newNode->n; j++)
                newNode->children[j] = node->children[j + mid + 1];
            node->n = mid;
            return {upKey, newNode};
        }
    }

public:
    BPlusTree() { root = new Node(true); }

    void insert(int key) {
        auto [promKey, newNode] = insertHelper(root, key);
        if (newNode != nullptr) {
            Node* newRoot = new Node(false);
            newRoot->keys[0] = promKey;
            newRoot->children[0] = root;
            newRoot->children[1] = newNode;
            newRoot->n = 1;
            root = newRoot;
        }
    }

    // Traverse only through leaf nodes (all data is in leaves, linked together)
    void traverse() {
        Node* cur = root;
        while (!cur->leaf)
            cur = cur->children[0];
        while (cur != nullptr) {
            for (int i = 0; i < cur->n; i++)
                cout << cur->keys[i] << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

int main() {
    BPlusTree t;
    t.insert(10); t.insert(20); t.insert(5);
    t.insert(6);  t.insert(12); t.insert(30);
    t.insert(7);  t.insert(17);

    cout << "B+ Tree sorted traversal: ";
    t.traverse();

    return 0;
}