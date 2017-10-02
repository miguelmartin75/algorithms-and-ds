// Tested on AlphabetOrderDiv2 on TopCoder
#include <bits/stdc++.h>
using namespace std;

enum Colour {
    WHITE,
    GRAY,
    BLACK
};

const int N = 26;
using Node = int;
using Graph = set<Node>[26]; // g[node] = adjacency list

bool dfs(Graph& g, int node, map<int, Colour>& c)
{
    if(c[node] == GRAY) return true;
    if(c[node] == BLACK) return false;

    c[node] = GRAY;

    for(auto& child : g[node])
    {
        if(dfs(g, child, c))
        {
            return true;
        }
    }

    c[node] = BLACK;

    return false;
}

bool isCycle(Graph& g)
{
    map<int, Colour> c;

    for(int i = 0; i < N; ++i)
    {
        if(dfs(g, i, c))
        {
            return true;
        }
    }
    return false;
}

struct AlphabetOrderDiv2
{
    string isOrdered(vector<string> words)
    {
        Graph graph;
        // create directed graph
        for(auto& w : words)
        {
            for(int i = 1; i < w.size(); ++i)
            {
                const char ch1 = w[i];
                const char ch2 = w[i - 1];
                if(ch1 == ch2) continue;
                graph[ch1 - 'a'].insert(ch2 - 'a');
            }
        }

        // check for cycles
        return isCycle(graph) ? "Impossible" : "Possible";
    }
};

#ifdef LOCAL
int main(int argc, char *argv[])
{
    AlphabetOrderDiv2 div;
    //cout << div.isOrdered({"ac"}) << endl;
    cout << div.isOrdered({"topcoder","topcoder"}) << endl;
    cout << div.isOrdered({"algorithm", "contest"}) << endl;
    //cout << div.isOrdered({"pink","floyd"}) << endl;
    //cout << div.isOrdered({"gimnasia","y","esgrima","la","plata"}) << endl;
    //cout << div.isOrdered({"hello","hello"}) << endl;
    //cout << div.isOrdered({"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}) << endl;
    //cout << div.isOrdered({"ab","bc","ca"}) << endl;
    //cout << div.isOrdered({{"xxxxxyeeeemmmpppprrcccwwwwwkkkvvvbbbbbhhqqfuussssaaaaazzziii", "xxyyyeeeemppppppooorccccnnwwkkkkkvvjjjjhhhqqqqqqfffftuddddsssaaaaaaaaggzzzzi", "xempporwwkkvvvvjhhtuuuuddddddagziiiil"}}) << endl;
    cout << div.isOrdered({{"xxxxxyeeeemmmpppprrcccwwwwwkkkvvvbbbbbhhqqfuussssaaaaazzziii", "xxyyyeeeemppppppooorccccnnwwkkkkkvvjjjjhhhqqqqqqfffftuddddsssaaaaaaaaggzzzzi", "xempporwwkkvvvvjhhtuuuuddddddagziiiil"}}) << endl;
}
#endif

