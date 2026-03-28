#include <iostream>
using namespace std;

const int T = 3;

struct BTreeNode {
    int keys[2 * T - 1];
    BTreeNode* children[2 * T];
    int n;
    bool leaf;

    BTreeNode(bool isLeaf) {
        leaf = isLeaf;
        n = 0;
        for (int i = 0; i < 2 * T; i++)
            children[i] = nullptr;
    }
};

class BTree {
    BTreeNode* root;

    void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
        BTreeNode* newNode = new BTreeNode(child->leaf);
        newNode->n = T - 1;

        for (int j = 0; j < T - 1; j++)
            newNode->keys[j] = child->keys[j + T];

        if (!child->leaf)
            for (int j = 0; j < T; j++)
                newNode->children[j] = child->children[j + T];

        child->n = T - 1;

        for (int j = parent->n; j >= i + 1; j--)
            parent->children[j + 1] = parent->children[j];
        parent->children[i + 1] = newNode;

        for (int j = parent->n - 1; j >= i; j--)
            parent->keys[j + 1] = parent->keys[j];
        parent->keys[i] = child->keys[T - 1];
        parent->n++;
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->n - 1;
        if (node->leaf) {
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->n++;
        } else {
            while (i >= 0 && node->keys[i] > key) i--;
            i++;
            if (node->children[i]->n == 2 * T - 1) {
                splitChild(node, i, node->children[i]);
                if (node->keys[i] < key) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

    void traverse(BTreeNode* node) {
        int i;
        for (i = 0; i < node->n; i++) {
            if (!node->leaf) traverse(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->leaf) traverse(node->children[i]);
    }

    int findKey(BTreeNode* node, int key) {
        int idx = 0;
        while (idx < node->n && node->keys[idx] < key) idx++;
        return idx;
    }

    void removeFromLeaf(BTreeNode* node, int idx) {
        for (int i = idx + 1; i < node->n; i++)
            node->keys[i - 1] = node->keys[i];
        node->n--;
    }

    int getPredecessor(BTreeNode* node, int idx) {
        BTreeNode* cur = node->children[idx];
        while (!cur->leaf) cur = cur->children[cur->n];
        return cur->keys[cur->n - 1];
    }

    int getSuccessor(BTreeNode* node, int idx) {
        BTreeNode* cur = node->children[idx + 1];
        while (!cur->leaf) cur = cur->children[0];
        return cur->keys[0];
    }

    void merge(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys[T - 1] = node->keys[idx];
        for (int i = 0; i < sibling->n; i++)
            child->keys[i + T] = sibling->keys[i];
        if (!child->leaf)
            for (int i = 0; i <= sibling->n; i++)
                child->children[i + T] = sibling->children[i];

        for (int i = idx + 1; i < node->n; i++)
            node->keys[i - 1] = node->keys[i];
        for (int i = idx + 2; i <= node->n; i++)
            node->children[i - 1] = node->children[i];

        child->n += sibling->n + 1;
        node->n--;
        delete sibling;
    }

    void borrowFromPrev(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx - 1];

        for (int i = child->n - 1; i >= 0; i--)
            child->keys[i + 1] = child->keys[i];
        if (!child->leaf)
            for (int i = child->n; i >= 0; i--)
                child->children[i + 1] = child->children[i];

        child->keys[0] = node->keys[idx - 1];
        if (!child->leaf)
            child->children[0] = sibling->children[sibling->n];

        node->keys[idx - 1] = sibling->keys[sibling->n - 1];
        child->n++;
        sibling->n--;
    }

    void borrowFromNext(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys[child->n] = node->keys[idx];
        if (!child->leaf)
            child->children[child->n + 1] = sibling->children[0];

        node->keys[idx] = sibling->keys[0];
        for (int i = 1; i < sibling->n; i++)
            sibling->keys[i - 1] = sibling->keys[i];
        if (!sibling->leaf)
            for (int i = 1; i <= sibling->n; i++)
                sibling->children[i - 1] = sibling->children[i];

        child->n++;
        sibling->n--;
    }

    void fill(BTreeNode* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->n >= T)
            borrowFromPrev(node, idx);
        else if (idx != node->n && node->children[idx + 1]->n >= T)
            borrowFromNext(node, idx);
        else {
            if (idx != node->n) merge(node, idx);
            else merge(node, idx - 1);
        }
    }

    void removeFromNonLeaf(BTreeNode* node, int idx) {
        int key = node->keys[idx];
        if (node->children[idx]->n >= T) {
            int pred = getPredecessor(node, idx);
            node->keys[idx] = pred;
            remove(node->children[idx], pred);
        } else if (node->children[idx + 1]->n >= T) {
            int succ = getSuccessor(node, idx);
            node->keys[idx] = succ;
            remove(node->children[idx + 1], succ);
        } else {
            merge(node, idx);
            remove(node->children[idx], key);
        }
    }

    void remove(BTreeNode* node, int key) {
        int idx = findKey(node, key);
        if (idx < node->n && node->keys[idx] == key) {
            if (node->leaf) removeFromLeaf(node, idx);
            else removeFromNonLeaf(node, idx);
        } else {
            if (node->leaf) {
                cout << "Key " << key << " not found.\n";
                return;
            }
            bool isLast = (idx == node->n);
            if (node->children[idx]->n < T) fill(node, idx);
            if (isLast && idx > node->n)
                remove(node->children[idx - 1], key);
            else
                remove(node->children[idx], key);
        }
    }

public:
    BTree() { root = nullptr; }

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->keys[0] = key;
            root->n = 1;
        } else {
            if (root->n == 2 * T - 1) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children[0] = root;
                splitChild(newRoot, 0, root);
                int i = (newRoot->keys[0] < key) ? 1 : 0;
                insertNonFull(newRoot->children[i], key);
                root = newRoot;
            } else {
                insertNonFull(root, key);
            }
        }
    }

    void remove(int key) {
        if (root == nullptr) { cout << "Tree is empty.\n"; return; }
        remove(root, key);
        if (root->n == 0) {
            BTreeNode* temp = root;
            root = root->leaf ? nullptr : root->children[0];
            delete temp;
        }
    }

    void traverse() {
        if (root != nullptr) traverse(root);
        cout << endl;
    }
};

int main() {
    BTree t;
    t.insert(10); t.insert(20); t.insert(5);
    t.insert(6);  t.insert(12); t.insert(30);
    t.insert(7);  t.insert(17);

    cout << "B-Tree traversal: ";
    t.traverse();

    t.remove(6);
    cout << "After removing 6: ";
    t.traverse();

    t.remove(17);
    cout << "After removing 17: ";
    t.traverse();

    return 0;
}