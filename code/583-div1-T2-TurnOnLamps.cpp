#include <bits/stdc++.h>
using namespace std;

const int N = 55;
struct Edge {
    int to;
    bool important;
    bool opened;
    Edge(int to=0,bool important=false,bool opened=false): to(to),important(important),opened(opened) {
    }
};

vector <Edge> e[N]; // point to, important
int cnt[N];
int p[N], owe[N];
int ret;

void dfs(int u, int f) { 
    int important_edges_need_open = 0;
    owe[u] = 0;
    for (auto it : e[u]) {
        if (it.to != f) {
            dfs(it.to, u);
            int need = it.important && !it.opened;
            owe[u] ^= need;
            important_edges_need_open += need;
            if (it.opened && it.important) {
                ret += owe[it.to];
            }
        }
    }
    ret += important_edges_need_open / 2;
}
int main () {
    int n;
    string start, imp;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> p[i];
    }
    cin >> start >> imp;
    for (int i = 0; i < n - 1; i++) {
        e[i + 1].push_back(Edge(p[i], imp[i] == '1', start[i] == '1'));
        e[p[i]].push_back(Edge(i + 1, imp[i] == '1', start[i] == '1'));
    }
    dfs(0, -1);
    cout << ret << endl;
    return 0;
}
