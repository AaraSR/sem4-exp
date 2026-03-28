#include <bits/stdc++.h>
using namespace std;

// constructing adj matrix using given edge vector<vector>
vector<vector<int>> constructadj(int V, vector<vector<int>> &edges){
    
    vector<vector<int>> adj(V);
    for(auto it:edges){
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }
    return adj;
}

bool dfs(int u, int color, vector<int> &colors, vector<vector<int>> &adj) {

    colors[u] = color; 

    for(auto &v : adj[u]) {
        if(colors[v] == -1) {

            if(!dfs(v, 1 - color, colors, adj))
                return false;
        }
        else if(colors[v] == color) {
            return false;
        }
    }
    return true;
}

bool isBipartite(int V, vector<vector<int>> &edges) {

    vector<int> colors(V, -1); 
    
    vector<vector<int>> adj = constructadj(V,edges);

    for(int i = 0; i < V; i++) {

        if(colors[i] == -1) {
            if(!dfs(i, 0, colors, adj))
                return false; 
        }
    }

    return true;
}


int main() {
    
    int V = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    if(isBipartite(V, edges))
        cout << "true";
    else
        cout << "false";
    
    return 0;
}
