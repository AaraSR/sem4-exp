#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void findTopoSort(int node, vector<int>& vis, vector<vector<int>>& adj, stack<int>& st) {
    vis[node] = 1;
    for (int it : adj[node]) {
        if (!vis[it]) {
            findTopoSort(it, vis, adj, st);
        }
    }

    st.push(node);
}

vector<int> topoSort(vector<vector<int>>& adj) {
    int n = adj.size();
    stack<int> st;
    vector<int> vis(n, 0);

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            findTopoSort(i, vis, adj, st);
        }
    }

    vector<int> topo;
    
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}


void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    
    addEdge(adj, 0, 1);
    addEdge(adj, 2, 1);
    addEdge(adj, 3, 2);
    addEdge(adj, 4, 2);

    vector<int> res = topoSort(adj);
    for (int vertex : res)
        cout << vertex << " ";
    cout << endl;
}
