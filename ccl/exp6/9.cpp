#include <iostream>
using namespace std;

const int MAXN = 100005;
int bit[MAXN];
int n;

// Adds 'val' at position idx (1-indexed)
void update(int idx, int val) {
    for (; idx <= n; idx += idx & (-idx))
        bit[idx] += val;
}

// Returns prefix sum from index 1 to idx (1-indexed)
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & (-idx))
        sum += bit[idx];
    return sum;
}

void build(int arr[], int size) {
    n = size;
    for (int i = 1; i <= n; i++)
        update(i, arr[i - 1]);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int size = 6;

    build(arr, size);

    cout << "Prefix sum up to index 3: " << query(3) << endl;
    cout << "Prefix sum up to index 5: " << query(5) << endl;
    cout << "Prefix sum up to index 6: " << query(6) << endl;

    // arr[3] (1-indexed) changes from 5 to 10, so we add the difference: 10 - 5 = 5
    update(3, 5);
    cout << "\nAfter updating index 3 from 5 to 10:" << endl;
    cout << "Prefix sum up to index 3: " << query(3) << endl;
    cout << "Prefix sum up to index 5: " << query(5) << endl;
    cout << "Prefix sum up to index 6: " << query(6) << endl;

    return 0;
}