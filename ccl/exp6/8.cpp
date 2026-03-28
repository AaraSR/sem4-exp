#include <iostream>
using namespace std;

const int MAXN = 100005;
int seg[4 * MAXN];

void build(int arr[], int node, int start, int end) {
    if (start == end) {
        seg[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(arr, 2 * node,     start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return seg[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) +
           query(2 * node + 1, mid + 1, end, l, r);
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        seg[node] = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) update(2 * node,     start, mid,     idx, val);
        else            update(2 * node + 1, mid + 1, end,   idx, val);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = 6;

    build(arr, 1, 0, n - 1);

    cout << "Sum of range [1, 3]: " << query(1, 0, n - 1, 1, 3) << endl;
    cout << "Sum of range [2, 5]: " << query(1, 0, n - 1, 2, 5) << endl;

    update(1, 0, n - 1, 3, 10);
    cout << "\nAfter updating index 3 to value 10:" << endl;
    cout << "Sum of range [1, 3]: " << query(1, 0, n - 1, 1, 3) << endl;
    cout << "Sum of range [2, 5]: " << query(1, 0, n - 1, 2, 5) << endl;

    return 0;
}