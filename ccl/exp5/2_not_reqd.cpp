#include <iostream>
#include <vector>
using namespace std;

// helping (utility) DFS function to detect cycle in a directed graph
bool isCyclicUtil(vector<vector<int>>& adj, int u, vector<bool>& visited, vector<bool>& recStack) {
    
    // it is in the path of checking 'isCycle', hence cycle exists!
    if (recStack[u]) return true;
    
    // already visited
    if (visited[u]) return false;   

    visited[u] = true;
    recStack[u] = true;

    // recursive func adj nodes
    for (int v : adj[u]) {
        if (isCyclicUtil(adj, v, visited, recStack))
            return true;
    }
    // before backtracking, removing 'u' from recStack[]
    recStack[u] = false; 
    return false;
}

// Function to detect cycle in a directed graph
bool isCyclic(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    // dfs on every node
    for (int i = 0; i < V; i++) {
        if (!visited[i] && isCyclicUtil(adj, i, visited, recStack))
            return true;
    }
    return false;
}

int main() {
    vector<vector<int>> adj = {{1},{2},{0, 3}};
    /* adj list:
        0    1    2    3
    0   0    1    0    0
    1   0    0    1    0
    2   1    0    1    0
    3   0    0    0    0
    */
    
    cout << (isCyclic(adj) ? "true" : "false") << endl;

    return 0;
}