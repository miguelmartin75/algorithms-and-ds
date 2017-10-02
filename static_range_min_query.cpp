#include <bits/stdc++.h>
using namespace std;

int rmq[18][50000];

int lg2(int x) 
{
    int p = 0;
    while(x > 0)
    {
        p++;
        x /= 2;
    }
    return p;
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    for(int i = 0; i < n; ++i) cin >> rmq[0][i];

    for(int p = 1; p < 18; ++p)
    {
        for(int i = 0; i < n; ++i)
        {
            const int offset = 1 << (p - 1);
            if(i + offset > n) continue;
            rmq[p][i] = min(rmq[p - 1][i], rmq[p - 1][i + offset]);
        }
    }

    int q;
    cin >> q;

    for(int x = 0; x < q; ++x)
    {
        int i, j;
        cin >> i >> j;
        if(j < i) swap(i, j);

        int p = lg2(j - i + 1) - 1;
        cout << min(rmq[p][i], rmq[p][j - (1 << p) + 1]) << endl;
    }
}
