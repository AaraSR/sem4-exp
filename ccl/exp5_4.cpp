#include <bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int> >& graph, int S, vector<int>& par, vector<int>& dist)
{
    queue<int> q;

    dist[S] = 0;

    q.push(S);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbour : graph[node]) {
            if (dist[neighbour] == 1e9) {
                par[neighbour] = node;
                dist[neighbour] = dist[node] + 1;
                q.push(neighbour);
            }
        }
    }
}

void printShortestDistance(vector<vector<int>>& graph, int S, int D, int V)
{
    vector<int> par(V, -1);

    vector<int> dist(V, 1e9);

    bfs(graph, S, par, dist);

    if (dist[D] == 1e9) {
        cout << "Source and Destination are not connected";
        return;
    }

    vector<int> path;
    int currentNode = D;
    path.push_back(D);
    while (par[currentNode] != -1) {
        path.push_back(par[currentNode]);
        currentNode = par[currentNode];
    }

    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}


int main()
{
    int V = 8, E = 10;
    int S = 2, D = 6;
    vector<vector<int> > edges
        = { { 0, 1 }, { 1, 2 }, { 0, 3 }, { 3, 4 },
            { 4, 7 }, { 3, 7 }, { 6, 7 }, { 4, 5 },
            { 4, 6 }, { 5, 6 } };

    vector<vector<int> > graph(V);
    for (auto edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    printShortestDistance(graph, S, D, V);
    return 0;
}