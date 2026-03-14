#include <bits/stdc++.h>
using namespace std;

vector<string> generateBinary(int n) {
    vector<string> result;
    queue<string> q;

    q.push("1");

    for (int i = 0; i < n; i++) {
        string curr = q.front();
        q.pop();
        result.push_back(curr);
        q.push(curr + "0");
        q.push(curr + "1");
    }

    return result;
}

int main() {
    int n;

    cout << "Enter the number: ";
    cin >> n;

    vector<string> ans = generateBinary(n);

    for (string s : ans)
        cout << s << " ";

    cout << "\n";
    
    return 0;
}
