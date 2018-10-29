#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

vector <int> e[N];
int col[N];
int sz[N];
int sum;
int mx;
bool vis[N];

void dfs(int u, int f) {
    sz[u] = 1;
    int idx = -1;
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v == f) {
            continue;
        }
        dfs(v, u);
        sz[u] += sz[v];
        if (idx == -1 || sz[v] > sz[edge[u][idx]]) {
            idx = i;
        }
    }
    if (~idx) {
        swap(edge[u][0], edge[u][idx]);
    }
}


void insert(int u, int f, int v) {
}

void solve(int u, int f, bool big) {
    for (int i = 1; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v == f) {
            continue;
        }
        solve(v, u, false);
    }
    if (e[u].first() != f) {
        solve(e[u].first(), u, true);
        vis[e[u].first()] = true;
    }

    insert(u, f, 1); // add the light sons
    ans[u] = sum;
    if (e[u].first() != -1) {
        vis[e[u].first()] = false;
    }
    if(false == big) {
        insert(u, f, -1);
        mx = sum = 0;
    }
}

int main (){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &col[i]);
    }
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(0, -1);
    solve(0, -1);
    return 0;
}
