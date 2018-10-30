#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

vector <int> e[N];
int col[N];
int sz[N];
int mx;
int cnt[N];
bool vis[N];
long long sum;
long long ans[N];

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
        if (idx == -1 || sz[v] > sz[e[u][idx]]) {
            idx = i;
        }
    }
    if (~idx) {
        swap(e[u][0], e[u][idx]);
    }
}


void insert(int u, int f, int v) {
    cnt[col[u]] += v;
    if (cnt[col[u]] > mx) {
        mx = cnt[col[u]];
        sum = col[u];
    } else if (cnt[col[u]] == mx){
        sum += col[u];
    }
    
    for (auto it : e[u]) {
        if (it != f && !vis[it]) {
            insert(it, u, v);
        }
    }
}

void solve(int u, int f, bool big) {
    for (int i = 1; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v == f) {
            continue;
        }
        solve(v, u, false);
    }
    if (*e[u].begin() != f) {
        solve(*e[u].begin(), u, true);
        vis[*e[u].begin()] = true;
    }

    insert(u, f, 1); // add u's light sons
    ans[u] = sum;
    if (*e[u].begin() != -1) {
        vis[*e[u].begin()] = false;
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
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(0, -1);
    solve(0, -1, false);
    for (int i = 0; i < n; i++) {
        printf("%lld ", ans[i]);
    }
    return 0;
}
