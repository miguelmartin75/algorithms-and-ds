// Max Flow implementation tested on UVA 259
#include <bits/stdc++.h>
using namespace std;

using Node = int;

const Node SOURCE = -1;
const Node SINK = -2;
const Node NO_ALLOC = -3;

using Graph = map<Node, map<Node, int>>;

vector<Node> find_path(Graph& graph)
{
    map<Node, Node> parents;
    map<Node, bool> visited;

    visited[SOURCE] = true;

    queue<Node> q;
    q.emplace(SOURCE);

    while(!q.empty())
    {
        Node top = q.front();
        q.pop();

        if(top == SINK)
        {
            vector<Node> path;
            Node curr = top;

            while(curr != SOURCE)
            {
                path.emplace_back(curr);
                curr = parents[curr];
            }
            path.emplace_back(SOURCE);

            return vector<Node>(path.rbegin(), path.rend());
        }

        for(auto& adj : graph[top])
        {
            if(visited[adj.first]) continue;
            if(adj.second <= 0) continue;

            visited[adj.first] = true;

            parents[adj.first] = top;
            q.emplace(adj.first);
        }
    }

    // no path
    return vector<Node>();
}

int get_bottleneck(Graph& graph, const vector<Node>& path)
{
    // find the bottle neck
    // probably better to do this when returning the path,
    // but doesn't matter
    int bottleneck = INT_MAX;

    for(int i = 1; i < path.size(); ++i)
    {
        int prev = path[i - 1];
        int curr = path[i];
        int edge_w = graph[prev][curr];

        bottleneck = min(bottleneck, edge_w);
    }

    return bottleneck;
}

pair<int, vector<Node>> max_flow(const Graph& graph)
{
    // reverse edges
    Graph reverse = graph;
    for(auto& x : graph)
    {
        auto& node = x.first;
        auto& adj = x.second;

        for(auto& a : adj)
        {
            reverse[a.first][node] = 0;
        }
    }

    int flow = 0;

    while(true)
    {
        auto path = find_path(reverse);
        if(path.empty())
            break;

        int bottleneck = get_bottleneck(reverse, path);

        // go through the path and decrease forward
        // edge by bottleneck and increase back edge by bottleneck
        for(int i = 1; i < path.size(); ++i)
        {
            int prev = path[i - 1];
            int curr = path[i];
            reverse[prev][curr] -= bottleneck;
            reverse[curr][prev] += bottleneck;
        }

        flow += bottleneck;
    }
    
    pair<int, vector<Node>> ans;
    ans.first = flow;
    ans.second = vector<Node>(10, NO_ALLOC);

    // go through each application
    // and work out what out-going edge that connects to a
    // computer is not 0 => those are the computers that are allocated
    for(auto& node : reverse)
    {
        if(node.first >= 'A' && node.first <= 'Z')
        {
            for(auto& comp : node.second)
            {
                if(comp.first < 0 || comp.first > 9) continue;
                if(comp.second == 0)
                {
                    ans.second[comp.first] = node.first;
                }
            }
        }
    }


    return ans;
}

void solve(Graph& graph, int num)
{
    if(graph.empty()) return;

    // connect computers to sink
    for(int i = 0; i < 10; ++i)
    {
        graph[i][SINK] = 1;
    }

    auto flow = max_flow(graph);

    if(flow.first < num)
    {
        cout << "!";
    }
    else
    {
        for(Node x : flow.second)
        {
            if(x == NO_ALLOC) cout << "_";
            else cout << ((char)x);
        }
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    Graph graph;

    int num = 0;
    string line;
    while(getline(cin, line))
    {
        if(line.empty())
        {
            solve(graph, num);

            num = 0;
            graph.clear();
            continue;
        }

        istringstream iss{line};

        string app, computers;
        iss >> app >> computers;

        map<Node, int> adj;
        for(int i = 0; i < computers.size() - 1; ++i)
        {
            adj[computers[i] - '0'] = 1;
        }

        char appName = app[0];
        int number = stoi(app.substr(1));

        graph[appName] = adj;
        graph[SOURCE][appName] = number;
        num += number;
    }

    solve(graph, num);
}
