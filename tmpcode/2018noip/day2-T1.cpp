#include <bits/stdc++.h>
using namespace std;

const int N = 5555;

vector <pair<int,int> > e[N];
int n, m;
bool vise[N];
int fa[N], fid[N];
vector <int> idx;
bool instack[N];

void input () {
    scanf("%d%d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        e[a].push_back(make_pair(b, i));
        e[b].push_back(make_pair(a, i));
    }
}


vector <int> ord;
void go (int u, int f) {
    ord.push_back(u);
    sort (e[u].begin(), e[u].end());
    for (auto it : e[u]) {
        int v = it.first;
        if (v != f && !vise[it.second]) {
            go (it.first, u);
        }
    }
}

void update(vector <int> &ret, vector <int> tmp) {
    for (int i = 0; i < n; i++) {
        if (tmp[i] > ret[i]) {
            return ;
        }
        if (tmp[i] < ret[i]) {
            ret = tmp;
            return ;
        }
    }
}

void solve (vector <int> &ret) {
    ord.clear();
    go(0, -1);
    update(ret, ord);
}

void dfs(int u, int id) {
    fid[u] = id;
    instack[u] = true;
    for (auto it : e[u]) {
        int v = it.first;
        if (it.second != id) {
            if (instack[v]) {
                idx.push_back(it.second);
                int x = id;
                while (x != fid[v]){
                    idx.push_back(x);
                    x = fa[x];
                } 
                continue;
            }
            fa[it.second] = id;
            dfs(v, it.second);
        }
    }
    instack[u] = false;
}


void run() {
    dfs(0, -1);
    vector <int> ret(n, n);
    for (int i = 0; i < (int)idx.size(); i++) {
        vise[idx[i]] = true;
        solve(ret);
        vise[idx[i]] = false;
    }
    if (idx.size() == 0) {
        solve(ret);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", ret[i] + 1 );
    }
    puts("");
}

int main() {
    input();
    run();
    return 0;
}
