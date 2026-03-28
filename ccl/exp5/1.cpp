#include <iostream>
#include<vector>
using namespace std;

bool dfs(int v, vector<vector<int>> &adj, vector<bool> &visited, int parent)
{
    // current node is vector "visited[]", holds T or F for each vertex in adj_list{} 
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    // recursive func for adj vertices of v
    for (int i : adj[v])
    {
        // check dfs() if adj vertice 'i' is not visited
        if (!visited[i])
        {
            if (dfs(i, adj, visited, v))
                return true;
        }
        
        // check if 'i' is parent of 'v'
        else if (i != parent)
            return true;
    }

    // once all vertices are visited, dfs() ends (returns F)
    return false;
}

// Returns true if the graph contains a cycle, else false.
bool isCycle(vector<vector<int>> &adj)
{
    int V= adj.size();
    vector<bool> visited(V, false);     // mark all vertices F (not visited)

    for (int u = 0; u < V; u++)
    {
        if (!visited[u])
        {
            if (dfs(u, adj, visited, -1))
                return true;
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> adj = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};

    // adj list:
    //      0    1    2    3
    //  0   0    1    1    0
    //  1   1    0    1    0
    //  2   1    1    0    1
    //  3   0    0    1    0

    isCycle(adj) ? cout << "true" : cout << "false";

    return 0;

}