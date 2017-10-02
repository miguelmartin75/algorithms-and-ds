#include <bits/stdc++.h>
using namespace std;

using Graph = map<string, vector<string>>;

enum Colour
{
    WHITE = 0,
    GRAY,
    BLACK
};

bool dfs(Graph& g, const string& node, map<string, int>& colours)
{
    colours[node] = GRAY;
    for(auto& adj : g[node])
    {
        auto& c = colours[adj];
        if(c == BLACK) continue;
        if(c == GRAY) return true;
        else if(dfs(g, adj, colours)) return true;
    }
    colours[node] = BLACK;
    return false;
}

bool is_cycle(Graph& g)
{
    map<string, int> colours;
    for(auto& node : g)
    {
        if(colours[node.first] == BLACK) continue;
        if(dfs(g, node.first, colours)) return true;
    }
    return false;
}

// Problem D from ANZAC 2017 round 6
//
// Basically, given a list of relative heights of dwarves given (given by the dwarves). e.g.
// a > b
// a < c
// b > c
//
// Determine whether or not the information they provide is consistent. 
//
// If so print possible
// Otherwise print impossible
int main()
{
    int n;
    cin >> n;

    Graph graph;
    for(int i = 0; i < n; ++i)
    {
        string s1, conn, s2; 

        cin >> s1;
        cin >> conn;
        cin >> s2;

        if(conn == ">")
        {
            graph[s1].push_back(s2);
        }
        else
        {
            graph[s2].push_back(s1);
        }
    }

    cout << (is_cycle(graph) ? "impossible" : "possible") << endl;
}

