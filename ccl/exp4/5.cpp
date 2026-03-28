#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i])
            st.pop();

        nge[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }

    return nge;
}

int main() {
    vector<int> arr = {1, 3, 2, 4};
    vector<int> result = nextGreaterElement(arr);

    for (int x : result)
        cout << x << " ";

    cout << endl;
    return 0;
}